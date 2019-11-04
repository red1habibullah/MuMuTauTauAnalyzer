#define MuMuTauHadTauHadAnalyzer_cxx
#include "MuMuTauHadTauHadAnalyzer.h"
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

void MuMuTauHadTauHadAnalyzer::Loop()
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

      // ---- prepare for the vector of matched muon pairs and tau-tau pairs ---
      vector<TLorentzVector> Mu1s;
      vector<TLorentzVector> Mu2s;
      vector<TLorentzVector> Tau1s;
      vector<TLorentzVector> Tau2s;

      vector<float> Mu1Iso;
      vector<float> Mu2Iso;
      vector<float> Tau1Iso;
      vector<float> Tau1DM;
      vector<float> Tau1MediumIsoDisc;
      vector<float> Tau2Iso;
      vector<float> Tau2DM;
      vector<float> Tau2MediumIsoDisc;

      Mu1s.clear();
      Mu2s.clear();
      Tau1s.clear();
      Tau2s.clear();

      Mu1Iso.clear();
      Mu2Iso.clear();
      Tau1Iso.clear();
      Tau1DM.clear();
      Tau1MediumIsoDisc.clear();
      Tau2Iso.clear();
      Tau2DM.clear();
      Tau2MediumIsoDisc.clear();
      // ========================================================================

      // ---- these vectors containing the rank of each matched muon to avoid double counting ---
      vector<int> indexMu1s;
      vector<int> indexMu2s;
      vector<int> indexTau2s;

      indexMu1s.clear();
      indexMu2s.clear();
      indexTau2s.clear();
      // =============================================================================

      // ---- these vectors containing the muons and taus that are not matched into pairs --- 
      vector<TLorentzVector> unMatchedMus;
      vector<TLorentzVector> unMatchedTaus;

      vector<float> unMatchedMuonIso;
      vector<float> unMatchedTauIso;
      vector<float> unMatchedTauDM;

      unMatchedMus.clear();
      unMatchedTaus.clear();

      unMatchedMuonIso.clear();
      unMatchedTauIso.clear();
      unMatchedTauDM.clear();
      // ============================================================================

      // ---- define varibles that will be used to be pushed into the above vectors ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Tau1;
      TLorentzVector Tau2;
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
          float smallestDR = 1.0; // dR cut between Mu1 and Mu2
          bool findMu2 = false;
          int indexMu2 = 0;

          for (unsigned int iMuon2=iMuon+1; iMuon2<recoMuonPt->size(); iMuon2++)
          {
              std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon2);
              if (iter2 != indexMu2s.end()) continue;

              if ((invertedMu2Iso == false && recoMuonIsolation->at(iMuon2) > Mu2IsoThreshold) || (invertedMu2Iso == true && recoMuonIsolation->at(iMuon2) < Mu2IsoThreshold)) continue;
              TLorentzVector Mu2Cand; // prepare this variable for dR(Mu1,Mu2) implementation
              Mu2Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon2), recoMuonEta->at(iMuon2), recoMuonPhi->at(iMuon2), recoMuonEnergy->at(iMuon2));
              if((Mu1.DeltaR(Mu2Cand) < smallestDR) && (recoMuonPDGId->at(iMuon) == (-1) * recoMuonPDGId->at(iMuon2)))
              {
                  Mu2.SetPtEtaPhiE(recoMuonPt->at(iMuon2), recoMuonEta->at(iMuon2), recoMuonPhi->at(iMuon2), recoMuonEnergy->at(iMuon2));
                  smallestDR = Mu1.DeltaR(Mu2);
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

              Mu1Iso.push_back(recoMuonIsolation->at(iMuon));
              Mu2Iso.push_back(recoMuonIsolation->at(indexMu2));
          } // end if findMu2 
      } // end loop for mu1

      // ------- start loop on tau candidates -------
      for (unsigned int iTau=0; iTau<recoTauPt->size(); iTau++)
      {
          if ((invertedTauIso == false && recoTauIsoMVAMedium->at(iTau) <= 0) || (invertedTauIso == true && recoTauIsoMVAMedium->at(iTau) > 0)) continue;
          if (((tauAntiMuDisc == "LOOSE") && (recoTauAntiMuMVALoose->at(iTau) <= 0)) || ((tauAntiMuDisc == "TIGHT") && (recoTauAntiMuMVATight->at(iTau) <= 0))) continue;
          Tau1.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
          float smallestDR = 0.8; // dR cut between tau1 and tau2
          bool findTau2 = false;
          int indexTau2 = 0;

          for (unsigned int iTau2=iTau+1; iTau2<recoTauPt->size(); iTau2++)
          {
              TLorentzVector Tau2Cand; // prepare this variable for dR(tau1, tau2) implementation
              Tau2Cand.SetPtEtaPhiE(recoTauPt->at(iTau2), recoTauEta->at(iTau2), recoTauPhi->at(iTau2), recoTauEnergy->at(iTau2));
              if ((Tau1.DeltaR(Tau2Cand) < smallestDR) && (recoTauPDGId->at(iTau) == (-1) * recoTauPDGId->at(iTau2)))
              {
                  Tau2.SetPtEtaPhiE(recoTauPt->at(iTau2), recoTauEta->at(iTau2), recoTauPhi->at(iTau2), recoTauEnergy->at(iTau2));
                  smallestDR = Tau1.DeltaR(Tau2);
                  findTau2 = true;
                  indexTau2 = iTau2;
              } // end if find tau2 with tau1 matched
          } // end loop for tau2

          if (findTau2 == true)
          {
              Tau1s.push_back(Tau1);
              Tau2s.push_back(Tau2);

              indexTau2s.push_back(indexTau2);

              Tau1Iso.push_back(recoTauIsoMVArawValue->at(iTau));
              Tau1MediumIsoDisc.push_back(recoTauIsoMVAMedium->at(iTau));
              Tau1DM.push_back(recoTauDecayMode->at(iTau));

              Tau2Iso.push_back(recoTauIsoMVArawValue->at(indexTau2));
              Tau2MediumIsoDisc.push_back(recoTauIsoMVAMedium->at(indexTau2));
              Tau2DM.push_back(recoTauDecayMode->at(indexTau2));
          } // end if findTau2

          else{
              unMatchedTaus.push_back(Tau1);
              unMatchedTauIso.push_back(recoTauIsoMVArawValue->at(iTau));
              unMatchedTauDM.push_back(recoTauDecayMode->at(iTau));
          } // end else findTau2
      } // end loop for tau

      // ---- search for unMatched muon candidates ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          std::vector<int>::iterator iter1 = std::find(indexMu1s.begin(), indexMu1s.end(), iMuon);
          std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon);

          if (iter1 == indexMu1s.end() && iter2 == indexMu2s.end())
          {
              unMatchedMu.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              unMatchedMus.push_back(unMatchedMu);
              unMatchedMuonIso.push_back(recoMuonIsolation->at(iMuon));
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
      nMatchedTauTauPair->Fill(Tau1s.size(), weight);
      nUnMatchedMu->Fill(unMatchedMus.size(), weight);
      nUnMatchedTau->Fill(unMatchedTaus.size(), weight);
      nMatchedMuPairNMatchedTauTauPair->Fill(Mu1s.size(), Tau1s.size(), weight);

      if (Mu1s.size() >0 && Tau1s.size() >0)
      {
          // --- filling histograms of four-body of mu-mu-tau-tau ---
          for (unsigned int iMuon=0; iMuon<Mu1s.size(); iMuon++)
          {
              Mu1 = Mu1s.at(iMuon);
              Mu2 = Mu2s.at(iMuon);
              TLorentzVector Mu1Mu2 = Mu1 + Mu2;
              bool passDR = false; // dR between mu-mu pair and tau-tau pair

              for (unsigned int iTau=0; iTau<Tau1s.size(); iTau++)
              {
                  Tau1 = Tau1s.at(iTau);
                  Tau2 = Tau2s.at(iTau);
                  TLorentzVector TauTau = Tau1 + Tau2;
                  TLorentzVector MuMuTauTau = Mu1Mu2 + TauTau;

                  if (Mu1.DeltaR(Tau1) > 0.8 && Mu2.DeltaR(Tau1) > 0.8 && Mu1.DeltaR(Tau2) > 0.8 && Mu2.DeltaR(Tau2) > 0.8)
                  {
                      passDR = true;

                      ptTauTau->Fill(TauTau.Pt(), weight);
                      dRTauTau->Fill(Tau1.DeltaR(Tau2), weight);
                      invMassTauTau->Fill(TauTau.M(), weight);
                      dRInvMassTauTau->Fill(Tau1.DeltaR(Tau2), TauTau.M(), weight);

                      tauIsoMVA->Fill(Tau1Iso.at(iTau), weight);
                      tauDecayMode->Fill(Tau1DM.at(iTau), weight);

                      tau2IsoMVA->Fill(Tau2Iso.at(iTau), weight);
                      tau2DecayMode->Fill(Tau2DM.at(iTau), weight);

                      tauPt->Fill(Tau1.Pt(), weight);
                      tauEta->Fill(Tau1.Eta(), weight);
                      tauPhi->Fill(Tau1.Phi(), weight);
                      tauMass->Fill(Tau1.M(), weight);

                      tau2Pt->Fill(Tau2.Pt(), weight);
                      tau2Eta->Fill(Tau2.Eta(), weight);
                      tau2Phi->Fill(Tau2.Phi(), weight);
                      tau2Mass->Fill(Tau2.M(), weight);

                      dRMu1Tau->Fill(Mu1.DeltaR(Tau1), weight);
                      dRMu1Tau2->Fill(Mu1.DeltaR(Tau2), weight);
                      dRMu2Tau->Fill(Mu2.DeltaR(Tau1), weight);
                      dRMu2Tau2->Fill(Mu2.DeltaR(Tau2), weight);

                      ptMuMuTauHadTauHad->Fill(MuMuTauTau.Pt(), weight);
                      invMassMuMuTauHadTauHad->Fill(MuMuTauTau.M(), weight);
                      break;
                  } // end if dR between mu-mu pair and tau-tau pair
              } // end loop for tau-tau pairs
              
              if (passDR == true)
              {
                  ptMu1Mu2->Fill(Mu1Mu2.Pt(), weight);
                  dRMu1Mu2->Fill(Mu1.DeltaR(Mu2), weight);
                  invMassMu1Mu2->Fill(Mu1Mu2.M(), weight);
                  dRInvMassMu1Mu2->Fill(Mu1.DeltaR(Mu2), Mu1Mu2.M(), weight);

                  mu1Iso->Fill(Mu1Iso.at(iMuon), weight);
                  mu2Iso->Fill(Mu2Iso.at(iMuon), weight);

                  mu1Pt->Fill(Mu1.Pt(), weight);
                  mu1Eta->Fill(Mu1.Eta(), weight);
                  mu1Phi->Fill(Mu1.Phi(), weight);

                  mu2Pt->Fill(Mu2.Pt(), weight);
                  mu2Eta->Fill(Mu2.Eta(), weight);
                  mu2Phi->Fill(Mu2.Phi(), weight);
                  break;
              } // end if passDR between mu-mu pair and tau-tau pair
          } // end loop for mu-mu pairs
      } // end if mu-mu & tau-tau pairs

      for (unsigned int iMuon=0; iMuon<unMatchedMus.size(); iMuon++)
      {
          unMatchedMuIso->Fill(unMatchedMuonIso.at(iMuon), weight);
          unMatchedMuPt->Fill(unMatchedMus.at(iMuon).Pt(), weight);
          unMatchedMuEta->Fill(unMatchedMus.at(iMuon).Eta(), weight);
          unMatchedMuPhi->Fill(unMatchedMus.at(iMuon).Phi(), weight);
      } // end loop for unMatched muons

      for (unsigned int iTau=0; iTau<unMatchedTaus.size(); iTau++)
      {
          unMatchedTauIsoMVA->Fill(unMatchedTauIso.at(iTau), weight);
          unMatchedTauDecayMode->Fill(unMatchedTauDM.at(iTau), weight);
          unMatchedTauPt->Fill(unMatchedTaus.at(iTau).Pt(), weight);
          unMatchedTauEta->Fill(unMatchedTaus.at(iTau).Eta(), weight);
          unMatchedTauPhi->Fill(unMatchedTaus.at(iTau).Phi(), weight);
      } // end loop for unMatched taus
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
