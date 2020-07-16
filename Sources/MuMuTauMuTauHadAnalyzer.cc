#define MuMuTauMuTauHadAnalyzer_cxx
#include "MuMuTauMuTauHadAnalyzer.h"
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

void MuMuTauMuTauHadAnalyzer::Loop()
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
      TLorentzVector Tau;

      float Mu1Iso;
      float Mu2Iso;
      float Mu3Iso;
      float TauIso;
      float TauDM;

      unsigned int indexMu1 = -1;
      unsigned int indexMu2 = -1;
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
      float smallestDR = 1.0; // dR cut between Mu1 and Mu2
      bool findMu2 = false;

      // ---- start loop on muon candidates for mu2 ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          if (iMuon == indexMu1) continue;
          if ((invertedMu2Iso == false && recoMuonIsolation->at(iMuon) > Mu2IsoThreshold) || (invertedMu2Iso == true && recoMuonIsolation->at(iMuon) < Mu2IsoThreshold)) continue;

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

      bool findMuTauPair = false;
      // ------- start loop on tau candidates -------
      for (unsigned int iTau=0; iTau<recoTauPt->size(); iTau++)
      {
          if (deepTauID && recoTauDeepVSjetraw->size() > 0)
          {
              // -------------------------------------------------------------------------------
              bool condTauDeepVSeLoose = deepTauVSele == "LOOSE" && recoTauDeepVSeLoose->at(iTau)>0;
              bool condTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauDeepVSjetLoose->at(iTau)>0;
              bool condTauDeepVSmuLoose = deepTauVSmu == "LOOSE" && recoTauDeepVSmuLoose->at(iTau)>0;

              bool condTauDeepVSeMedium = deepTauVSele == "MEDIUM" && recoTauDeepVSeMedium->at(iTau)>0;
              bool condTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauDeepVSjetMedium->at(iTau)>0;
              bool condTauDeepVSmuMedium = deepTauVSmu == "MEDIUM" && recoTauDeepVSmuMedium->at(iTau)>0;

              bool condTauDeepVSeTight = deepTauVSele == "TIGHT" && recoTauDeepVSeTight->at(iTau)>0;
              bool condTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauDeepVSjetTight->at(iTau)>0;
              bool condTauDeepVSmuTight = deepTauVSmu == "TIGHT" && recoTauDeepVSmuTight->at(iTau)>0;

              bool condTauDeepVSeVLoose = deepTauVSele == "VLOOSE" && recoTauDeepVSeVLoose->at(iTau)>0;
              bool condTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauDeepVSjetVLoose->at(iTau)>0;
              bool condTauDeepVSmuVLoose = deepTauVSmu == "VLOOSE" && recoTauDeepVSmuVLoose->at(iTau)>0;

              bool condTauDeepVSeVTight = deepTauVSele == "VTIGHT" && recoTauDeepVSeVTight->at(iTau)>0;
              bool condTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauDeepVSjetVTight->at(iTau)>0;

              bool condTauDeepVSeVVLoose = deepTauVSele == "VVLOOSE" && recoTauDeepVSeVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauDeepVSjetVVLoose->at(iTau)>0;
              
              bool condTauDeepVSeVVTight = deepTauVSele == "VVTIGHT" && recoTauDeepVSeVVTight->at(iTau)>0;
              bool condTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauDeepVSjetVVTight->at(iTau)>0;

              bool condTauDeepVSeVVVLoose = deepTauVSele == "VVVLOOSE" && recoTauDeepVSeVVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVVLoose = deepTauVSjet == "VVVLOOSE" && recoTauDeepVSjetVVVLoose->at(iTau)>0;

              bool condTauDeepVSeNull = deepTauVSele != "LOOSE" && deepTauVSele != "MEDIUM" && deepTauVSele != "TIGHT" && deepTauVSele != "VLOOSE" && deepTauVSele != "VTIGHT" && deepTauVSele != "VVLOOSE" && deepTauVSele != "VVTIGHT" && deepTauVSele != "VVVLOOSE";
              bool condTauDeepVSmuNull = deepTauVSmu != "LOOSE" && deepTauVSmu != "MEDIUM" && deepTauVSmu != "TIGHT" && deepTauVSmu != "VLOOSE";
              // -------------------------------------------------------------------------------

              bool passCondTauDeepVSele = (condTauDeepVSeLoose || condTauDeepVSeMedium || condTauDeepVSeTight || condTauDeepVSeVLoose || condTauDeepVSeVTight || condTauDeepVSeVVLoose || condTauDeepVSeVVTight || condTauDeepVSeVVVLoose || condTauDeepVSeNull);
              bool passCondTauDeepVSjet = (condTauDeepVSjetLoose || condTauDeepVSjetMedium || condTauDeepVSjetTight || condTauDeepVSjetVLoose || condTauDeepVSjetVTight || condTauDeepVSjetVVLoose || condTauDeepVSjetVVTight || condTauDeepVSjetVVVLoose);
              bool passCondTauDeepVSmu = (condTauDeepVSmuLoose || condTauDeepVSmuMedium || condTauDeepVSmuTight || condTauDeepVSmuVLoose || condTauDeepVSmuNull);

              bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;

              // -------------------- inverted deep Tau ID -----------------------------
              bool condInvertTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauDeepVSjetLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauDeepVSjetMedium->at(iTau)<=0;
              bool condInvertTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauDeepVSjetTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauDeepVSjetVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauDeepVSjetVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauDeepVSjetVVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauDeepVSjetVVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVVLoose = recoTauDeepVSjetVVVLoose->at(iTau)>0;
              // -------------------------------------------------------------------------------

              bool passCondInvertTauDeepVSjet = ((condInvertTauDeepVSjetLoose || condInvertTauDeepVSjetMedium || condInvertTauDeepVSjetTight || condInvertTauDeepVSjetVLoose || condInvertTauDeepVSjetVTight || condInvertTauDeepVSjetVVLoose || condInvertTauDeepVSjetVVTight) && condInvertTauDeepVSjetVVVLoose && passCondTauDeepVSele && passCondTauDeepVSmu);
              // -------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauDeep) || (invertedTauIso && !passCondInvertTauDeepVSjet)) continue;
          } // end if deepTauID && recoTauDeepVSjetraw->size() > 0

          else{
              bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau)>0;
              bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau)>0;
              bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau)>0;
              bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau)>0;
              bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau)>0;
              bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau)>0;
              bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau)>0;

              bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight);
              // -------------------------------------------------------------------------------------------------

              bool condInvertTauMVARaw = recoTauIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condInvertTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau)<=0;
              bool condInvertTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau)<=0;
              bool condInvertTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau)<=0;
              bool condInvertTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau)<=0;
              bool condInvertTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau)<=0;

              // ------ always require tau candidates pass vvvloose MVA id in order to have similar dynamic shape as real tau
              bool passCondInvertTauMVA = (condInvertTauMVARaw && (condInvertTauMVAWPVVLoose || condInvertTauMVAWPVLoose || condInvertTauMVAWPLoose || condInvertTauMVAWPMedium || condInvertTauMVAWPTight || condInvertTauMVAWPVTight || condInvertTauMVAWPVVTight));
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauAntiMuMVALoose->at(iTau)>0;
              bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauAntiMuMVATight->at(iTau)>0; 
              bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

              bool passCondTauAntiMuMVA = (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull);
              // -------------------------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauMVA) || (invertedTauIso && !passCondInvertTauMVA) || !passCondTauAntiMuMVA) continue;
          } // end if !deepTauID (tauMVAID)

          TLorentzVector TauCand;
          TauCand.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));

          if (TauCand.DeltaR(Mu1) < 0.8 || TauCand.DeltaR(Mu2) < 0.8) continue;
          if ((recoTauDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
          Tau.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
          TauIso = deepTauID ? recoTauDeepVSjetraw->at(iTau) : recoTauIsoMVArawValue->at(iTau);
          TauDM = recoTauDecayMode->at(iTau);

          float smallestDR = 0.8; // dR cut between Mu3 and tau
          bool findMu3 = false;

          for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
          {
              if (iMuon == indexMu1 || iMuon == indexMu2) continue;

              TLorentzVector Mu3Cand; // prepare this variable for dR(Mu3, tau) implementation
              Mu3Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              bool overlapMuTau = recoMuonRefToTau->at(iMuon) > 0 && recoTauRefToMuon->at(iTau) > 0 && recoMuonRefToTau->at(iMuon) == recoTauRefToMuon->at(iTau);

              if ((Tau.DeltaR(Mu3Cand) < smallestDR) && (recoTauPDGId->at(iTau)/fabs(recoTauPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))) && ((Tau+Mu3Cand).M() < 60.0) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4) && !overlapMuTau)
              {
                  Mu3.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
                  Mu3Iso = recoMuonIsolation->at(iMuon); 
                  smallestDR = Tau.DeltaR(Mu3);
                  findMu3 = true;
              } // end if find mu3 with tau matched
          } // end loop for mu3

          if (!findMu3) continue;
          else{
              findMuTauPair = true;
              break;
          } // end if findMu3
      } // end loop for tau

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight; 
      } // end if isMC == true

      // ---- fill histograms ----
      if (findMu1 && findMu2 && findMuTauPair)
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

          ptMu3Tau->Fill((Mu3+Tau).Pt(), weight);
          dRMu3Tau->Fill(Mu3.DeltaR(Tau), weight);
          invMassMu3Tau->Fill((Mu3+Tau).M(), weight);
          dRInvMassMu3Tau->Fill(Mu3.DeltaR(Tau), (Mu3+Tau).M(), weight);

          mu3Iso->Fill(Mu3Iso, weight);
          tauIsoMVA->Fill(TauIso, weight);
          tauDecayMode->Fill(TauDM, weight);

          mu3Pt->Fill(Mu3.Pt(), weight);
          mu3Eta->Fill(Mu3.Eta(), weight);
          mu3Phi->Fill(Mu3.Phi(), weight);

          tauPt->Fill(Tau.Pt(), weight);
          tauEta->Fill(Tau.Eta(), weight);
          tauPhi->Fill(Tau.Phi(), weight);
          tauMass->Fill(Tau.M(), weight);

          dRMu1Mu3->Fill(Mu1.DeltaR(Mu3), weight);
          dRMu1Tau->Fill(Mu1.DeltaR(Tau), weight);
          dRMu2Mu3->Fill(Mu2.DeltaR(Mu3), weight);
          dRMu2Tau->Fill(Mu2.DeltaR(Tau), weight);

          ptMuMuTauMuTauHad->Fill((Mu1+Mu2+Mu3+Tau).Pt(), weight);
          invMassMuMuTauMuTauHad->Fill((Mu1+Mu2+Mu3+Tau).M(), weight);

          // ----- fill flat trees -----
          invMassMuMu = (Mu1+Mu2).M();
          visMassTauTau = (Mu3+Tau).M();
          visMassMuMuTauTau = (Mu1+Mu2+Mu3+Tau).M();

          deltaRMuMu = Mu1.DeltaR(Mu2);
          deltaRTauTau = Mu3.DeltaR(Tau);

          Mu1Pt = Mu1.Pt();
          Mu1Eta = Mu1.Eta();

          Mu2Pt = Mu2.Pt();
          Mu2Eta = Mu2.Eta();

          Tau1Pt = Mu3.Pt();
          Tau1Eta = Mu3.Eta();
          Tau1Isolation = Mu3Iso;

          Tau2Pt = Tau.Pt();
          Tau2Eta = Tau.Eta();
          Tau2DecayMode = TauDM;
          Tau2Isolation = TauIso;

          eventWeight = weight/summedWeights;
          TreeMuMuTauTau->Fill();
      } // end if findMu1 && findMu2 && findMuTauPair
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
