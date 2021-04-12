#define MuMuTauTauInclusiveAnalyzer_cxx
#include "MuMuTauTauInclusiveAnalyzer.h"
#include "RoccoR.h"
#include "functions.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TRandom.h>
#include <iomanip>
#include <iostream>
#include <TLorentzVector.h>
#include <math.h>
using namespace std;

void MuMuTauTauInclusiveAnalyzer::Loop()
{
   TString outputfileName = createOutputFileName();
   TFile* outputFile = new TFile(outputfileName, "RECREATE");
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   if (nMaxEvents >= 0 && nMaxEvents  < nentries) nentries = nMaxEvents;
   cout << "We will run on " << nentries << " events" << endl;

   Long64_t nbytes = 0, nb = 0;

   // ---- define the variable for rochester correction ----
   string rochesterFileName = rochesterFile.Data();
   RoccoR rc(rochesterFileName);
   double rochesterSF = 1;
   int errorMember = 0;

   if (muonScaleSyst < 0) muonScaleSyst = fabs(muonScaleSyst);
   if (muonScaleSyst > 104) muonScaleSyst = 104;
   if (muonScaleSyst > 5)
   {
       errorMember = muonScaleSyst - 5;
       muonScaleSyst = 1; // error set to statistical uncertainty replicas
   } // end if muonScaleSyst > 5

   for (Long64_t jentry=0; jentry<nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

      if (jentry % 1000 == 0 && jentry > 0) cout << "*** Processing #Events: " << jentry << endl;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight; 
      } // end if isMC == true

      // ---- define varibles that will be used to be filled into histograms ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Mu3;
      TLorentzVector Mu4;
      TLorentzVector Ele;
      TLorentzVector Tau;
      TLorentzVector Tau2;

      float Mu1Iso;
      float Mu2Iso;
      float Mu3Iso;
      float Mu4Iso;
      float EleIso;
      float TauIso;
      float TauDM;
      float Tau2Iso;
      float Tau2DM;

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
          //bool passDXYDZ = fabs(recoMuonDXY->at(iMuon)) < 0.2 && fabs(recoMuonDZ->at(iMuon)) < 0.5;

          //if (recoMuonTriggerFlag->at(iMuon) == 1 && recoMuonIsolation->at(iMuon) < Mu1IsoThreshold && passMuonID && passDXYDZ) 
          if (recoMuonTriggerFlag->at(iMuon) == 1 && recoMuonIsolation->at(iMuon) < Mu1IsoThreshold && passMuonID) 
          {
              Mu1.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              double recoMuonMass = Mu1.M();

              if (isMC)
              {
                  double rng = gRandom->Rndm();
                  rochesterSF = rc.kSmearMC(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonNTrackerLayers->at(iMuon), rng, muonScaleSyst, errorMember);
              } // end if isMC == true

              else{
                  rochesterSF = rc.kScaleDT(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), muonScaleSyst, errorMember);
              } // end if isMC == false (data)

              Mu1.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);
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
          //bool passDXYDZ = fabs(recoMuonDXY->at(iMuon)) < 0.2 && fabs(recoMuonDZ->at(iMuon)) < 0.5;

          if (iMuon == indexMu1) continue;
          //if ((!invertedMu2Iso && recoMuonIsolation->at(iMuon) > Mu2IsoThreshold) || (invertedMu2Iso && recoMuonIsolation->at(iMuon) < Mu2IsoThreshold) || (invertedMu2Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID || !passDXYDZ) continue;
          if ((!invertedMu2Iso && recoMuonIsolation->at(iMuon) > Mu2IsoThreshold) || (invertedMu2Iso && recoMuonIsolation->at(iMuon) < Mu2IsoThreshold) || (invertedMu2Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID) continue;

          TLorentzVector Mu2Cand; // prepare this variable for dR(Mu1,Mu2) implementation
          Mu2Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          double recoMuonMass = Mu2Cand.M();

          if (isMC)
          {
              double rng = gRandom->Rndm();
              rochesterSF = rc.kSmearMC(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonNTrackerLayers->at(iMuon), rng, muonScaleSyst, errorMember);
          } // end if isMC == true

          else{
              rochesterSF = rc.kScaleDT(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), muonScaleSyst, errorMember);
          } // end if isMC == false (data)

          Mu2Cand.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);

          if((Mu1.DeltaR(Mu2Cand) < smallestDR) && (recoMuonPDGId->at(indexMu1) == (-1) * recoMuonPDGId->at(iMuon)) && ((Mu1+Mu2Cand).M() > diMuonMassLowThreshold) && ((Mu1+Mu2Cand).M() < diMuonMassHighThreshold))
          {
              Mu2.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);
              Mu2Iso = recoMuonIsolation->at(iMuon);
              smallestDR = Mu1.DeltaR(Mu2);
              indexMu2 = iMuon;
              findMu2 = true;
          } // end if pair candidates
      } // end loop for mu2

      if (!findMu2) continue;

      // ---- 2mu channel ---
      bool findMuMuPair = false;
      // ------- start loop on the second muon pair candidates -------
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
          bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
          bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
          bool passMuonID = isLoose || isMedium || isTight;
          //bool passDXYDZ = fabs(recoMuonDXY->at(iMuon)) < 0.2 && fabs(recoMuonDZ->at(iMuon)) < 0.5;

          if (iMuon == indexMu1 || iMuon == indexMu2) continue;
          //if ((!invertedMu4Iso && recoMuonIsolation->at(iMuon) > Mu4IsoThreshold) || (invertedMu4Iso && recoMuonIsolation->at(iMuon) < Mu4IsoThreshold) || (invertedMu4Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID || !passDXYDZ) continue;
          if ((!invertedMu4Iso && recoMuonIsolation->at(iMuon) > Mu4IsoThreshold) || (invertedMu4Iso && recoMuonIsolation->at(iMuon) < Mu4IsoThreshold) || (invertedMu4Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID) continue;
          
          TLorentzVector Mu4Cand;
          Mu4Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          //bool qcdVeto = (recoMuonPDGId->at(indexMu1) != recoMuonPDGId->at(iMuon) && (Mu1+Mu4Cand).M() > 12.0) || (recoMuonPDGId->at(indexMu2) != recoMuonPDGId->at(iMuon) && (Mu2+Mu4Cand).M() > 12.0);
          //if (!qcdVeto) continue;

          // ---- bjet veto for Mu4 ---
          //bool bjetVeto = false;
          //for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
          //{
          //    TLorentzVector Jet;
          //    Jet.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
          //    if (Mu4Cand.DeltaR(Jet) < 0.4 && recoJetCSV->at(iJet) > 0.5426)
          //    {
          //        bjetVeto = true;
          //        break;
          //    } // end if bjet veto
          //} // end for loop over the reco-jets
          //if (bjetVeto) continue;

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
              //bool passDXYDZ = fabs(recoMuonDXY->at(iMuon3)) < 0.2 && fabs(recoMuonDZ->at(iMuon3)) < 0.5;

              if (iMuon3 == indexMu1 || iMuon3 == indexMu2 || iMuon3 == iMuon) continue;
              //if ((!invertedMu3Iso && recoMuonIsolation->at(iMuon3) > Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon3) < Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon3) > MuIsoUpperBound) || !passMuonID || !passDXYDZ) continue;
              if ((!invertedMu3Iso && recoMuonIsolation->at(iMuon3) > Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon3) < Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon3) > MuIsoUpperBound) || !passMuonID) continue;

              TLorentzVector Mu3Cand; // prepare this variable for dR(Mu3, Mu4) implementation
              Mu3Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon3), recoMuonEta->at(iMuon3), recoMuonPhi->at(iMuon3), recoMuonEnergy->at(iMuon3));
              //bool qcdVeto = (recoMuonPDGId->at(indexMu1) != recoMuonPDGId->at(iMuon3) && (Mu1+Mu3Cand).M() > 12.0) || (recoMuonPDGId->at(indexMu2) != recoMuonPDGId->at(iMuon3) && (Mu2+Mu3Cand).M() > 12.0);
              //if (!qcdVeto) continue;

              // ---- bjet veto for Mu3 ---
              //bool bjetVeto = false;
              //for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
              //{
              //    TLorentzVector Jet;
              //    Jet.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
              //    if (Mu3Cand.DeltaR(Jet) < 0.4 && recoJetCSV->at(iJet) > 0.5426)
              //    {
              //        bjetVeto = true;
              //        break;
              //    } // end if bjet veto
              //} // end for loop over the reco-jets
              //if (bjetVeto) continue;

              //if ((Mu4.DeltaR(Mu3Cand) < smallestDR) && (recoMuonPDGId->at(iMuon3) == (-1) * recoMuonPDGId->at(iMuon)) && ((Mu4+Mu3Cand).M() < 60.0) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4))
              if ((Mu4.DeltaR(Mu3Cand) < smallestDR) && (recoMuonPDGId->at(iMuon3) == (-1) * recoMuonPDGId->at(iMuon)) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4))
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

              // ----- fill flat trees -----
              invMassMu1Mu2_mm = (Mu1+Mu2).M();
              visMassMu3Mu4_mm = (Mu3+Mu4).M();
              visMass4Mu_mm = (Mu1+Mu2+Mu3+Mu4).M();
              
              deltaRMu1Mu2_mm = Mu1.DeltaR(Mu2);
              deltaRMu3Mu4_mm = Mu3.DeltaR(Mu4);

              mu1Pt_mm = Mu1.Pt();
              mu1Eta_mm = Mu1.Eta();
              mu1Phi_mm = Mu1.Phi();
              mu1Mass_mm = Mu1.M();

              mu2Pt_mm = Mu2.Pt();
              mu2Eta_mm = Mu2.Eta();
              mu2Phi_mm = Mu2.Phi();
              mu2Mass_mm = Mu2.M();

              mu3Pt_mm = Mu3.Pt();
              mu3Eta_mm = Mu3.Eta();
              mu3Phi_mm = Mu3.Phi();
              mu3Mass_mm = Mu3.M();

              mu4Pt_mm = Mu4.Pt();
              mu4Eta_mm = Mu4.Eta();
              mu4Phi_mm = Mu4.Phi();
              mu4Mass_mm = Mu4.M();
              
              eventWeight_mm = weight/summedWeights;
              Tree2Mu->Fill();
              break;
          } // end if findMu3
      } // end loop for Mu4

      if (findMuMuPair) continue;

      // ---- mue channel ---
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

          // ---- bjet veto for electron ---
          //bool bjetVeto = false;
          //for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
          //{
          //    TLorentzVector Jet;
          //    Jet.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
          //    if (EleCand.DeltaR(Jet) < 0.4 && recoJetCSV->at(iJet) > 0.5426)
          //    {
          //        bjetVeto = true;
          //        break;
          //    } // end if bjet veto
          //} // end for loop over the reco-jets
          //if (bjetVeto) continue;

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
              //bool passDXYDZ = fabs(recoMuonDXY->at(iMuon)) < 0.2 && fabs(recoMuonDZ->at(iMuon)) < 0.5;

              if (iMuon == indexMu1 || iMuon == indexMu2) continue;
              //if ((!invertedMu3Iso && recoMuonIsolation->at(iMuon) > Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon) < Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID || !passDXYDZ) continue;
              if ((!invertedMu3Iso && recoMuonIsolation->at(iMuon) > Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon) < Mu3IsoThreshold) || (invertedMu3Iso && recoMuonIsolation->at(iMuon) > MuIsoUpperBound) || !passMuonID) continue;

              TLorentzVector Mu3Cand; // prepare this variable for dR(Mu3, electron) implementation
              Mu3Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              //bool qcdVeto = (recoMuonPDGId->at(indexMu1) != recoMuonPDGId->at(iMuon) && (Mu1+Mu3Cand).M() > 12.0) || (recoMuonPDGId->at(indexMu2) != recoMuonPDGId->at(iMuon) && (Mu2+Mu3Cand).M() > 12.0);
              //if (!qcdVeto) continue;

              // ---- bjet veto for Mu3 ---
              //bool bjetVeto = false;
              //for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
              //{
              //    TLorentzVector Jet;
              //    Jet.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
              //    if (Mu3Cand.DeltaR(Jet) < 0.4 && recoJetCSV->at(iJet) > 0.5426)
              //    {
              //        bjetVeto = true;
              //        break;
              //    } // end if bjet veto
              //} // end for loop over the reco-jets
              //if (bjetVeto) continue;

              bool overlapMuEle = recoMuonRefToElectron->at(iMuon) > 0 && recoElectronRefToMuon->at(iEle) > 0 && recoMuonRefToElectron->at(iMuon) == recoElectronRefToMuon->at(iEle);

              //if ((Ele.DeltaR(Mu3Cand) < smallestDR) && (recoElectronPDGId->at(iEle)/fabs(recoElectronPDGId->at(iEle)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))) && ((Ele+Mu3Cand).M() < 60.0) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4) && !overlapMuEle)
              if ((Ele.DeltaR(Mu3Cand) < smallestDR) && (recoElectronPDGId->at(iEle)/fabs(recoElectronPDGId->at(iEle)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4) && !overlapMuEle)
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

              // ----- fill flat trees -----
              invMassMu1Mu2_me = (Mu1+Mu2).M();
              visMassMu3Ele_me = (Mu3+Ele).M();
              visMass3MuEle_me = (Mu1+Mu2+Mu3+Ele).M();

              deltaRMu1Mu2_me = Mu1.DeltaR(Mu2);
              deltaRMu3Ele_me = Mu3.DeltaR(Ele);

              mu1Pt_me = Mu1.Pt();
              mu1Eta_me = Mu1.Eta();
              mu1Phi_me = Mu1.Phi();
              mu1Mass_me = Mu1.M();

              mu2Pt_me = Mu2.Pt();
              mu2Eta_me = Mu2.Eta();
              mu2Phi_me = Mu2.Phi();
              mu2Mass_me = Mu2.M();

              mu3Pt_me = Mu3.Pt();
              mu3Eta_me = Mu3.Eta();
              mu3Phi_me = Mu3.Phi();
              mu3Mass_me = Mu3.M();

              elePt_me = Ele.Pt();
              eleEta_me = Ele.Eta();
              elePhi_me = Ele.Phi();
              eleMass_me = Ele.M();

              eventWeight_me = weight/summedWeights; 
              TreeMuEle->Fill();
              break;
          } // end if findMu3
      } // end loop for electron

      if (findMuElePair) continue;

      // ---- mutau channel ---
      bool findMuTauPair = false;

      // ------- start loop on tau candidates -------
      for (unsigned int iTau=0; iTau<recoTauMuonCleanedPt->size(); iTau++)
      {
          if (deepTauID && recoTauMuonCleanedDeepVSjetraw->size() > 0)
          {
              // -------------------------------------------------------------------------------
              bool condTauDeepVSeLoose = deepTauVSele == "LOOSE" && recoTauMuonCleanedDeepVSeLoose->at(iTau)>0;
              bool condTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauMuonCleanedDeepVSjetLoose->at(iTau)>0;
              bool condTauDeepVSmuLoose = deepTauVSmu == "LOOSE" && recoTauMuonCleanedDeepVSmuLoose->at(iTau)>0;

              bool condTauDeepVSeMedium = deepTauVSele == "MEDIUM" && recoTauMuonCleanedDeepVSeMedium->at(iTau)>0;
              bool condTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauMuonCleanedDeepVSjetMedium->at(iTau)>0;
              bool condTauDeepVSmuMedium = deepTauVSmu == "MEDIUM" && recoTauMuonCleanedDeepVSmuMedium->at(iTau)>0;

              bool condTauDeepVSeTight = deepTauVSele == "TIGHT" && recoTauMuonCleanedDeepVSeTight->at(iTau)>0;
              bool condTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauMuonCleanedDeepVSjetTight->at(iTau)>0;
              bool condTauDeepVSmuTight = deepTauVSmu == "TIGHT" && recoTauMuonCleanedDeepVSmuTight->at(iTau)>0;

              bool condTauDeepVSeVLoose = deepTauVSele == "VLOOSE" && recoTauMuonCleanedDeepVSeVLoose->at(iTau)>0;
              bool condTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauMuonCleanedDeepVSjetVLoose->at(iTau)>0;
              bool condTauDeepVSmuVLoose = deepTauVSmu == "VLOOSE" && recoTauMuonCleanedDeepVSmuVLoose->at(iTau)>0;

              bool condTauDeepVSeVTight = deepTauVSele == "VTIGHT" && recoTauMuonCleanedDeepVSeVTight->at(iTau)>0;
              bool condTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauMuonCleanedDeepVSjetVTight->at(iTau)>0;

              bool condTauDeepVSeVVLoose = deepTauVSele == "VVLOOSE" && recoTauMuonCleanedDeepVSeVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauMuonCleanedDeepVSjetVVLoose->at(iTau)>0;
              
              bool condTauDeepVSeVVTight = deepTauVSele == "VVTIGHT" && recoTauMuonCleanedDeepVSeVVTight->at(iTau)>0;
              bool condTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauMuonCleanedDeepVSjetVVTight->at(iTau)>0;

              bool condTauDeepVSeVVVLoose = deepTauVSele == "VVVLOOSE" && recoTauMuonCleanedDeepVSeVVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVVLoose = deepTauVSjet == "VVVLOOSE" && recoTauMuonCleanedDeepVSjetVVVLoose->at(iTau)>0;

              bool condTauDeepVSeNull = deepTauVSele != "LOOSE" && deepTauVSele != "MEDIUM" && deepTauVSele != "TIGHT" && deepTauVSele != "VLOOSE" && deepTauVSele != "VTIGHT" && deepTauVSele != "VVLOOSE" && deepTauVSele != "VVTIGHT" && deepTauVSele != "VVVLOOSE";
              bool condTauDeepVSmuNull = deepTauVSmu != "LOOSE" && deepTauVSmu != "MEDIUM" && deepTauVSmu != "TIGHT" && deepTauVSmu != "VLOOSE";
              // -------------------------------------------------------------------------------

              bool passCondTauDeepVSele = (condTauDeepVSeLoose || condTauDeepVSeMedium || condTauDeepVSeTight || condTauDeepVSeVLoose || condTauDeepVSeVTight || condTauDeepVSeVVLoose || condTauDeepVSeVVTight || condTauDeepVSeVVVLoose || condTauDeepVSeNull);
              bool passCondTauDeepVSjet = (condTauDeepVSjetLoose || condTauDeepVSjetMedium || condTauDeepVSjetTight || condTauDeepVSjetVLoose || condTauDeepVSjetVTight || condTauDeepVSjetVVLoose || condTauDeepVSjetVVTight || condTauDeepVSjetVVVLoose);
              bool passCondTauDeepVSmu = (condTauDeepVSmuLoose || condTauDeepVSmuMedium || condTauDeepVSmuTight || condTauDeepVSmuVLoose || condTauDeepVSmuNull);

              bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;

              // -------------------- inverted deep Tau ID -----------------------------
              bool condInvertTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauMuonCleanedDeepVSjetLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauMuonCleanedDeepVSjetMedium->at(iTau)<=0;
              bool condInvertTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauMuonCleanedDeepVSjetTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauMuonCleanedDeepVSjetVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauMuonCleanedDeepVSjetVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauMuonCleanedDeepVSjetVVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauMuonCleanedDeepVSjetVVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVVLoose = recoTauMuonCleanedDeepVSjetVVVLoose->at(iTau)>0;
              // -------------------------------------------------------------------------------

              bool passCondInvertTauDeepVSjet = ((condInvertTauDeepVSjetLoose || condInvertTauDeepVSjetMedium || condInvertTauDeepVSjetTight || condInvertTauDeepVSjetVLoose || condInvertTauDeepVSjetVTight || condInvertTauDeepVSjetVVLoose || condInvertTauDeepVSjetVVTight) && condInvertTauDeepVSjetVVVLoose && passCondTauDeepVSele && passCondTauDeepVSmu);
              // -------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauDeep) || (invertedTauIso && !passCondInvertTauDeepVSjet)) continue;
          } // end if deepTauID && recoTauMuonCleanedDeepVSjetraw->size() > 0

          else{
              bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauMuonCleanedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauMuonCleanedIsoMVAVVLoose->at(iTau)>0;
              bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauMuonCleanedIsoMVAVLoose->at(iTau)>0;
              bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauMuonCleanedIsoMVALoose->at(iTau)>0;
              bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauMuonCleanedIsoMVAMedium->at(iTau)>0;
              bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauMuonCleanedIsoMVATight->at(iTau)>0;
              bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauMuonCleanedIsoMVAVTight->at(iTau)>0;
              bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauMuonCleanedIsoMVAVVTight->at(iTau)>0;

              bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight);
              // -------------------------------------------------------------------------------------------------

              bool condInvertTauMVARaw = recoTauMuonCleanedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condInvertTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauMuonCleanedIsoMVAVVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauMuonCleanedIsoMVAVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauMuonCleanedIsoMVALoose->at(iTau)<=0;
              bool condInvertTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauMuonCleanedIsoMVAMedium->at(iTau)<=0;
              bool condInvertTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauMuonCleanedIsoMVATight->at(iTau)<=0;
              bool condInvertTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauMuonCleanedIsoMVAVTight->at(iTau)<=0;
              bool condInvertTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauMuonCleanedIsoMVAVVTight->at(iTau)<=0;

              // ------ always require tau candidates pass vvvloose MVA id in order to have similar dynamic shape as real tau
              bool passCondInvertTauMVA = (condInvertTauMVARaw && (condInvertTauMVAWPVVLoose || condInvertTauMVAWPVLoose || condInvertTauMVAWPLoose || condInvertTauMVAWPMedium || condInvertTauMVAWPTight || condInvertTauMVAWPVTight || condInvertTauMVAWPVVTight));
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauMuonCleanedAntiMuMVALoose->at(iTau)>0;
              bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauMuonCleanedAntiMuMVATight->at(iTau)>0; 
              bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

              bool passCondTauAntiMuMVA = (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull);
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauMuonCleanedAntiEleMVALoose->at(iTau)>0;
              bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauMuonCleanedAntiEleMVAMedium->at(iTau)>0;
              bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauMuonCleanedAntiEleMVATight->at(iTau)>0; 
              bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

              bool passCondTauAntiEleMVA = (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull);
              // -------------------------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauMVA) || (invertedTauIso && !passCondInvertTauMVA) || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
          } // end if !deepTauID (tauMVAID)

          TLorentzVector TauCand;
          TauCand.SetPtEtaPhiE(recoTauMuonCleanedPt->at(iTau), recoTauMuonCleanedEta->at(iTau), recoTauMuonCleanedPhi->at(iTau), recoTauMuonCleanedEnergy->at(iTau));
          double recoTauMuonCleanedMass = TauCand.M();
          TauCand.SetPtEtaPhiM(recoTauMuonCleanedPt->at(iTau)*tauScaleCorr, recoTauMuonCleanedEta->at(iTau), recoTauMuonCleanedPhi->at(iTau), recoTauMuonCleanedMass);

          if (TauCand.DeltaR(Mu1) < 0.8 || TauCand.DeltaR(Mu2) < 0.8) continue;

          // ---- bjet veto for tau ---
          //bool bjetVeto = false;
          //for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
          //{
          //    TLorentzVector Jet;
          //    Jet.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
          //    if (TauCand.DeltaR(Jet) < 0.4 && recoJetCSV->at(iJet) > 0.5426)
          //    {
          //        bjetVeto = true;
          //        break;
          //    } // end if bjet veto
          //} // end for loop over the reco-jets
          //if (bjetVeto) continue;

          if ((recoTauMuonCleanedDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
          Tau.SetPtEtaPhiM(recoTauMuonCleanedPt->at(iTau)*tauScaleCorr, recoTauMuonCleanedEta->at(iTau), recoTauMuonCleanedPhi->at(iTau), recoTauMuonCleanedMass);
          TauIso = deepTauID ? recoTauMuonCleanedDeepVSjetraw->at(iTau) : recoTauMuonCleanedIsoMVArawValue->at(iTau);
          TauDM = recoTauMuonCleanedDecayMode->at(iTau);

          float smallestDR = 0.8; // dR cut between Mu3 and tau
          bool findMu3 = false;

          for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
          {
              bool isLoose = MuonId == "LOOSE" && recoMuonIdLoose->at(iMuon) > 0;
              bool isMedium = MuonId == "MEDIUM" && recoMuonIdMedium->at(iMuon) > 0;
              bool isTight = MuonId == "TIGHT" && recoMuonIdTight->at(iMuon) > 0;
              bool passMuonID = isLoose || isMedium || isTight;
              //bool passDXYDZ = fabs(recoMuonDXY->at(iMuon)) < 0.2 && fabs(recoMuonDZ->at(iMuon)) < 0.5;

              if (iMuon == indexMu1 || iMuon == indexMu2) continue;
              //if (!passMuonID || !passDXYDZ) continue;
              if (!passMuonID) continue;

              TLorentzVector Mu3Cand; // prepare this variable for dR(Mu3, tau) implementation
              Mu3Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              double recoMuonMass = Mu3Cand.M();

              if (isMC)
              {
                  double rng = gRandom->Rndm();
                  rochesterSF = rc.kSmearMC(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonNTrackerLayers->at(iMuon), rng, muonScaleSyst, errorMember);
              } // end if isMC == true

              else{
                  rochesterSF = rc.kScaleDT(recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)), recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), muonScaleSyst, errorMember);
              } // end if isMC == false (data)

              Mu3Cand.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);

              bool overlapMuTau = recoMuonRefToTauMuonCleaned->at(iMuon) > 0 && recoTauMuonCleanedRefToMuon->at(iTau) > 0 && recoMuonRefToTauMuonCleaned->at(iMuon) == recoTauMuonCleanedRefToMuon->at(iTau);

              //if ((Tau.DeltaR(Mu3Cand) < smallestDR) && (recoTauMuonCleanedPDGId->at(iTau)/fabs(recoTauMuonCleanedPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))) && ((Tau+Mu3Cand).M() < 60.0) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4) && !overlapMuTau)
              if ((Tau.DeltaR(Mu3Cand) < smallestDR) && (recoTauMuonCleanedPDGId->at(iTau)/fabs(recoTauMuonCleanedPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))) && (Mu3Cand.DeltaR(Mu1) > 0.4) && (Mu3Cand.DeltaR(Mu2) > 0.4) && !overlapMuTau)
              {
                  Mu3.SetPtEtaPhiM(recoMuonPt->at(iMuon)*rochesterSF, recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonMass);
                  Mu3Iso = recoMuonIsolation->at(iMuon); 
                  smallestDR = Tau.DeltaR(Mu3);
                  findMu3 = true;
              } // end if find mu3 with tau matched
          } // end loop for mu3

          if (!findMu3) continue;
          else{
              findMuTauPair = true;

              // ----- fill flat trees -----
              invMassMu1Mu2_mt = (Mu1+Mu2).M();
              visMassMu3Tau_mt = (Mu3+Tau).M();
              visMass3MuTau_mt = (Mu1+Mu2+Mu3+Tau).M();

              deltaRMu1Mu2_mt = Mu1.DeltaR(Mu2);
              deltaRMu3Tau_mt = Mu3.DeltaR(Tau);

              mu1Pt_mt = Mu1.Pt();
              mu1Eta_mt = Mu1.Eta();
              mu1Phi_mt = Mu1.Phi();
              mu1Mass_mt = Mu1.M();

              mu2Pt_mt = Mu2.Pt();
              mu2Eta_mt = Mu2.Eta();
              mu2Phi_mt = Mu2.Phi();
              mu2Mass_mt = Mu2.M();

              mu3Pt_mt = Mu3.Pt();
              mu3Eta_mt = Mu3.Eta();
              mu3Phi_mt = Mu3.Phi();
              mu3Mass_mt = Mu3.M();

              tauPt_mt = Tau.Pt();
              tauEta_mt = Tau.Eta();
              tauPhi_mt = Tau.Phi();
              tauMass_mt = Tau.M();
              tauDisc_mt = TauIso;
              tauDM_mt = TauDM;

              eventWeight_mt = weight/summedWeights;
              TreeMuTau->Fill();
              break;
          } // end if findMu3
      } // end loop for tau

      if (findMuTauPair) continue;
      
      // ---- etau channel ---
      bool findEleTauPair = false;

      // ------- start loop on tau candidates -------
      for (unsigned int iTau=0; iTau<recoTauElectronCleanedPt->size(); iTau++)
      {
          if (deepTauID && recoTauElectronCleanedDeepVSjetraw->size() > 0)
          {
              // -------------------------------------------------------------------------------
              bool condTauDeepVSeLoose = deepTauVSele == "LOOSE" && recoTauElectronCleanedDeepVSeLoose->at(iTau)>0;
              bool condTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauElectronCleanedDeepVSjetLoose->at(iTau)>0;
              bool condTauDeepVSmuLoose = deepTauVSmu == "LOOSE" && recoTauElectronCleanedDeepVSmuLoose->at(iTau)>0;

              bool condTauDeepVSeMedium = deepTauVSele == "MEDIUM" && recoTauElectronCleanedDeepVSeMedium->at(iTau)>0;
              bool condTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauElectronCleanedDeepVSjetMedium->at(iTau)>0;
              bool condTauDeepVSmuMedium = deepTauVSmu == "MEDIUM" && recoTauElectronCleanedDeepVSmuMedium->at(iTau)>0;

              bool condTauDeepVSeTight = deepTauVSele == "TIGHT" && recoTauElectronCleanedDeepVSeTight->at(iTau)>0;
              bool condTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauElectronCleanedDeepVSjetTight->at(iTau)>0;
              bool condTauDeepVSmuTight = deepTauVSmu == "TIGHT" && recoTauElectronCleanedDeepVSmuTight->at(iTau)>0;

              bool condTauDeepVSeVLoose = deepTauVSele == "VLOOSE" && recoTauElectronCleanedDeepVSeVLoose->at(iTau)>0;
              bool condTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauElectronCleanedDeepVSjetVLoose->at(iTau)>0;
              bool condTauDeepVSmuVLoose = deepTauVSmu == "VLOOSE" && recoTauElectronCleanedDeepVSmuVLoose->at(iTau)>0;

              bool condTauDeepVSeVTight = deepTauVSele == "VTIGHT" && recoTauElectronCleanedDeepVSeVTight->at(iTau)>0;
              bool condTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauElectronCleanedDeepVSjetVTight->at(iTau)>0;

              bool condTauDeepVSeVVLoose = deepTauVSele == "VVLOOSE" && recoTauElectronCleanedDeepVSeVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauElectronCleanedDeepVSjetVVLoose->at(iTau)>0;
              
              bool condTauDeepVSeVVTight = deepTauVSele == "VVTIGHT" && recoTauElectronCleanedDeepVSeVVTight->at(iTau)>0;
              bool condTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauElectronCleanedDeepVSjetVVTight->at(iTau)>0;

              bool condTauDeepVSeVVVLoose = deepTauVSele == "VVVLOOSE" && recoTauElectronCleanedDeepVSeVVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVVLoose = deepTauVSjet == "VVVLOOSE" && recoTauElectronCleanedDeepVSjetVVVLoose->at(iTau)>0;

              bool condTauDeepVSeNull = deepTauVSele != "LOOSE" && deepTauVSele != "MEDIUM" && deepTauVSele != "TIGHT" && deepTauVSele != "VLOOSE" && deepTauVSele != "VTIGHT" && deepTauVSele != "VVLOOSE" && deepTauVSele != "VVTIGHT" && deepTauVSele != "VVVLOOSE";
              bool condTauDeepVSmuNull = deepTauVSmu != "LOOSE" && deepTauVSmu != "MEDIUM" && deepTauVSmu != "TIGHT" && deepTauVSmu != "VLOOSE";
              // -------------------------------------------------------------------------------

              bool passCondTauDeepVSele = (condTauDeepVSeLoose || condTauDeepVSeMedium || condTauDeepVSeTight || condTauDeepVSeVLoose || condTauDeepVSeVTight || condTauDeepVSeVVLoose || condTauDeepVSeVVTight || condTauDeepVSeVVVLoose || condTauDeepVSeNull);
              bool passCondTauDeepVSjet = (condTauDeepVSjetLoose || condTauDeepVSjetMedium || condTauDeepVSjetTight || condTauDeepVSjetVLoose || condTauDeepVSjetVTight || condTauDeepVSjetVVLoose || condTauDeepVSjetVVTight || condTauDeepVSjetVVVLoose);
              bool passCondTauDeepVSmu = (condTauDeepVSmuLoose || condTauDeepVSmuMedium || condTauDeepVSmuTight || condTauDeepVSmuVLoose || condTauDeepVSmuNull);

              bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;

              // -------------------- inverted deep Tau ID -----------------------------
              bool condInvertTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauElectronCleanedDeepVSjetLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauElectronCleanedDeepVSjetMedium->at(iTau)<=0;
              bool condInvertTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauElectronCleanedDeepVSjetTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauElectronCleanedDeepVSjetVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauElectronCleanedDeepVSjetVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauElectronCleanedDeepVSjetVVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauElectronCleanedDeepVSjetVVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVVLoose = recoTauElectronCleanedDeepVSjetVVVLoose->at(iTau)>0;
              // -------------------------------------------------------------------------------

              bool passCondInvertTauDeepVSjet = ((condInvertTauDeepVSjetLoose || condInvertTauDeepVSjetMedium || condInvertTauDeepVSjetTight || condInvertTauDeepVSjetVLoose || condInvertTauDeepVSjetVTight || condInvertTauDeepVSjetVVLoose || condInvertTauDeepVSjetVVTight) && condInvertTauDeepVSjetVVVLoose && passCondTauDeepVSele && passCondTauDeepVSmu);
              // -------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauDeep) || (invertedTauIso && !passCondInvertTauDeepVSjet)) continue;
          } // end if deepTauID && recoTauElectronCleanedDeepVSjetraw->size() > 0

          else{
              bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauElectronCleanedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauElectronCleanedIsoMVAVVLoose->at(iTau)>0;
              bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauElectronCleanedIsoMVAVLoose->at(iTau)>0;
              bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauElectronCleanedIsoMVALoose->at(iTau)>0;
              bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauElectronCleanedIsoMVAMedium->at(iTau)>0;
              bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauElectronCleanedIsoMVATight->at(iTau)>0;
              bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauElectronCleanedIsoMVAVTight->at(iTau)>0;
              bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauElectronCleanedIsoMVAVVTight->at(iTau)>0;

              bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight);
              // -------------------------------------------------------------------------------------------------

              bool condInvertTauMVARaw = recoTauElectronCleanedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condInvertTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauElectronCleanedIsoMVAVVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauElectronCleanedIsoMVAVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauElectronCleanedIsoMVALoose->at(iTau)<=0;
              bool condInvertTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauElectronCleanedIsoMVAMedium->at(iTau)<=0;
              bool condInvertTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauElectronCleanedIsoMVATight->at(iTau)<=0;
              bool condInvertTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauElectronCleanedIsoMVAVTight->at(iTau)<=0;
              bool condInvertTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauElectronCleanedIsoMVAVVTight->at(iTau)<=0;

              // ------ always require tau candidates pass vvvloose MVA id in order to have similar dynamic shape as real tau
              bool passCondInvertTauMVA = (condInvertTauMVARaw && (condInvertTauMVAWPVVLoose || condInvertTauMVAWPVLoose || condInvertTauMVAWPLoose || condInvertTauMVAWPMedium || condInvertTauMVAWPTight || condInvertTauMVAWPVTight || condInvertTauMVAWPVVTight));
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauElectronCleanedAntiMuMVALoose->at(iTau)>0;
              bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauElectronCleanedAntiMuMVATight->at(iTau)>0; 
              bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

              bool passCondTauAntiMuMVA = (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull);
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauElectronCleanedAntiEleMVALoose->at(iTau)>0;
              bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauElectronCleanedAntiEleMVAMedium->at(iTau)>0;
              bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauElectronCleanedAntiEleMVATight->at(iTau)>0; 
              bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

              bool passCondTauAntiEleMVA = (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull);
              // -------------------------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauMVA) || (invertedTauIso && !passCondInvertTauMVA) || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
          } // end if !deepTauID (tauMVAID)

          TLorentzVector TauCand;
          TauCand.SetPtEtaPhiE(recoTauElectronCleanedPt->at(iTau), recoTauElectronCleanedEta->at(iTau), recoTauElectronCleanedPhi->at(iTau), recoTauElectronCleanedEnergy->at(iTau));
          double recoTauElectronCleanedMass = TauCand.M();
          TauCand.SetPtEtaPhiM(recoTauElectronCleanedPt->at(iTau)*tauScaleCorr, recoTauElectronCleanedEta->at(iTau), recoTauElectronCleanedPhi->at(iTau), recoTauElectronCleanedMass);

          if (TauCand.DeltaR(Mu1) < 0.8 || TauCand.DeltaR(Mu2) < 0.8) continue;

          // ---- bjet veto for tau ---
          //bool bjetVeto = false;
          //for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
          //{
          //    TLorentzVector Jet;
          //    Jet.SetPtEtaPhiE(recoJetPt->at(iJet), recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet));
          //    if (TauCand.DeltaR(Jet) < 0.4 && recoJetCSV->at(iJet) > 0.5426)
          //    {
          //        bjetVeto = true;
          //        break;
          //    } // end if bjet veto
          //} // end for loop over the reco-jets
          //if (bjetVeto) continue;

          if ((recoTauElectronCleanedDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
          Tau.SetPtEtaPhiM(recoTauElectronCleanedPt->at(iTau)*tauScaleCorr, recoTauElectronCleanedEta->at(iTau), recoTauElectronCleanedPhi->at(iTau), recoTauElectronCleanedMass);
          TauIso = deepTauID ? recoTauElectronCleanedDeepVSjetraw->at(iTau) : recoTauElectronCleanedIsoMVArawValue->at(iTau);
          TauDM = recoTauElectronCleanedDecayMode->at(iTau);

          float smallestDR = 0.8; // dR cut between electron and tau
          bool findEle = false;

          for (unsigned int iEle=0; iEle<recoElectronPt->size(); iEle++)
          {
              bool condEleLoose = EleRelId == "LOOSE" && recoElectronIdLooseNoIso->at(iEle) > 0;
              bool condEleMedium = EleRelId == "MEDIUM" && recoElectronIdMediumNoIso->at(iEle) > 0;
              bool condEleTight = EleRelId == "TIGHT" && recoElectronIdTightNoIso->at(iEle) > 0;
              bool condEleNull = EleRelId != "LOOSE" && EleRelId != "MEDIUM" && EleRelId != "TIGHT";
              bool passCondEleId = condEleLoose || condEleMedium || condEleTight || condEleNull;

              if (!passCondEleId) continue;

              TLorentzVector EleCand; // prepare this variable for dR(Ele, tau) implementation
              EleCand.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEnergy->at(iEle));
              double recoElectronMass = EleCand.M();
              double recoElectronPtCorr = recoElectronPt->at(iEle);
              
              if (electronScaleSyst == 0) recoElectronPtCorr = recoElectronPt->at(iEle) * recoElectronEcalTrkEnergyPostCorr->at(iEle) / recoElectronEnergy->at(iEle);
              if (electronScaleSyst == 1) recoElectronPtCorr = recoElectronPt->at(iEle) * recoElectronEnergyScaleUp->at(iEle) / recoElectronEnergy->at(iEle); 
              if (electronScaleSyst == -1) recoElectronPtCorr = recoElectronPt->at(iEle) * recoElectronEnergyScaleDown->at(iEle) / recoElectronEnergy->at(iEle); 
              if (electronScaleSyst == 2) recoElectronPtCorr = recoElectronPt->at(iEle) * recoElectronEnergySigmaUp->at(iEle) / recoElectronEnergy->at(iEle); 
              if (electronScaleSyst == -2) recoElectronPtCorr = recoElectronPt->at(iEle) * recoElectronEnergySigmaDown->at(iEle) / recoElectronEnergy->at(iEle); 

              EleCand.SetPtEtaPhiM(recoElectronPtCorr, recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronMass);
              bool overlapEleTau = recoElectronRefToTauElectronCleaned->at(iEle) > 0 && recoTauElectronCleanedRefToElectron->at(iTau) > 0 && recoElectronRefToTauElectronCleaned->at(iEle) == recoTauElectronCleanedRefToElectron->at(iTau);

              //if ((Tau.DeltaR(EleCand) < smallestDR) && (recoTauElectronCleanedPDGId->at(iTau)/fabs(recoTauElectronCleanedPDGId->at(iTau)) == (-1) * recoElectronPDGId->at(iEle)/fabs(recoElectronPDGId->at(iEle))) && ((Tau+EleCand).M() < 60.0) && (EleCand.DeltaR(Mu1) > 0.4) && (EleCand.DeltaR(Mu2) > 0.4) && !overlapEleTau)
              if ((Tau.DeltaR(EleCand) < smallestDR) && (recoTauElectronCleanedPDGId->at(iTau)/fabs(recoTauElectronCleanedPDGId->at(iTau)) == (-1) * recoElectronPDGId->at(iEle)/fabs(recoElectronPDGId->at(iEle))) && (EleCand.DeltaR(Mu1) > 0.4) && (EleCand.DeltaR(Mu2) > 0.4) && !overlapEleTau)
              {
                  Ele.SetPtEtaPhiM(recoElectronPtCorr, recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronMass);
                  EleIso = recoElectronIsolation->at(iEle); 
                  smallestDR = Tau.DeltaR(Ele);
                  findEle = true;
              } // end if find electron with tau matched
          } // end loop for electron

          if (!findEle) continue;
          else{
              findEleTauPair = true;

              // ----- fill flat trees -----
              invMassMu1Mu2_et = (Mu1+Mu2).M();
              visMassEleTau_et = (Ele+Tau).M();
              visMass2MuEleTau_et = (Mu1+Mu2+Ele+Tau).M();

              deltaRMu1Mu2_et = Mu1.DeltaR(Mu2);
              deltaREleTau_et = Ele.DeltaR(Tau);

              mu1Pt_et = Mu1.Pt();
              mu1Eta_et = Mu1.Eta();
              mu1Phi_et = Mu1.Phi();
              mu1Mass_et = Mu1.M();

              mu2Pt_et = Mu2.Pt();
              mu2Eta_et = Mu2.Eta();
              mu2Phi_et = Mu2.Phi();
              mu2Mass_et = Mu2.M();

              elePt_et = Ele.Pt();
              eleEta_et = Ele.Eta();
              elePhi_et = Ele.Phi();
              eleMass_et = Ele.M();

              tauPt_et = Tau.Pt();
              tauEta_et = Tau.Eta();
              tauPhi_et = Tau.Phi();
              tauMass_et = Tau.M();
              tauDisc_et = TauIso;
              tauDM_et = TauDM;

              eventWeight_et = weight/summedWeights;
              TreeEleTau->Fill();
              break;
          } // end if findEle
      } // end loop for tau

      if (findEleTauPair) continue;

      // ---- tautau channel ---
      bool findTauTauPair = false;
      double highestPt = 0;

      // ------- start loop on jet (di-tau_h) candidates -------
      for (unsigned int iJet=0; iJet<recoJetPt->size(); iJet++)
      {
          if (boostDiTauOpt) break;
          bool condJetIdLoose = JetId == "LOOSE" && recoJetIdLoose->at(iJet) > 0;
          bool condJetIdTight = JetId == "TIGHT" && recoJetIdTight->at(iJet) > 0;
          bool condJetIdTightLepVeto = JetId == "TIGHTLEPVETO" && recoJetIdTightLepVeto->at(iJet) > 0;
          bool condJetIdNull = JetId != "LOOSE" && JetId != "TIGHT" && JetId != "TIGHTLEPVETO";
          bool condJetIdPU = recoJetIdPileUp->at(iJet) > 0;
          bool passCondJetId = ((condJetIdLoose || condJetIdTight || condJetIdTightLepVeto) && condJetIdPU) || condJetIdNull;

          if (!passCondJetId) continue;
          if (recoJetCSV->at(iJet) > 0.5426) continue; // bjet veto

          bool condDiTauDisc = (!massDecorrelation && recoJetDeepDiTauValue->at(iJet) > deepDiTauRawThreshold) || (massDecorrelation && recoJetDeepDiTauValueMD->at(iJet) > deepDiTauRawThreshold);
          bool condInvertDiTauDisc = (!massDecorrelation && recoJetDeepDiTauValue->at(iJet) < deepDiTauRawThreshold && recoJetDeepDiTauValue->at(iJet) > deepDiTauRawLowerBound) || (massDecorrelation && recoJetDeepDiTauValueMD->at(iJet) < deepDiTauRawThreshold && recoJetDeepDiTauValueMD->at(iJet) > deepDiTauRawLowerBound);

          if ((!invertedTauIso && !condDiTauDisc) || (invertedTauIso && !condInvertDiTauDisc)) continue;

          // ------ estimate JEC systematics ------
          table TableJESunc(jecSystFile);
          double jetEnergyCorr = 1 + jetScaleSyst * (TableJESunc.getEfficiency(recoJetPt->at(iJet), recoJetEta->at(iJet)));

          TLorentzVector TauCand;
          TauCand.SetPtEtaPhiE(recoJetPt->at(iJet) * jetEnergyCorr, recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet) * jetEnergyCorr);

          if (TauCand.DeltaR(Mu1) < 0.8 || TauCand.DeltaR(Mu2) < 0.8) continue;
          if (TauCand.Pt() > highestPt)
          {
              Tau.SetPtEtaPhiE(recoJetPt->at(iJet) * jetEnergyCorr, recoJetEta->at(iJet), recoJetPhi->at(iJet), recoJetEnergy->at(iJet) * jetEnergyCorr);
              TauIso = massDecorrelation ? recoJetDeepDiTauValueMD->at(iJet) : recoJetDeepDiTauValue->at(iJet);
              highestPt = Tau.Pt();
              findTauTauPair = true;
          } // end if highest pt
      } // end loop for jets containing tau candidates

      // ------- start loop on tau candidates -------
      for (unsigned int iTau=0; iTau<recoTauBoostedPt->size(); iTau++)
      {
          if (!boostDiTauOpt) break;
          if (deepTauID && recoTauBoostedDeepVSjetraw->size() > 0)
          {
              // -------------------------------------------------------------------------------
              bool condTauDeepVSeLoose = deepTauVSele == "LOOSE" && recoTauBoostedDeepVSeLoose->at(iTau)>0;
              bool condTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauBoostedDeepVSjetLoose->at(iTau)>0;
              bool condTauDeepVSmuLoose = deepTauVSmu == "LOOSE" && recoTauBoostedDeepVSmuLoose->at(iTau)>0;

              bool condTauDeepVSeMedium = deepTauVSele == "MEDIUM" && recoTauBoostedDeepVSeMedium->at(iTau)>0;
              bool condTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauBoostedDeepVSjetMedium->at(iTau)>0;
              bool condTauDeepVSmuMedium = deepTauVSmu == "MEDIUM" && recoTauBoostedDeepVSmuMedium->at(iTau)>0;

              bool condTauDeepVSeTight = deepTauVSele == "TIGHT" && recoTauBoostedDeepVSeTight->at(iTau)>0;
              bool condTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauBoostedDeepVSjetTight->at(iTau)>0;
              bool condTauDeepVSmuTight = deepTauVSmu == "TIGHT" && recoTauBoostedDeepVSmuTight->at(iTau)>0;

              bool condTauDeepVSeVLoose = deepTauVSele == "VLOOSE" && recoTauBoostedDeepVSeVLoose->at(iTau)>0;
              bool condTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauBoostedDeepVSjetVLoose->at(iTau)>0;
              bool condTauDeepVSmuVLoose = deepTauVSmu == "VLOOSE" && recoTauBoostedDeepVSmuVLoose->at(iTau)>0;

              bool condTauDeepVSeVTight = deepTauVSele == "VTIGHT" && recoTauBoostedDeepVSeVTight->at(iTau)>0;
              bool condTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauBoostedDeepVSjetVTight->at(iTau)>0;

              bool condTauDeepVSeVVLoose = deepTauVSele == "VVLOOSE" && recoTauBoostedDeepVSeVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauBoostedDeepVSjetVVLoose->at(iTau)>0;
              
              bool condTauDeepVSeVVTight = deepTauVSele == "VVTIGHT" && recoTauBoostedDeepVSeVVTight->at(iTau)>0;
              bool condTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauBoostedDeepVSjetVVTight->at(iTau)>0;

              bool condTauDeepVSeVVVLoose = deepTauVSele == "VVVLOOSE" && recoTauBoostedDeepVSeVVVLoose->at(iTau)>0;
              bool condTauDeepVSjetVVVLoose = deepTauVSjet == "VVVLOOSE" && recoTauBoostedDeepVSjetVVVLoose->at(iTau)>0;

              bool condTauDeepVSeNull = deepTauVSele != "LOOSE" && deepTauVSele != "MEDIUM" && deepTauVSele != "TIGHT" && deepTauVSele != "VLOOSE" && deepTauVSele != "VTIGHT" && deepTauVSele != "VVLOOSE" && deepTauVSele != "VVTIGHT" && deepTauVSele != "VVVLOOSE";
              bool condTauDeepVSmuNull = deepTauVSmu != "LOOSE" && deepTauVSmu != "MEDIUM" && deepTauVSmu != "TIGHT" && deepTauVSmu != "VLOOSE";
              // -------------------------------------------------------------------------------

              bool passCondTauDeepVSele = (condTauDeepVSeLoose || condTauDeepVSeMedium || condTauDeepVSeTight || condTauDeepVSeVLoose || condTauDeepVSeVTight || condTauDeepVSeVVLoose || condTauDeepVSeVVTight || condTauDeepVSeVVVLoose || condTauDeepVSeNull);
              bool passCondTauDeepVSjet = (condTauDeepVSjetLoose || condTauDeepVSjetMedium || condTauDeepVSjetTight || condTauDeepVSjetVLoose || condTauDeepVSjetVTight || condTauDeepVSjetVVLoose || condTauDeepVSjetVVTight || condTauDeepVSjetVVVLoose);
              bool passCondTauDeepVSmu = (condTauDeepVSmuLoose || condTauDeepVSmuMedium || condTauDeepVSmuTight || condTauDeepVSmuVLoose || condTauDeepVSmuNull);

              bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;

              // -------------------- inverted deep Tau ID -----------------------------
              bool condInvertTauDeepVSjetLoose = deepTauVSjet == "LOOSE" && recoTauBoostedDeepVSjetLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetMedium = deepTauVSjet == "MEDIUM" && recoTauBoostedDeepVSjetMedium->at(iTau)<=0;
              bool condInvertTauDeepVSjetTight = deepTauVSjet == "TIGHT" && recoTauBoostedDeepVSjetTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVLoose = deepTauVSjet == "VLOOSE" && recoTauBoostedDeepVSjetVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVTight = deepTauVSjet == "VTIGHT" && recoTauBoostedDeepVSjetVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVLoose = deepTauVSjet == "VVLOOSE" && recoTauBoostedDeepVSjetVVLoose->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVTight = deepTauVSjet == "VVTIGHT" && recoTauBoostedDeepVSjetVVTight->at(iTau)<=0;
              bool condInvertTauDeepVSjetVVVLoose = recoTauBoostedDeepVSjetVVVLoose->at(iTau)>0;
              bool condInvertTauDeepVSeVVVLoose = recoTauBoostedDeepVSeVVVLoose->at(iTau)>0;
              bool condInvertTauDeepVSmuVLoose = recoTauBoostedDeepVSmuVLoose->at(iTau)>0;
              // -------------------------------------------------------------------------------

              bool passCondInvertTauDeepVSjet = ((condInvertTauDeepVSjetLoose || condInvertTauDeepVSjetMedium || condInvertTauDeepVSjetTight || condInvertTauDeepVSjetVLoose || condInvertTauDeepVSjetVTight || condInvertTauDeepVSjetVVLoose || condInvertTauDeepVSjetVVTight) && condInvertTauDeepVSjetVVVLoose && condInvertTauDeepVSeVVVLoose && condInvertTauDeepVSmuVLoose);
              // -------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauDeep) || (invertedTauIso && !passCondInvertTauDeepVSjet)) continue;
          } // end if deepTauID && recoTauBoostedDeepVSjetraw->size() > 0

          else{
              bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauBoostedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauBoostedIsoMVAVVLoose->at(iTau)>0;
              bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauBoostedIsoMVAVLoose->at(iTau)>0;
              bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauBoostedIsoMVALoose->at(iTau)>0;
              bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauBoostedIsoMVAMedium->at(iTau)>0;
              bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauBoostedIsoMVATight->at(iTau)>0;
              bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauBoostedIsoMVAVTight->at(iTau)>0;
              bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauBoostedIsoMVAVVTight->at(iTau)>0;

              bool passCondTauMVA = (condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight);
              // -------------------------------------------------------------------------------------------------

              bool condInvertTauMVARaw = recoTauBoostedIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condInvertTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauBoostedIsoMVAVVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauBoostedIsoMVAVLoose->at(iTau)<=0;
              bool condInvertTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauBoostedIsoMVALoose->at(iTau)<=0;
              bool condInvertTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauBoostedIsoMVAMedium->at(iTau)<=0;
              bool condInvertTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauBoostedIsoMVATight->at(iTau)<=0;
              bool condInvertTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauBoostedIsoMVAVTight->at(iTau)<=0;
              bool condInvertTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauBoostedIsoMVAVVTight->at(iTau)<=0;

              // ------ always require tau candidates pass vvvloose MVA id in order to have similar dynamic shape as real tau
              bool passCondInvertTauMVA = (condInvertTauMVARaw && (condInvertTauMVAWPVVLoose || condInvertTauMVAWPVLoose || condInvertTauMVAWPLoose || condInvertTauMVAWPMedium || condInvertTauMVAWPTight || condInvertTauMVAWPVTight || condInvertTauMVAWPVVTight));
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauBoostedAntiMuMVALoose->at(iTau)>0;
              bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauBoostedAntiMuMVATight->at(iTau)>0; 
              bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

              bool passCondTauAntiMuMVA = (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull);
              // -------------------------------------------------------------------------------------------------

              bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauBoostedAntiEleMVALoose->at(iTau)>0;
              bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauBoostedAntiEleMVAMedium->at(iTau)>0;
              bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauBoostedAntiEleMVATight->at(iTau)>0; 
              bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

              bool passCondTauAntiEleMVA = (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull);
              // -------------------------------------------------------------------------------------------------

              if ((!invertedTauIso && !passCondTauMVA) || (invertedTauIso && !passCondInvertTauMVA) || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
          } // end if !deepTauID (tauMVAID)

          TLorentzVector TauCand;
          TauCand.SetPtEtaPhiE(recoTauBoostedPt->at(iTau), recoTauBoostedEta->at(iTau), recoTauBoostedPhi->at(iTau), recoTauBoostedEnergy->at(iTau));
          double recoTauBoostedMass = TauCand.M();
          TauCand.SetPtEtaPhiM(recoTauBoostedPt->at(iTau)*tauScaleCorr, recoTauBoostedEta->at(iTau), recoTauBoostedPhi->at(iTau), recoTauBoostedMass);

          if (TauCand.DeltaR(Mu1) < 0.4 || TauCand.DeltaR(Mu2) < 0.4) continue;
          if ((recoTauBoostedDecayMode->at(iTau) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
          Tau.SetPtEtaPhiM(recoTauBoostedPt->at(iTau)*tauScaleCorr, recoTauBoostedEta->at(iTau), recoTauBoostedPhi->at(iTau), recoTauBoostedMass);
          TauIso = deepTauID ? recoTauBoostedDeepVSjetraw->at(iTau) : recoTauBoostedIsoMVArawValue->at(iTau);
          TauDM = recoTauBoostedDecayMode->at(iTau);

          float smallestDR = 1.0; // dR cut between tau1 and tau2
          bool findTau2 = false;

          for (unsigned int iTau2=iTau+1; iTau2<recoTauBoostedPt->size(); iTau2++)
          {
              //if (iTau2 == iTau) continue;
              if (deepTauID && recoTauBoostedDeepVSjetraw->size() > 0)
              {
                  // -------------------------------------------------------------------------------
                  bool passCondTauDeepVSele = recoTauBoostedDeepVSeVLoose->at(iTau2)>0;
                  bool passCondTauDeepVSjet = recoTauBoostedDeepVSjetVLoose->at(iTau2)>0;
                  bool passCondTauDeepVSmu = recoTauBoostedDeepVSmuVLoose->at(iTau2)>0;
                  bool passCondTauDeep = passCondTauDeepVSele && passCondTauDeepVSjet && passCondTauDeepVSmu;
                  // -------------------------------------------------------------------------------

                  if (!passCondTauDeep) continue;
              } // end if deepTauID && recoTauBoostedDeepVSjetraw->size() > 0

              else{
                  bool passCondTauMVA = recoTauBoostedIsoMVAVLoose->at(iTau2)>0;
                  bool passCondTauAntiMuMVA = recoTauBoostedAntiMuMVALoose->at(iTau2)>0;
                  bool passCondTauAntiEleMVA = recoTauBoostedAntiEleMVALoose->at(iTau2)>0;
                  if (!passCondTauMVA || !passCondTauAntiMuMVA || !passCondTauAntiEleMVA) continue;
              } // end if !deepTauID (tauMVAID)

              if ((recoTauBoostedDecayMode->at(iTau2) != tauDecayModeThreshold) && (tauDecayModeThreshold == 0 || tauDecayModeThreshold == 1 || tauDecayModeThreshold == 5 || tauDecayModeThreshold == 6 || tauDecayModeThreshold == 10 || tauDecayModeThreshold == 11)) continue;
              TLorentzVector Tau2Cand; // prepare this variable for dR(tau1, tau2) implementation
              Tau2Cand.SetPtEtaPhiE(recoTauBoostedPt->at(iTau2), recoTauBoostedEta->at(iTau2), recoTauBoostedPhi->at(iTau2), recoTauBoostedEnergy->at(iTau2));
              double recoTauBoostedMass = Tau2Cand.M();
              Tau2Cand.SetPtEtaPhiM(recoTauBoostedPt->at(iTau2)*tauScaleCorr, recoTauBoostedEta->at(iTau2), recoTauBoostedPhi->at(iTau2), recoTauBoostedMass);
              //if ((Tau.DeltaR(Tau2Cand) < smallestDR) && (recoTauBoostedPDGId->at(iTau) == (-1) * recoTauBoostedPDGId->at(iTau2)) && ((Tau+Tau2Cand).M() < 60.0) && (Tau2Cand.DeltaR(Mu1) > 0.8) && (Tau2Cand.DeltaR(Mu2) > 0.8))
              if ((Tau.DeltaR(Tau2Cand) < smallestDR) && (recoTauBoostedPDGId->at(iTau) == (-1) * recoTauBoostedPDGId->at(iTau2)) && (Tau2Cand.DeltaR(Mu1) > 0.4) && (Tau2Cand.DeltaR(Mu2) > 0.4))
              {
                  Tau2.SetPtEtaPhiM(recoTauBoostedPt->at(iTau2)*tauScaleCorr, recoTauBoostedEta->at(iTau2), recoTauBoostedPhi->at(iTau2), recoTauBoostedMass);
                  Tau2Iso = deepTauID ? recoTauBoostedDeepVSjetraw->at(iTau2) : recoTauBoostedIsoMVArawValue->at(iTau2);
                  Tau2DM = recoTauBoostedDecayMode->at(iTau2);
                  smallestDR = Tau.DeltaR(Tau2);
                  findTau2 = true;
              } // end if find tau2 with tau1 matched
          } // end loop for tau2

          if (!findTau2) continue;
          else{
              findTauTauPair = true;

              // ----- fill flat trees -----
              invMassMu1Mu2_tt = (Mu1+Mu2).M();
              deltaRMu1Mu2_tt = Mu1.DeltaR(Mu2);

              mu1Pt_tt = Mu1.Pt();
              mu1Eta_tt = Mu1.Eta();
              mu1Phi_tt = Mu1.Phi();
              mu1Mass_tt = Mu1.M();

              mu2Pt_tt = Mu2.Pt();
              mu2Eta_tt = Mu2.Eta();
              mu2Phi_tt = Mu2.Phi();
              mu2Mass_tt = Mu2.M();

              if (boostDiTauOpt)
              {
                  visMassTauTau_tt = (Tau+Tau2).M();
                  visMass2Mu2Tau_tt = (Mu1+Mu2+Tau+Tau2).M();
                  deltaRTauTau_tt = Tau.DeltaR(Tau2);

                  tauPt_tt = Tau.Pt();
                  tauEta_tt = Tau.Eta();
                  tauPhi_tt = Tau.Phi();
                  tauMass_tt = Tau.M();
                  tauDisc_tt = TauIso;
                  tauDM_tt = TauDM;

                  tau2Pt_tt = Tau2.Pt();
                  tau2Eta_tt = Tau2.Eta();
                  tau2Phi_tt = Tau2.Phi();
                  tau2Mass_tt = Tau2.M();
                  tau2Disc_tt = Tau2Iso;
                  tau2DM_tt = Tau2DM;
              } // end if boostDiTauOpt == true

              else{
                  visMassTauTau_tt = Tau.M();
                  visMass2Mu2Tau_tt = (Mu1+Mu2+Tau).M();

                  tauPt_tt = Tau.Pt();
                  tauEta_tt = Tau.Eta();
                  tauPhi_tt = Tau.Phi();
                  tauMass_tt = Tau.M();
                  tauDisc_tt = TauIso;
              } // end if boostDiTauOpt == false

              eventWeight_tt = weight/summedWeights;
              TreeTauTau->Fill();
              break;
          } // end if findTau2
      } // end loop for tau
   }// end loop for events

   outputFile->cd();
   Tree2Mu->Write("Tree2Mu", TObject::kOverwrite);
   TreeMuEle->Write("TreeMuEle", TObject::kOverwrite);
   TreeMuTau->Write("TreeMuTau", TObject::kOverwrite);
   TreeEleTau->Write("TreeEleTau", TObject::kOverwrite);
   TreeTauTau->Write("TreeTauTau", TObject::kOverwrite);
   outputFile->Close();
}
