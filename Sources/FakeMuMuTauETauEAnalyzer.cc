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

      // ---- define varibles that will be used to be filled into histograms ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Ele1;
      TLorentzVector Ele2;

      float Mu1Iso;
      float Mu2Iso;
      float Ele1Iso;
      float Ele2Iso;

      unsigned int indexMu1 = -1;
      // ============================================================================

      // ---- start loop on muon candidates for mu1 ----
      bool findMu1 = false;
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          if (recoMuonTriggerFlag->at(iMuon) == 1 && recoMuonIsolation->at(iMuon) < 0.25)
          {
              Mu1.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              Mu1Iso = recoMuonIsolation->at(iMuon);
              indexMu1 = iMuon;
              findMu1 = true;
              break;
          } // end if there is any matched Mu1 candidiate
      } // end loop for mu1

      if (!findMu1) continue;
      float dRCut = 0.3; // dR cut between Mu1 and Mu2
      float highestPt = 0;
      float invMassLowThre = 60.0;
      float invMassHighThre = 120.0;
      bool findMu2 = false;

      // ---- start loop on muon candidates for mu2 ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          if (iMuon == indexMu1) continue;
          if (recoMuonIsolation->at(iMuon) > 0.25) continue;

          TLorentzVector Mu2Cand; // prepare this variable for dR(Mu1,Mu2) implementation
          Mu2Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          if((Mu1.DeltaR(Mu2Cand) > dRCut) && (Mu2Cand.Pt() > highestPt) 
                  && ((Mu1+Mu2Cand).M() > invMassLowThre) && ((Mu1+Mu2Cand).M() < invMassHighThre)
                  && (recoMuonPDGId->at(indexMu1) == (-1) * recoMuonPDGId->at(iMuon)))
          {
              Mu2.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              Mu2Iso = recoMuonIsolation->at(iMuon);
              highestPt = Mu2Cand.Pt();
              findMu2 = true;
          } // end if pair candidates
      } // end loop for mu2

      if (!findMu2) continue;
      bool findEleElePair = false;

      // ---- search for a electron-electron pair for fake rate study ----
      for (unsigned int iEle=0; iEle<recoElectronPt->size(); iEle++)
      {
          if ((invertedEle1Iso == false && recoElectronIsolation->at(iEle) > Ele1IsoThreshold) || (invertedEle1Iso == true && recoElectronIsolation->at(iEle) < Ele1IsoThreshold)) continue;
          TLorentzVector Ele1Cand;
          Ele1Cand.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));

          if (Ele1Cand.DeltaR(Mu1) < 0.4 || Ele1Cand.DeltaR(Mu2) < 0.4) continue;
          Ele1.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));
          Ele1Iso = recoElectronIsolation->at(iEle);
          
          float smallestDR = 4.0; // dR cut between Ele1 and Ele2
          bool findEle2 = false;

          for (unsigned int iEle2=0; iEle2<recoElectronPt->size(); iEle2++)
          {
              if (iEle2 == iEle) continue;
              TLorentzVector Ele2Cand; // prepare this variable for dR(Ele1, Ele2) implementation
              Ele2Cand.SetPtEtaPhiE(recoElectronPt->at(iEle2), recoElectronEta->at(iEle2), recoElectronPhi->at(iEle2), recoElectronEnergy->at(iEle2));
              if ((Ele1.DeltaR(Ele2Cand) < smallestDR) && (recoElectronPDGId->at(iEle) == (-1) * recoElectronPDGId->at(iEle2)) && ((Ele1+Ele2Cand).M() < 60.0) && (Ele2Cand.DeltaR(Mu1) > 0.4) && (Ele2Cand.DeltaR(Mu2) > 0.4))
              {
                  Ele2.SetPtEtaPhiE(recoElectronPt->at(iEle2), recoElectronEta->at(iEle2), recoElectronPhi->at(iEle2), recoElectronEnergy->at(iEle2));
                  Ele2Iso = recoElectronIsolation->at(iEle2);
                  smallestDR = Ele1.DeltaR(Ele2);
                  findEle2 = true;
              } // end if find ele2 with electron matched
          } // end loop for ele2

          if (!findEle2) continue;
          else{
              findEleElePair = true;
              break;
          } // end if findEle2
      } // end loop for electron

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight; 
      } // end if isMC == true

      // ---- fill histograms ----
      if (findMu1 && findMu2 && findEleElePair)
      {
          ptMu1Mu2->Fill((Mu1+Mu2).Pt(), weight);
          dRMu1Mu2->Fill(Mu1.DeltaR(Mu2), weight);
          invMassMu1Mu2->Fill((Mu1+Mu2).M(), weight);
          dRInvMassMu1Mu2->Fill(Mu1.DeltaR(Mu2), (Mu1+Mu2).M(), weight);

          mu1Iso->Fill(Mu1Iso, weight);
          mu2Iso->Fill(Mu2Iso, weight);

          mu1Pt->Fill(Mu1.Pt(), weight);
          mu1Eta->Fill(Mu1.Eta(), weight);
          mu1Phi->Fill(Mu1.Phi(), weight);

          mu2Pt->Fill(Mu2.Pt(), weight);
          mu2Eta->Fill(Mu2.Eta(), weight);
          mu2Phi->Fill(Mu2.Phi(), weight);

          ptEleEle->Fill((Ele1+Ele2).Pt(), weight);
          dREleEle->Fill(Ele1.DeltaR(Ele2), weight);
          invMassEleEle->Fill((Ele1+Ele2).M(), weight);
          dRInvMassEleEle->Fill(Ele1.DeltaR(Ele2), (Ele1+Ele2).M(), weight);

          ele1Iso->Fill(Ele1Iso, weight);
          ele2Iso->Fill(Ele2Iso, weight);

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

          ptMuMuTauEleTauEle->Fill((Mu1+Mu2+Ele1+Ele2).Pt(), weight);
          invMassMuMuTauEleTauEle->Fill((Mu1+Mu2+Ele1+Ele2).M(), weight);
      } // end if findMu1 && findMu2 && findEleElePair
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
