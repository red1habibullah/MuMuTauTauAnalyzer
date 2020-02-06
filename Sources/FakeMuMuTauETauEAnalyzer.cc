#define FakeMuMuTauETauEAnalyzer_cxx
#include "FakeMuMuTauETauEAnalyzer.h"
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

void FakeMuMuTauETauEAnalyzer::Loop()
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

      // ---- prepare for the vector of matched muon pairs and an additional muon pair candidate ---
      vector<TLorentzVector> Mu1s;
      vector<TLorentzVector> Mu2s;
      vector<TLorentzVector> Ele1s;
      vector<TLorentzVector> Ele2s;

      vector<float> Ele1Iso;
      vector<float> Ele2Iso;

      Mu1s.clear();
      Mu2s.clear();
      Ele1s.clear();
      Ele2s.clear();

      Ele1Iso.clear();
      Ele2Iso.clear();
      // ========================================================================

      // ---- these vectors containing the rank of each matched muon to avoid double counting ---
      vector<int> indexMu1s;
      vector<int> indexMu2s;

      indexMu1s.clear();
      indexMu2s.clear();
      // =============================================================================

      // ---- these vectors containing the muons that are not matched into pairs nor third muon nor selected electron --- 
      vector<TLorentzVector> unMatchedMus;
      vector<TLorentzVector> unMatchedEles;

      unMatchedMus.clear();
      unMatchedEles.clear();
      // ============================================================================

      // ---- define varibles that will be used to be pushed into the above vectors ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Ele1;
      TLorentzVector Ele2;
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
              if((Mu2Cand.Pt() > highestPt) 
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
              break;
          } // end if findMu2 
      } // end loop for mu1

      // ---- search for a electron-electron pair for fake rate study ----
      for (unsigned int iEle=0; iEle<recoElectronPt->size(); iEle++)
      {
          if ((invertedEle1Iso == false && recoElectronIsolation->at(iEle) > Ele1IsoThreshold) || (invertedEle1Iso == true && recoElectronIsolation->at(iEle) < Ele1IsoThreshold)) continue;
          Ele1.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEcalTrkEnergyPostCorr->at(iEle));
          float smallestDR = 5.0; // dR between ele1 and ele2
          bool findEle2 = false;
          int indexEle2 = 0;

          for (unsigned int iEle2=0; iEle2<recoElectronPt->size(); iEle2++)
          {
              TLorentzVector Ele2Cand; // prepare this variable for dR(Ele1, Ele2) implementation
              Ele2Cand.SetPtEtaPhiE(recoElectronPt->at(iEle2), recoElectronEta->at(iEle2), recoElectronPhi->at(iEle2), recoElectronEcalTrkEnergyPostCorr->at(iEle2));
              if (recoElectronPDGId->at(iEle) == (-1) * recoElectronPDGId->at(iEle2) && Ele1.DeltaR(Ele2Cand) < smallestDR)
              {
                  Ele2.SetPtEtaPhiE(recoElectronPt->at(iEle2), recoElectronEta->at(iEle2), recoElectronPhi->at(iEle2), recoElectronEcalTrkEnergyPostCorr->at(iEle2));
                  smallestDR = Ele1.DeltaR(Ele2);
                  findEle2 = true;
                  indexEle2 = iEle2;
              } // end if find ele2 with electron matched
          } // end loop for ele2

          if (findEle2 == true)
          {
              Ele1s.push_back(Ele1);
              Ele2s.push_back(Ele2);

              Ele1Iso.push_back(recoElectronIsolation->at(iEle));
              Ele2Iso.push_back(recoElectronIsolation->at(indexEle2));
          } // end if findEle2

          else{
              unMatchedEles.push_back(Ele1);
          } // end else findEle2
      } // end loop for electron

      // ---- search for unMatched muon candidates ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          std::vector<int>::iterator iter1 = std::find(indexMu1s.begin(), indexMu1s.end(), iMuon);
          std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon);

          if (iter1 == indexMu1s.end() && iter2 == indexMu2s.end())
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
      nUnMatchedEle->Fill(unMatchedEles.size(), weight);      

      if (Mu1s.size() >0 && Ele1s.size() >0)
      {
          // --- filling histograms of mu-mu-mu-e ---
          for (unsigned int iMuon=0; iMuon<Mu1s.size(); iMuon++)
          {
              Mu1 = Mu1s.at(iMuon);
              Mu2 = Mu2s.at(iMuon);
              TLorentzVector Mu1Mu2 = Mu1 + Mu2;
              bool passDR = false; // dR between mu-mu pair and mu-e pair

              for (unsigned int iEle=0; iEle<Ele1s.size(); iEle++)
              {
                  Ele1 = Ele1s.at(iEle);
                  Ele2 = Ele2s.at(iEle);
                  TLorentzVector EleEle = Ele1 + Ele2;
                  TLorentzVector MuMuEleEle = Mu1Mu2 + EleEle;

                  if (Mu1.DeltaR(Ele1) > 0.4 && Mu2.DeltaR(Ele1) > 0.4 && Mu1.DeltaR(Ele2) > 0.4 && Mu2.DeltaR(Ele2) > 0.4)
                  {
                      passDR = true;

                      ptEleEle->Fill(EleEle.Pt(), weight);
                      dREleEle->Fill(Ele1.DeltaR(Ele2), weight);
                      invMassEleEle->Fill(EleEle.M(), weight);
                      dRInvMassEleEle->Fill(Ele1.DeltaR(Ele2), EleEle.M(), weight);

                      ele1Pt->Fill(Ele1.Pt(), weight);
                      ele1Eta->Fill(Ele1.Eta(), weight);
                      ele1Phi->Fill(Ele1.Phi(), weight);

                      ele2Pt->Fill(Ele2.Pt(), weight);
                      ele2Eta->Fill(Ele2.Eta(), weight);
                      ele2Phi->Fill(Ele2.Phi(), weight);

                      dRMu1Ele1->Fill(Mu1.DeltaR(Ele1), weight);
                      dRMu1Ele2->Fill(Mu1.DeltaR(Ele2), weight);
                      dRMu2Ele1->Fill(Mu2.DeltaR(Ele1), weight);
                      dRMu2Ele2->Fill(Mu2.DeltaR(Ele2), weight);

                      ptMuMuTauEleTauEle->Fill(MuMuEleEle.Pt(), weight);
                      invMassMuMuTauEleTauEle->Fill(MuMuEleEle.M(), weight);
                      break;
                  } // end if dR between mu-mu pair and e-e pair
              } // end for loop on e-e pair

              if (passDR == true)
              {
                  ptMu1Mu2->Fill(Mu1Mu2.Pt(), weight);
                  dRMu1Mu2->Fill(Mu1.DeltaR(Mu2), weight);
                  invMassMu1Mu2->Fill(Mu1Mu2.M(), weight);
                  dRInvMassMu1Mu2->Fill(Mu1.DeltaR(Mu2), Mu1Mu2.M(), weight);

                  mu1Pt->Fill(Mu1.Pt(), weight);
                  mu1Eta->Fill(Mu1.Eta(), weight);
                  mu1Phi->Fill(Mu1.Phi(), weight);

                  mu2Pt->Fill(Mu2.Pt(), weight);
                  mu2Eta->Fill(Mu2.Eta(), weight);
                  mu2Phi->Fill(Mu2.Phi(), weight);
                  break;
              } // end if passDR between mu-mu pair and e-e pair
          } // end loop for mu-mu pairs
      } // end if mu-mu pairs

      for (unsigned int iMuon=0; iMuon<unMatchedMus.size(); iMuon++)
      {
          unMatchedMuPt->Fill(unMatchedMus.at(iMuon).Pt(), weight);
          unMatchedMuEta->Fill(unMatchedMus.at(iMuon).Eta(), weight);
          unMatchedMuPhi->Fill(unMatchedMus.at(iMuon).Phi(), weight);
      } // end loop for unMatched muons

      for (unsigned int iEle=0; iEle<unMatchedEles.size(); iEle++)
      {
          unMatchedElePt->Fill(unMatchedEles.at(iEle).Pt(), weight);
          unMatchedEleEta->Fill(unMatchedEles.at(iEle).Eta(), weight);
          unMatchedElePhi->Fill(unMatchedEles.at(iEle).Phi(), weight);
      } // end loop for unMatched electrons
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
