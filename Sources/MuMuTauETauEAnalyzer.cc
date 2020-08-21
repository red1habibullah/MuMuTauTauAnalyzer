#define MuMuTauETauEAnalyzer_cxx
#include "MuMuTauETauEAnalyzer.h"
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

void MuMuTauETauEAnalyzer::Loop()
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
              findMu2 = true;
          } // end if pair candidates
      } // end loop for mu2

      if (!findMu2) continue;
      bool findEleElePair = false;

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
          TLorentzVector Ele1Cand;
          Ele1Cand.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));

          if (Ele1Cand.DeltaR(Mu1) < 0.4 || Ele1Cand.DeltaR(Mu2) < 0.4) continue;
          Ele1.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));
          Ele1Iso = recoElectronIsolation->at(iEle);
          
          float smallestDR = 1.0; // dR cut between Ele1 and Ele2
          bool findEle2 = false;

          for (unsigned int iEle2=0; iEle2<recoElectronPt->size(); iEle2++)
          {
              if (iEle2 == iEle) continue;
              bool condEleLoose = EleRelId == "LOOSE" && recoElectronIdLoose->at(iEle2) > 0;
              bool condEleMedium = EleRelId == "MEDIUM" && recoElectronIdMedium->at(iEle2) > 0;
              bool condEleTight = EleRelId == "TIGHT" && recoElectronIdTight->at(iEle2) > 0;
              bool condEleNull = EleRelId != "LOOSE" && EleRelId != "MEDIUM" && EleRelId != "TIGHT" && recoElectronIsolation->at(iEle2) < EleIsoUpperBound;
              bool passCondEleId = condEleLoose || condEleMedium || condEleTight || condEleNull;

              // -------------------- inverted electron ID -----------------------------
              bool condInvertEleLoose = EleRelId == "LOOSE" && recoElectronIdLoose->at(iEle2) <= 0;
              bool condInvertEleMedium = EleRelId == "MEDIUM" && recoElectronIdMedium->at(iEle2) <= 0;
              bool condInvertEleTight = EleRelId == "TIGHT" && recoElectronIdTight->at(iEle2) <= 0;
              bool condInvertEleIso = recoElectronIsolation->at(iEle2) < EleIsoUpperBound;
              bool passCondInvertEleId = (condInvertEleLoose || condInvertEleMedium || condInvertEleTight) && condInvertEleIso;

              if ((!invertedEle2Iso && !passCondEleId) || (invertedEle2Iso && !passCondInvertEleId)) continue;

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

          // ----- fill flat trees -----
          invMassMuMu = (Mu1+Mu2).M();
          visMassTauTau = (Ele1+Ele2).M();
          visMassMuMuTauTau = (Mu1+Mu2+Ele1+Ele2).M();

          deltaRMuMu = Mu1.DeltaR(Mu2);
          deltaRTauTau = Ele1.DeltaR(Ele2);

          Mu1Pt = Mu1.Pt();
          Mu1Eta = Mu1.Eta();

          Mu2Pt = Mu2.Pt();
          Mu2Eta = Mu2.Eta();

          Tau1Pt = Ele1.Pt();
          Tau1Eta = Ele1.Eta();
          Tau1Isolation = Ele1Iso;

          Tau2Pt = Ele2.Pt();
          Tau2Eta = Ele2.Eta();
          Tau2Isolation = Ele2Iso;

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
