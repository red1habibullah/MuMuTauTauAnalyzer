#define MuMuTauMuTauEAnalyzer_cxx
#include "MuMuTauMuTauEAnalyzer.h"
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

void MuMuTauMuTauEAnalyzer::Loop()
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
      TLorentzVector Mu3;
      TLorentzVector Ele;

      float Mu1Iso;
      float Mu2Iso;
      float Mu3Iso;
      float EleIso;

      unsigned int indexMu1 = -1;
      unsigned int indexMu2 = -1;
      // ============================================================================

      // ---- start loop on muon candidates for mu1 ----
      bool findMu1 = false;
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
          bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
          bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
          bool passMuonID = isLoose || isMedium || isTight;
          bool passDXYDZ = recoMuonDXY->at(iMuon) < 0.2 && recoMuonDZ->at(iMuon) < 0.5;

          if (recoMuonTriggerFlag->at(iMuon) == 1 && recoMuonIsolation->at(iMuon) < Mu1IsoThreshold && passMuonID && passDXYDZ) 
          {
              Mu1.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              Mu1Iso = recoMuonIsolation->at(iMuon);
              indexMu1 = iMuon;
              findMu1 = true;
              break;
          } // end if there is any matched Mu1 candidiate
      } // end loop for mu1

      if (!findMu1) continue;
      float smallestDR = 1.0; // dR cut between Mu1 and Mu2
      bool findMu2 = false;

      // ---- start loop on muon candidates for mu2 ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
          bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
          bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
          bool passMuonID = isLoose || isMedium || isTight;
          bool passDXYDZ = recoMuonDXY->at(iMuon) < 0.2 && recoMuonDZ->at(iMuon) < 0.5;

          if (iMuon == indexMu1) continue;
          if ((!invertedMu2Iso && recoMuonIsolation->at(iMuon) > Mu2IsoThreshold) || (invertedMu2Iso && recoMuonIsolation->at(iMuon) < Mu2IsoThreshold) || (invertedMu2Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID || !passDXYDZ) continue;

          TLorentzVector Mu2Cand; // prepare this variable for dR(Mu1,Mu2) implementation
          Mu2Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));

          if((Mu1.DeltaR(Mu2Cand) < smallestDR) && (recoMuonPDGId->at(indexMu1) == (-1) * recoMuonPDGId->at(iMuon)) && ((Mu1+Mu2Cand).M() > diMuonMassLowThreshold) && ((Mu1+Mu2Cand).M() < diMuonMassHighThreshold))
          {
              Mu2.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              Mu2Iso = recoMuonIsolation->at(iMuon);
              smallestDR = Mu1.DeltaR(Mu2);
              indexMu2 = iMuon;
              findMu2 = true;
          } // end if pair candidates
      } // end loop for mu2

      if (!findMu2) continue;
      bool findMuElePair = false;

      // ------- start loop on electron candidates -------
      for (unsigned int iEle=0; iEle<recoElectronPt->size(); iEle++)
      {
          bool condEleLoose = EleRelId == "LOOSE" && recoElectronIdLoose->at(iEle) > 0;
          bool condEleMedium = EleRelId == "MEDIUM" && recoElectronIdMedium->at(iEle) > 0;
          bool condEleTight = EleRelId == "TIGHT" && recoElectronIdTight->at(iEle) > 0;
          bool condEleNull = EleRelId != "LOOSE" && EleRelId != "MEDIUM" && EleRelId != "TIGHT" && recoElectronIsolation->at(iEle) < EleIsoUpperBound;
          bool passCondEleId = condEleLoose || condEleMedium || condEleTight || condEleNull;

          // -------------------- inverted electron ID -----------------------------
          bool condInvertEleLoose = EleRelId == "LOOSE" && recoElectronIdLoose->at(iEle) <= 0;
          bool condInvertEleMedium = EleRelId == "MEDIUM" && recoElectronIdMedium->at(iEle) <= 0;
          bool condInvertEleTight = EleRelId == "TIGHT" && recoElectronIdTight->at(iEle) <= 0;
          bool condInvertEleIso = recoElectronIsolation->at(iEle) < EleIsoUpperBound;
          bool passCondInvertEleId = (condInvertEleLoose || condInvertEleMedium || condInvertEleTight) && condInvertEleIso;

          if ((!invertedEle1Iso && !passCondEleId) || (invertedEle1Iso && !passCondInvertEleId)) continue;
          TLorentzVector EleCand;
          EleCand.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));

          if (EleCand.DeltaR(Mu1) < 0.4 || EleCand.DeltaR(Mu2) < 0.4) continue;
          Ele.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));
          EleIso = recoElectronIsolation->at(iEle);

          float smallestDR = 1.0; // dR cut between Mu3 and electron
          bool findMu3 = false;

          for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
          {
              bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
              bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
              bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
              bool passMuonID = isLoose || isMedium || isTight;
              bool passDXYDZ = recoMuonDXY->at(iMuon) < 0.2 && recoMuonDZ->at(iMuon) < 0.5;

              if (iMuon == indexMu1 || iMuon == indexMu2) continue;
              if ((!invertedMu3Iso && recoMuonIsolation->at(iMuon) > Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon) < Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID || !passDXYDZ) continue;

              TLorentzVector Mu3Cand; // prepare this variable for dR(Mu3, electron) implementation
              Mu3Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              bool qcdVeto = (recoMuonPDGId->at(indexMu1) != recoMuonPDGId->at(iMuon) && (Mu1+Mu3Cand).M() > 12.0) || (recoMuonPDGId->at(indexMu2) != recoMuonPDGId->at(iMuon) && (Mu2+Mu3Cand).M() > 12.0);
              if (!qcdVeto) continue;

              bool overlapMuEle = recoMuonRefToElectron->at(iMuon) > 0 && recoElectronRefToMuon->at(iEle) > 0 && recoMuonRefToElectron->at(iMuon) == recoElectronRefToMuon->at(iEle);

              if ((Ele.DeltaR(Mu3Cand) < smallestDR) && (recoElectronPDGId->at(iEle)/fabs(recoElectronPDGId->at(iEle)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))) && ((Ele+Mu3Cand).M() < 60.0) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4) && !overlapMuEle)
              {
                  Mu3.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
                  Mu3Iso = recoMuonIsolation->at(iMuon);
                  smallestDR = Ele.DeltaR(Mu3);
                  findMu3 = true;
              } // end if find mu3 with electron matched
          } // end loop for mu3

          if (!findMu3) continue;
          else{
              findMuElePair = true;
              break;
          } // end if findMu3
      } // end loop for electron

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight; 
      } // end if isMC == true

      // ---- fill histograms ----
      if (findMu1 && findMu2 && findMuElePair)
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

          ptMu3Ele->Fill((Mu3+Ele).Pt(), weight);
          dRMu3Ele->Fill(Mu3.DeltaR(Ele), weight);
          invMassMu3Ele->Fill((Mu3+Ele).M(), weight);
          dRInvMassMu3Ele->Fill(Mu3.DeltaR(Ele), (Mu3+Ele).M(), weight);

          mu3Iso->Fill(Mu3Iso, weight);
          ele1Iso->Fill(EleIso, weight);

          mu3Pt->Fill(Mu3.Pt(), weight);
          mu3Eta->Fill(Mu3.Eta(), weight);
          mu3Phi->Fill(Mu3.Phi(), weight);

          ele1Pt->Fill(Ele.Pt(), weight);
          ele1Eta->Fill(Ele.Eta(), weight);
          ele1Phi->Fill(Ele.Phi(), weight);

          dRMu1Mu3->Fill(Mu1.DeltaR(Mu3), weight);
          dRMu1Ele1->Fill(Mu1.DeltaR(Ele), weight);
          dRMu2Mu3->Fill(Mu2.DeltaR(Mu3), weight);
          dRMu2Ele1->Fill(Mu2.DeltaR(Ele), weight);

          ptMuMuTauMuTauEle->Fill((Mu1+Mu2+Mu3+Ele).Pt(), weight);
          invMassMuMuTauMuTauEle->Fill((Mu1+Mu2+Mu3+Ele).M(), weight);

          // ----- fill flat trees -----
          invMassMuMu = (Mu1+Mu2).M();
          visMassTauTau = (Mu3+Ele).M();
          visMassMuMuTauTau = (Mu1+Mu2+Mu3+Ele).M();

          deltaRMuMu = Mu1.DeltaR(Mu2);
          deltaRTauTau = Mu3.DeltaR(Ele);

          Mu1Pt = Mu1.Pt();
          Mu1Eta = Mu1.Eta();

          Mu2Pt = Mu2.Pt();
          Mu2Eta = Mu2.Eta();

          Tau1Pt = Mu3.Pt();
          Tau1Eta = Mu3.Eta();
          Tau1Isolation = Mu3Iso;

          Tau2Pt = Ele.Pt();
          Tau2Eta = Ele.Eta();
          Tau2Isolation = EleIso;

          eventWeight = weight/summedWeights;
          TreeMuMuTauTau->Fill();
      } // end if findMu1 && findMu2 && findMuElePair
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

   TreeMuMuTauTau->Write("TreeMuMuTauTau", TObject::kOverwrite);
   outputFile->Close();
}
