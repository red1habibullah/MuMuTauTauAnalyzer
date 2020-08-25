#define MuMuTauMuTauMuAnalyzer_cxx
#include "MuMuTauMuTauMuAnalyzer.h"
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

void MuMuTauMuTauMuAnalyzer::Loop()
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
      TLorentzVector Mu4;

      float Mu1Iso;
      float Mu2Iso;
      float Mu3Iso;
      float Mu4Iso;

      unsigned int indexMu1 = -1;
      unsigned int indexMu2 = -1;
      // =============================================================================

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

      bool findMuMuPair = false;
      // ------- start loop on the second muon pair candidates -------
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
          bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
          bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
          bool passMuonID = isLoose || isMedium || isTight;
          bool passDXYDZ = recoMuonDXY->at(iMuon) < 0.2 && recoMuonDZ->at(iMuon) < 0.5;

          if (iMuon == indexMu1 || iMuon == indexMu2) continue;
          if ((!invertedMu4Iso && recoMuonIsolation->at(iMuon) > Mu4IsoThreshold) || (invertedMu4Iso && recoMuonIsolation->at(iMuon) < Mu4IsoThreshold) || (invertedMu4Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID || !passDXYDZ) continue;
          
          TLorentzVector Mu4Cand;
          Mu4Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          bool qcdVeto = (recoMuonPDGId->at(indexMu1) != recoMuonPDGId->at(iMuon) && (Mu1+Mu4Cand).M() > 12.0) || (recoMuonPDGId->at(indexMu2) != recoMuonPDGId->at(iMuon) && (Mu2+Mu4Cand).M() > 12.0);
          if (!qcdVeto) continue;

          if (Mu4Cand.DeltaR(Mu1) < 0.4 || Mu4Cand.DeltaR(Mu2) < 0.4) continue;
          Mu4.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          Mu4Iso = recoMuonIsolation->at(iMuon);

          float smallestDR = 1.0; // dR cut between Mu3 and Mu4
          bool findMu3 = false;

          for (unsigned int iMuon3=0; iMuon3<recoMuonPt->size(); iMuon3++)
          {
              bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon3) > 0;
              bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon3) > 0;
              bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon3) > 0;
              bool passMuonID = isLoose || isMedium || isTight;
              bool passDXYDZ = recoMuonDXY->at(iMuon3) < 0.2 && recoMuonDZ->at(iMuon3) < 0.5;

              if (iMuon3 == indexMu1 || iMuon3 == indexMu2 || iMuon3 == iMuon) continue;
              if ((!invertedMu3Iso && recoMuonIsolation->at(iMuon3) > Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon3) < Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon3) > MuIsoUpperBound) || !passMuonID || !passDXYDZ) continue;

              TLorentzVector Mu3Cand; // prepare this variable for dR(Mu3, Mu4) implementation
              Mu3Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon3), recoMuonEta->at(iMuon3), recoMuonPhi->at(iMuon3), recoMuonEnergy->at(iMuon3));
              bool qcdVeto = (recoMuonPDGId->at(indexMu1) != recoMuonPDGId->at(iMuon3) && (Mu1+Mu3Cand).M() > 12.0) || (recoMuonPDGId->at(indexMu2) != recoMuonPDGId->at(iMuon3) && (Mu2+Mu3Cand).M() > 12.0);
              if (!qcdVeto) continue;

              if ((Mu4.DeltaR(Mu3Cand) < smallestDR) && (recoMuonPDGId->at(iMuon3) == (-1) * recoMuonPDGId->at(iMuon)) && ((Mu4+Mu3Cand).M() < 60.0) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4))
              {
                  Mu3.SetPtEtaPhiE(recoMuonPt->at(iMuon3), recoMuonEta->at(iMuon3), recoMuonPhi->at(iMuon3), recoMuonEnergy->at(iMuon3));
                  Mu3Iso = recoMuonIsolation->at(iMuon3);
                  smallestDR = Mu4.DeltaR(Mu3);
                  findMu3 = true;
              } // end if find mu3 with mu4 matched
          } // end loop for mu3

          if (!findMu3) continue;
          else{
              findMuMuPair = true;
              break;
          } // end if findMu3
      } // end loop for Mu4

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight; 
      } // end if isMC == true

      // ---- fill histograms ----
      if (findMu1 && findMu2 && findMuMuPair)
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

          ptMu3Mu4->Fill((Mu3+Mu4).Pt(), weight);
          dRMu3Mu4->Fill(Mu3.DeltaR(Mu4), weight);
          invMassMu3Mu4->Fill((Mu3+Mu4).M(), weight);
          dRInvMassMu3Mu4->Fill(Mu3.DeltaR(Mu4), (Mu3+Mu4).M(), weight);

          mu3Iso->Fill(Mu3Iso, weight);
          mu4Iso->Fill(Mu4Iso, weight);

          mu3Pt->Fill(Mu3.Pt(), weight);
          mu3Eta->Fill(Mu3.Eta(), weight);
          mu3Phi->Fill(Mu3.Phi(), weight);

          mu4Pt->Fill(Mu4.Pt(), weight);
          mu4Eta->Fill(Mu4.Eta(), weight);
          mu4Phi->Fill(Mu4.Phi(), weight);

          dRMu1Mu3->Fill(Mu1.DeltaR(Mu3), weight);
          dRMu1Mu4->Fill(Mu1.DeltaR(Mu4), weight);
          dRMu2Mu3->Fill(Mu2.DeltaR(Mu3), weight);
          dRMu2Mu4->Fill(Mu2.DeltaR(Mu4), weight);

          ptMuMuTauMuTauMu->Fill((Mu1+Mu2+Mu3+Mu4).Pt(), weight);
          invMassMuMuTauMuTauMu->Fill((Mu1+Mu2+Mu3+Mu4).M(), weight);

          // ----- fill flat trees -----
          invMassMuMu = (Mu1+Mu2).M();
          visMassTauTau = (Mu3+Mu4).M();
          visMassMuMuTauTau = (Mu1+Mu2+Mu3+Mu4).M();

          deltaRMuMu = Mu1.DeltaR(Mu2);
          deltaRTauTau = Mu3.DeltaR(Mu4);

          Mu1Pt = Mu1.Pt();
          Mu1Eta = Mu1.Eta();

          Mu2Pt = Mu2.Pt();
          Mu2Eta = Mu2.Eta();

          Tau1Pt = Mu3.Pt();
          Tau1Eta = Mu3.Eta();
          Tau1Isolation = Mu3Iso;

          Tau2Pt = Mu4.Pt();
          Tau2Eta = Mu4.Eta();
          Tau2Isolation = Mu4Iso;

          eventWeight = weight/summedWeights;
          TreeMuMuTauTau->Fill();
      } // end if findMu1 && findMu2 && findMuMuPair
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
