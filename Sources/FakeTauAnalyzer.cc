#define FakeTauAnalyzer_cxx
#include "FakeTauAnalyzer.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <iomanip>
#include <iostream>
#include <TLorentzVector.h>
#include <math.h>
using namespace std;

void FakeTauAnalyzer::Loop()
{
   TString outputfileName = createOutputFileName();
   TFile* outputFile = new TFile(outputfileName, "RECREATE");
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   if (nMaxEvents >= 0 && nMaxEvents  < nentries) nentries = nMaxEvents;
   cout << "We will run on " << nentries << " events" << endl;

   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry<nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

      if (jentry % 1000 == 0 && jentry > 0) cout << "*** Processing #Events: " << jentry << endl;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      // ---- prepare for the vector of matched muon pairs and a muon & tau candidate ---
      vector<TLorentzVector> Mu1s;
      vector<TLorentzVector> Mu2s;
      vector<TLorentzVector> Mu3s;
      vector<TLorentzVector> Taus;

      vector<float> TauIso;
      vector<float> TauDM;

      Mu1s.clear();
      Mu2s.clear();
      Mu3s.clear();
      Taus.clear();

      TauIso.clear();
      TauDM.clear();
      // ========================================================================

      // ---- these vectors containing the rank of each matched muon to avoid double counting ---
      vector<int> indexMu1s;
      vector<int> indexMu2s;
      vector<int> indexMu3s;

      indexMu1s.clear();
      indexMu2s.clear();
      indexMu3s.clear();
      // =============================================================================

      // ---- these vectors containing the muons that are not matched into pairs and third muon --- 
      vector<TLorentzVector> unMatchedMus;
      unMatchedMus.clear();
      // ============================================================================

      // ---- define varibles that will be used to be pushed into the above vectors ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Mu3;
      TLorentzVector Tau;
      TLorentzVector unMatchedMu;
      // ============================================================================

      // ---- start loop on muon candidates ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          if (indexMu2s.size() > 0) 
          {
              std::vector<int>::iterator iter = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon);
              if (iter != indexMu2s.end()) continue;
          } // end if there is any matched Mu2 candidiate

          if (recoMuonIsolation->at(iMuon) > 0.25) continue;
          Mu1.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          float dRCut = 0.3; // dR cut between Mu1 and Mu2
          float highestPt = 0;
          float invMassLowThre = 60.0;
          float invMassHighThre = 120.0;
          bool findMu2 = false;
          int indexMu2 = 0;

          for (unsigned int iMuon2=iMuon+1; iMuon2<recoMuonPt->size(); iMuon2++)
          {
              std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon2);
              if (iter2 != indexMu2s.end()) continue;

              if (recoMuonIsolation->at(iMuon2) > 0.25) continue;
              TLorentzVector Mu2Cand; // prepare this variable for dR(Mu1,Mu2) implementation
              Mu2Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon2), recoMuonEta->at(iMuon2), recoMuonPhi->at(iMuon2), recoMuonEnergy->at(iMuon2));
              if((Mu1.DeltaR(Mu2Cand) > dRCut) && (Mu2Cand.Pt() > highestPt) 
                      && ((Mu1+Mu2Cand).M() > invMassLowThre) && ((Mu1+Mu2Cand).M() < invMassHighThre)
                      && (recoMuonPDGId->at(iMuon) == (-1) * recoMuonPDGId->at(iMuon2)))
              {
                  Mu2.SetPtEtaPhiE(recoMuonPt->at(iMuon2), recoMuonEta->at(iMuon2), recoMuonPhi->at(iMuon2), recoMuonEnergy->at(iMuon2));
                  highestPt = Mu2Cand.Pt();
                  findMu2 = true;
                  indexMu2 = iMuon2;
              } // end if pair candidates
          } // end loop for mu2
          
          if (findMu2 == true)
          {
              Mu1s.push_back(Mu1);
              Mu2s.push_back(Mu2);

              indexMu1s.push_back(iMuon);
              indexMu2s.push_back(indexMu2);
          } // end if findMu2 
      } // end loop for mu1

      // ---- search for an additional muon and tau for fake rate study ----
      if (recoMuonPt->size()>2 && recoTauPt->size()>0)
      {
          for (unsigned int iTau=0; iTau<recoTauPt->size(); iTau++)
          {
              if ((tauMVAIsoRawORWP == true && recoTauIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau)>0))
              {
                  Tau.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
                  bool findMu3 = false;
                  int indexMu3 = 0;

                  for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
                  {
                      std::vector<int>::iterator iter1 = std::find(indexMu1s.begin(), indexMu1s.end(), iMuon);
                      std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon);
                      if (iter1 != indexMu1s.end() || iter2 != indexMu2s.end()) continue;

                      TLorentzVector Mu3Cand;
                      Mu3Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
                      if (recoTauPDGId->at(iTau)/fabs(recoTauPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)))
                      {
                          Mu3.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
                          findMu3 = true;
                          indexMu3 = iMuon;
                      } // end if find mu3 with opposite charge
                  } // end for loop on additional muons

                  if (findMu3 == true)
                  {
                      Mu3s.push_back(Mu3);
                      indexMu3s.push_back(indexMu3);

                      Taus.push_back(Tau);
                      TauIso.push_back(recoTauIsoMVArawValue->at(iTau));
                      TauDM.push_back(recoTauDecayMode->at(iTau));
                  } // end if findMu3
              } // end if a tau candidate passes the requirement
              else{
                  continue;
              } // end else a tau candidate passes the requirement
          } // end for loop on tau candidates
      } // end if tau cluster size > 0 && muon cluster > 2

      // ---- search for unMatched muon candidates ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          std::vector<int>::iterator iter1 = std::find(indexMu1s.begin(), indexMu1s.end(), iMuon);
          std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon);
          std::vector<int>::iterator iter3 = std::find(indexMu3s.begin(), indexMu3s.end(), iMuon);

          if (iter1 == indexMu1s.end() && iter2 == indexMu2s.end() && iter3 == indexMu3s.end())
          {
              unMatchedMu.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              unMatchedMus.push_back(unMatchedMu);
          } // end if find unMatched Mu
      } // end loop for unMatched muon candidates

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight; 
      } // end if isMC == true

      // ---- fill histograms ----
      nMatchedMuPair->Fill(Mu1s.size(), weight);
      nUnMatchedMu->Fill(unMatchedMus.size(), weight);
      
      if (Mu1s.size() >0 && Taus.size() >0)
      {
          // --- filling histograms of mu-mu ---
          for (unsigned int iMuon=0; iMuon<Mu1s.size(); iMuon++)
          {
              Mu1 = Mu1s.at(iMuon);
              Mu2 = Mu2s.at(iMuon);
              TLorentzVector Mu1Mu2 = Mu1 + Mu2;
              bool passDR = false; // dR between mu-mu pair and tau

              for (unsigned int iTau=0; iTau<Taus.size(); iTau++)
              {
                  Mu3 = Mu3s.at(iTau);
                  Tau = Taus.at(iTau);
                  TLorentzVector MuTau = Mu3 + Tau;
                  TLorentzVector MuMuTauTau = Mu1Mu2 + MuTau;

                  if (Mu1.DeltaR(Mu3) > 0.4 && Mu2.DeltaR(Mu3) > 0.4 && Mu1.DeltaR(Tau) > 0.8 && Mu2.DeltaR(Tau) > 0.8)
                  {
                      passDR = true;

                      ptMuTau->Fill(MuTau.Pt(), weight);
                      dRMuTau->Fill(Mu3.DeltaR(Tau), weight);
                      invMassMuTau->Fill(MuTau.M(), weight);
                      dRInvMassMuTau->Fill(Mu3.DeltaR(Tau), MuTau.M(), weight);

                      mu3Pt->Fill(Mu3.Pt(), weight);
                      mu3Eta->Fill(Mu3.Eta(), weight);
                      mu3Phi->Fill(Mu3.Phi(), weight);

                      tauPt->Fill(Tau.Pt(), weight);
                      tauEta->Fill(Tau.Eta(), weight);
                      tauPhi->Fill(Tau.Phi(), weight);
                      tauMass->Fill(Tau.M(), weight);
                      tauDecayMode->Fill(TauDM.at(iTau), weight);

                      dRMu1Mu3->Fill(Mu1.DeltaR(Mu3), weight);
                      dRMu1Tau->Fill(Mu1.DeltaR(Tau), weight);
                      dRMu2Mu3->Fill(Mu2.DeltaR(Mu3), weight);
                      dRMu2Tau->Fill(Mu2.DeltaR(Tau), weight);

                      ptMuMuTauTau->Fill(MuMuTauTau.Pt(), weight);
                      invMassMuMuTauTau->Fill(MuMuTauTau.M(), weight);
                      break;
                  } // end if dR between mu-mu pair and tau
              } // end for loop on taus

              if (passDR == true)
              {
                  ptMuMu->Fill(Mu1Mu2.Pt(), weight);
                  dRMuMu->Fill(Mu1.DeltaR(Mu2), weight);
                  invMassMuMu->Fill(Mu1Mu2.M(), weight);
                  dRInvMassMuMu->Fill(Mu1.DeltaR(Mu2), Mu1Mu2.M(), weight);

                  mu1Pt->Fill(Mu1.Pt(), weight);
                  mu1Eta->Fill(Mu1.Eta(), weight);
                  mu1Phi->Fill(Mu1.Phi(), weight);

                  mu2Pt->Fill(Mu2.Pt(), weight);
                  mu2Eta->Fill(Mu2.Eta(), weight);
                  mu2Phi->Fill(Mu2.Phi(), weight);
                  break;
              } // end if passDR between mu-mu pair and tau and additional muon
          } // end loop for mu-mu pairs
      } // end if mu-mu pairs

      for (unsigned int iMuon=0; iMuon<unMatchedMus.size(); iMuon++)
      {
          unMatchedMuPt->Fill(unMatchedMus.at(iMuon).Pt(), weight);
          unMatchedMuEta->Fill(unMatchedMus.at(iMuon).Eta(), weight);
          unMatchedMuPhi->Fill(unMatchedMus.at(iMuon).Phi(), weight);
      } // end loop for unMatched muons

   }// end loop for events

   outputFile->cd();

   int numberofhist = histColl.size();
   for(int i=0; i<numberofhist; i++){
       if (isMC) histColl[i]->Scale(lumiScale/summedWeights);
       histColl[i]->Write();
   } // end loop for writing all the histograms into the output file

   for(int j=0; j<numberofhist; j++){
       delete histColl[j];
   } // end loop for deleting all the histograms

   outputFile->Close();
}
