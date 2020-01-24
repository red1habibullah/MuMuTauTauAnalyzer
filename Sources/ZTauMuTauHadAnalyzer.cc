#define ZTauMuTauHadAnalyzer_cxx
#include "ZTauMuTauHadAnalyzer.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <math.h>
#include <iomanip>
#include <iostream>
using namespace std;

void ZTauMuTauHadAnalyzer::Loop()
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
      
      // ---- prepare for the vector of muon & tau candidates ---
      vector<TLorentzVector> Mus;
      vector<TLorentzVector> Taus;

      vector<float> TauDM;
      vector<float> TauIso;

      Mus.clear();
      Taus.clear();

      TauDM.clear();
      TauIso.clear();
      // =============================================================================

      // ---- these vectors containing the rank of each matched muon to avoid double counting ---
      vector<int> indexMus;
      indexMus.clear();

      // ---- these vectors containing the rank of each matched tau to avoid double counting ---
      vector<int> indexTaus;
      indexTaus.clear();
      // =============================================================================

      // ---- these vectors containing the muons or taus that are not matched into pairs ---
      vector<TLorentzVector> unMatchedMus;
      vector<TLorentzVector> unMatchedTaus;

      vector<float> unMatchedMuIsos;
      vector<float> unMatchedTauMVAIsos;
      vector<float> unMatchedTauDM;

      unMatchedMus.clear();
      unMatchedTaus.clear();

      unMatchedMuIsos.clear();
      unMatchedTauMVAIsos.clear();
      unMatchedTauDM.clear();
      // =============================================================================
      
      // ---- define varibles that will be used to be pushed into the above vectors ---
      TLorentzVector Mu;
      TLorentzVector Tau;
      TLorentzVector unMatchedTau;
      // =============================================================================

      // ---- start loop on muon candidates ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          if ((invertedMu1Iso == true && recoMuonIsolation->at(iMuon) < Mu1IsoThreshold) || (invertedMu1Iso == false && recoMuonIsolation->at(iMuon) > Mu1IsoThreshold) || (recoMuonPt->at(iMuon) < 26.0))
          {
              continue;
          } // end if MuIso requirement

          Mu.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          float highestPt = 0;
          bool findTau = false;
          int indexTau = 0;

          for (unsigned int iTau=0; iTau<recoTauPt->size(); iTau++)
          {
              bool condTauMVARaw = tauMVAIsoRawORWP == true && recoTauIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold;
              bool condTauMVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau)>0;
              bool condTauMVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau)>0;
              bool condTauMVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau)>0;
              bool condTauMVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau)>0;
              bool condTauMVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau)>0;
              bool condTauMVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau)>0;
              bool condTauMVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau)>0;
              bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauAntiMuMVALoose->at(iTau)>0;
              bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauAntiMuMVATight->at(iTau)>0;
              bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";
              bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauAntiEleMVALoose->at(iTau)>0;
              bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauAntiEleMVAMedium->at(iTau)>0;
              bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauAntiEleMVATight->at(iTau)>0;
              bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

              if ((condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight) && (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull) && (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull))
              {
                  TLorentzVector TauCand;
                  TauCand.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
                  if (Mu.DeltaR(TauCand) > 0.5 && TauCand.Pt() > highestPt)
                  {
                      Tau.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
                      highestPt = TauCand.Pt();
                      findTau = true;
                      indexTau = iTau;
                  } // end if dR (mu, tau) and highest pt
              } // end if tau candidates satisfying MVA discriminators
          } // end for loop on taus

          if (findTau == true)
          {
              Mus.push_back(Mu);
              Taus.push_back(Tau);

              TauIso.push_back(recoTauIsoMVArawValue->at(indexTau));
              TauDM.push_back(recoTauDecayMode->at(indexTau));

              indexMus.push_back(iMuon);
              indexTaus.push_back(indexTau);
          } // end if findTau

          else{
              unMatchedMus.push_back(Mu);
              unMatchedMuIsos.push_back(recoMuonIsolation->at(iMuon));
          } // end else findTau
      } // end for loop on muons

      // ---- search for unMatched tau candidates ----
      for (unsigned int iTau=0; iTau<recoTauPt->size(); iTau++)
      {
          std::vector<int>::iterator iter = std::find(indexTaus.begin(), indexTaus.end(), iTau);
          if (iter == indexTaus.end())
          {
              unMatchedTau.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
              unMatchedTaus.push_back(unMatchedTau);
              unMatchedTauMVAIsos.push_back(recoTauIsoMVArawValue->at(iTau));
              unMatchedTauDM.push_back(recoTauDecayMode->at(iTau));
          } // end if find unMatched taus
      } // end for loop on unMatched tau candidates

      // ---- prepare event weight info ----
      double weight = 1;
      if (isMC == true)
      {
          weight *= genEventWeight;
      } // end if isMC == true

      // ---- fill histograms ----
      nMatchedMuTauPair->Fill(Mus.size(), weight);
      nUnMatchedMu->Fill(unMatchedMus.size(), weight);
      nUnMatchedTau->Fill(unMatchedTaus.size(), weight);

      if (Mus.size()>0 && Taus.size()>0)
      {
          bool fillRec = false;

          // --- filling histograms --- 
          Mu = Mus.at(0);
          Tau = Taus.at(0);
          TLorentzVector MuTau = Mu + Tau;

          bool isSameSign = recoTauPDGId->at(indexTaus.at(0))/fabs(recoTauPDGId->at(indexTaus.at(0))) == recoMuonPDGId->at(indexMus.at(0))/fabs(recoMuonPDGId->at(indexMus.at(0)));
          bool isOppositeSign = recoTauPDGId->at(indexTaus.at(0))/fabs(recoTauPDGId->at(indexTaus.at(0))) == (-1) * recoMuonPDGId->at(indexMus.at(0))/fabs(recoMuonPDGId->at(indexMus.at(0)));
          if ((isSameSign && !signSameOROpposite) || (isOppositeSign && signSameOROpposite)) continue;

          float MetPt = recoMET->at(0);
          float MetPhi= recoMETPhi->at(0);
          float MetPx = recoMETPx->at(0);
          float MetPy = recoMETPy->at(0);
          float MuTauMt = sqrt(pow(Mu.Pt() + MetPt, 2) - pow(Mu.Px() + MetPx, 2) - pow(Mu.Py() + MetPy, 2));

          // ---------------- Pzeta variable ---------------------------
          float norm_zeta = sqrt(pow(Tau.Px()/Tau.Pt() + Mu.Px()/Mu.Pt(), 2) + pow(Tau.Py()/Tau.Pt() + Mu.Py()/Mu.Pt(), 2));
          float x_zeta = (Tau.Px()/Tau.Pt() + Mu.Px()/Mu.Pt())/norm_zeta;
          float y_zeta = (Tau.Py()/Tau.Pt() + Mu.Py()/Mu.Pt())/norm_zeta;
          float p_zeta_mis = MetPx*x_zeta + MetPy*y_zeta;
          float p_zeta_vis = (Tau.Px() + Mu.Px())*x_zeta + (Tau.Py() + Mu.Py())*y_zeta;
          float zeta = p_zeta_mis - 0.85*p_zeta_vis;
          // -----------------------------------------------------------

          // ---------------- various parameter cuts for different region analysis ------------------
          bool pzetaCut = (invertedPzetaCut == false && zeta > pzetaThreshold) || (invertedPzetaCut == true && zeta < pzetaThreshold);
          bool mutauMtCut = (MuTauMt > mTMuMetLowThreshold) && (MuTauMt < mTMuMetHighThreshold);
          bool tauPtCut = (Tau.Pt() > tauPtLowThreshold) && (Tau.Pt() < tauPtHighThreshold);
          // ----------------------------------------------------------------------------------------

          // --------------- rec-gen matching for separating ZTT, DYB, DYJ, and other backgrounds and data -------------------
          if (isMC && doWhatSample == "ZTT" && genMuonPt->size()>0 && genTauMuPt->size()>0 && genTauHadPt->size()>0)
          {
              TLorentzVector GenMu;
              TLorentzVector GenTauMu;
              TLorentzVector GenTauHad;

              bool findMatchedRecGenMu = false;
              bool findMatchedRecGenTauMu = false;
              bool findMatchedRecGenTauHad = false;

              // --------- search for matched genMu for recMu --------------
              double smallestDR = 0.15;
              for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
              {
                  TLorentzVector GenMuCand;
                  GenMuCand.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
                  if (Mu.DeltaR(GenMuCand) <= smallestDR)
                  {
                      smallestDR = Mu.DeltaR(GenMuCand);
                      findMatchedRecGenMu = true;
                      GenMu = GenMuCand;
                  } // end if Mu.DeltaR(GenMuCand) <= smallestDR
              } // end for loop on GenMu

              // --------- search for matched genTauMu for recMu --------------
              smallestDR = 0.15;
              for (unsigned int iGenTauMu=0; iGenTauMu<genTauMuPt->size(); iGenTauMu++)
              {
                  TLorentzVector GenTauMuCand;
                  GenTauMuCand.SetPtEtaPhiM(genTauMuPt->at(iGenTauMu), genTauMuEta->at(iGenTauMu), genTauMuPhi->at(iGenTauMu), genTauMuMass->at(iGenTauMu));
                  if (Mu.DeltaR(GenTauMuCand) <= smallestDR && fabs(genTauMuMotherPDGId->at(iGenTauMu)) == 23)
                  {
                      smallestDR = Mu.DeltaR(GenTauMuCand);
                      findMatchedRecGenTauMu = true;
                      GenTauMu = GenTauMuCand;
                  } // end if Mu.DeltaR(GenTauMuCand) <= smallestDR
              } // end for loop on GenTauMu

              // --------- search for matched genTauHad for Tau --------------
              smallestDR = 0.15;
              double GenTauHadVisiblePt = 0;

              for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
              {
                  TLorentzVector GenTauHadCand;
                  GenTauHadCand.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                  if (Tau.DeltaR(GenTauHadCand) <= smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad)) == 23)
                  {
                      smallestDR = Tau.DeltaR(GenTauHadCand);
                      findMatchedRecGenTauHad = true;
                      GenTauHad = GenTauHadCand;
                      GenTauHadVisiblePt = genTauHadVisPt->at(iGenTauHad);
                  } // end if Tau.DeltaR(GenTauHad) <= smallestDR
              } // end for loop on GenTauHad

              if (findMatchedRecGenMu && findMatchedRecGenTauMu && findMatchedRecGenTauHad && pzetaCut && mutauMtCut)
              {
                  tauPt->Fill(Tau.Pt(), weight);
                  tauPtVSGenTauHadPt->Fill(Tau.Pt(), GenTauHad.Pt(), weight);
                  tauPtVSGenTauHadVisPt->Fill(Tau.Pt(), GenTauHadVisiblePt, weight);
                  tauPtResponse->Fill(Tau.Pt()/GenTauHadVisiblePt, weight);
                  tauPtVSTauPtResponse->Fill(Tau.Pt(), Tau.Pt()/GenTauHadVisiblePt, weight);
              } // end if findMatchedRecGenMu && findMatchedRecGenTauMu && findMatchedRecGenTauHad && pzetaCut && mutauMtCut

              if (findMatchedRecGenMu && findMatchedRecGenTauMu && findMatchedRecGenTauHad && pzetaCut && tauPtCut)
              {
                  mtMuMet->Fill(MuTauMt, weight);
              } // end if findMatchedRecGenMu && findMatchedRecGenTauMu && findMatchedRecGenTauHad && pzetaCut && tauPtCut

              if (findMatchedRecGenMu && findMatchedRecGenTauMu && findMatchedRecGenTauHad && mutauMtCut && tauPtCut)
              {
                  pzeta->Fill(zeta, weight);
              } // end if findMatchedRecGenMu && findMatchedRecGenTauMu && findMatchedRecGenTauHad && mutauMtCut && tauPtCut

              if (findMatchedRecGenMu && findMatchedRecGenTauMu && findMatchedRecGenTauHad && pzetaCut && mutauMtCut && tauPtCut)
              {
                  muPt->Fill(Mu.Pt(), weight);
                  muEta->Fill(Mu.Eta(), weight);
                  muPhi->Fill(Mu.Phi(), weight);

                  tauEta->Fill(Tau.Eta(), weight);
                  tauPhi->Fill(Tau.Phi(), weight);
                  tauMass->Fill(Tau.M(), weight);
                  tauDecayMode->Fill(TauDM.at(0), weight);
                  tauIsoMVA->Fill(TauIso.at(0), weight);

                  dRMuTau->Fill(Mu.DeltaR(Tau), weight);
                  invMassMuTau->Fill(MuTau.M(), weight);
                  ptMuTau->Fill(MuTau.Pt(), weight);
                  dRInvMassMuTau->Fill(Mu.DeltaR(Tau), MuTau.M(), weight);

                  metPt->Fill(MetPt, weight);
                  metPhi->Fill(MetPhi, weight);

                  muPtVSGenMuPt->Fill(Mu.Pt(), GenMu.Pt(), weight);
                  muEtaVSGenMuEta->Fill(Mu.Eta(), GenMu.Eta(), weight);
                  muPhiVSGenMuPhi->Fill(Mu.Phi(), GenMu.Phi(), weight);
                  muPtVSGenTauMuPt->Fill(Mu.Pt(), GenTauMu.Pt(), weight);

                  dRMuTauVSGenMuGenTauHad->Fill(Mu.DeltaR(Tau), GenMu.DeltaR(GenTauHad), weight);
                  invMassMuTauVSGenMuGenTauHad->Fill(MuTau.M(), (GenMu + GenTauHad).M(), weight);

                  dRMuTauVSGenTauMuGenTauHad->Fill(Mu.DeltaR(Tau), GenTauMu.DeltaR(GenTauHad), weight);
                  invMassMuTauVSGenTauMuGenTauHad->Fill(MuTau.M(), (GenTauMu + GenTauHad).M(), weight);
              } // end if findMatchedRecGenMu && findMatchedRecGenTauMu && findMatchedRecGenTauHad && pzetaCut && mutauMtCut && tauPtCut
          } // end if isMC && doWhatSample == "ZTT" && genMuonPt->size()>0 && genTauMuPt->size()>0 && genTauHadPt->size()>0

          if (isMC && doWhatSample == "DYB" && genMuonPt->size()>0 && genTauHadPt->size()>0)
          {
              TLorentzVector GenMu;
              TLorentzVector GenTauHad;

              bool findMatchedRecGenMu = false;
              bool findMatchedRecGenTauHad = false;

              // --------- search for matched genMu for recMu --------------
              double smallestDR = 0.15;
              for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
              {
                  TLorentzVector GenMuCand;
                  GenMuCand.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
                  if (Mu.DeltaR(GenMuCand) <= smallestDR && fabs(genMuonMotherPDGId->at(iGenMu)) == 23)
                  {
                      smallestDR = Mu.DeltaR(GenMuCand);
                      findMatchedRecGenMu = true;
                      GenMu = GenMuCand;
                  } // end if Mu.DeltaR(GenMuCand) <= smallestDR && fabs(genMuonMotherPDGId->at(iGenMu)) == 23
              } // end for loop on GenMu

              // --------- search for matched genTauHad for Tau --------------
              smallestDR = 0.15;
              double GenTauHadVisiblePt = 0;

              for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
              {
                  TLorentzVector GenTauHadCand;
                  GenTauHadCand.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                  if (Tau.DeltaR(GenTauHadCand) <= smallestDR && fabs(genTauHadMotherPDGId->at(iGenTauHad)) != 23)
                  {
                      smallestDR = Tau.DeltaR(GenTauHadCand);
                      findMatchedRecGenTauHad = true;
                      GenTauHad = GenTauHadCand;
                      GenTauHadVisiblePt = genTauHadVisPt->at(iGenTauHad);
                  } // end if Tau.DeltaR(GenTauHad) <= smallestDR
              } // end for loop on GenTauHad

              if (findMatchedRecGenMu && findMatchedRecGenTauHad && pzetaCut && mutauMtCut)
              {
                  tauPt->Fill(Tau.Pt(), weight);
                  tauPtVSGenTauHadPt->Fill(Tau.Pt(), GenTauHad.Pt(), weight);
                  tauPtVSGenTauHadVisPt->Fill(Tau.Pt(), GenTauHadVisiblePt, weight);
                  tauPtResponse->Fill(Tau.Pt()/GenTauHadVisiblePt, weight);
                  tauPtVSTauPtResponse->Fill(Tau.Pt(), Tau.Pt()/GenTauHadVisiblePt, weight);
              } // end if findMatchedRecGenMu && findMatchedRecGenTauHad && pzetaCut && mutauMtCut

              if (findMatchedRecGenMu && findMatchedRecGenTauHad && pzetaCut && tauPtCut)
              {
                  mtMuMet->Fill(MuTauMt, weight);
              } // end if findMatchedRecGenMu && findMatchedRecGenTauHad && pzetaCut && tauPtCut

              if (findMatchedRecGenMu && findMatchedRecGenTauHad && mutauMtCut && tauPtCut)
              {
                  pzeta->Fill(zeta, weight);
              } // end if findMatchedRecGenMu && findMatchedRecGenTauHad && mutauMtCut && tauPtCut

              if (findMatchedRecGenMu && findMatchedRecGenTauHad && pzetaCut && mutauMtCut && tauPtCut)
              {
                  muPt->Fill(Mu.Pt(), weight);
                  muEta->Fill(Mu.Eta(), weight);
                  muPhi->Fill(Mu.Phi(), weight);

                  tauEta->Fill(Tau.Eta(), weight);
                  tauPhi->Fill(Tau.Phi(), weight);
                  tauMass->Fill(Tau.M(), weight);
                  tauDecayMode->Fill(TauDM.at(0), weight);
                  tauIsoMVA->Fill(TauIso.at(0), weight);

                  dRMuTau->Fill(Mu.DeltaR(Tau), weight);
                  invMassMuTau->Fill(MuTau.M(), weight);
                  ptMuTau->Fill(MuTau.Pt(), weight);
                  dRInvMassMuTau->Fill(Mu.DeltaR(Tau), MuTau.M(), weight);

                  metPt->Fill(MetPt, weight);
                  metPhi->Fill(MetPhi, weight);

                  muPtVSGenMuPt->Fill(Mu.Pt(), GenMu.Pt(), weight);
                  muEtaVSGenMuEta->Fill(Mu.Eta(), GenMu.Eta(), weight);
                  muPhiVSGenMuPhi->Fill(Mu.Phi(), GenMu.Phi(), weight);

                  dRMuTauVSGenMuGenTauHad->Fill(Mu.DeltaR(Tau), GenMu.DeltaR(GenTauHad), weight);
                  invMassMuTauVSGenMuGenTauHad->Fill(MuTau.M(), (GenMu + GenTauHad).M(), weight);
              } // end if findMatchedRecGenMu && findMatchedRecGenTauHad && pzetaCut && mutauMtCut && tauPtCut
          } // end if isMC && doWhatSample == "DYB" && genMuonPt->size()>0 && genTauHadPt->size()>0

          if (isMC && doWhatSample == "DYJ")
          {
              TLorentzVector GenMu;
              TLorentzVector GenTauHad;

              bool findMatchedRecGenMu = false;
              bool findMatchedRecGenTauHad = false;

              // --------- search for matched genMu for recMu --------------
              double smallestDR = 0.15;
              for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
              {
                  TLorentzVector GenMuCand;
                  GenMuCand.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
                  if (Mu.DeltaR(GenMuCand) <= smallestDR)
                  {
                      smallestDR = Mu.DeltaR(GenMuCand);
                      findMatchedRecGenMu = true;
                      GenMu = GenMuCand;
                  } // end if Mu.DeltaR(GenMuCand) <= smallestDR
              } // end for loop on GenMu

              // --------- search for matched genTauHad for Tau --------------
              smallestDR = 0.15;
              double GenTauHadVisiblePt = 0;

              for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
              {
                  TLorentzVector GenTauHadCand;
                  GenTauHadCand.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                  if (Tau.DeltaR(GenTauHadCand) <= smallestDR)
                  {
                      smallestDR = Tau.DeltaR(GenTauHadCand);
                      findMatchedRecGenTauHad = true;
                      GenTauHad = GenTauHadCand;
                      GenTauHadVisiblePt = genTauHadVisPt->at(iGenTauHad);
                  } // end if Tau.DeltaR(GenTauHad) <= smallestDR
              } // end for loop on GenTauHad

              if (findMatchedRecGenMu && !findMatchedRecGenTauHad && pzetaCut && mutauMtCut)
              {
                  tauPt->Fill(Tau.Pt(), weight);
                  tauPtVSGenTauHadPt->Fill(Tau.Pt(), GenTauHad.Pt(), weight);
                  tauPtVSGenTauHadVisPt->Fill(Tau.Pt(), GenTauHadVisiblePt, weight);
                  tauPtResponse->Fill(Tau.Pt()/GenTauHadVisiblePt, weight);
                  tauPtVSTauPtResponse->Fill(Tau.Pt(), Tau.Pt()/GenTauHadVisiblePt, weight);
              } // end if findMatchedRecGenMu && !findMatchedRecGenTauHad && pzetaCut && mutauMtCut

              if (findMatchedRecGenMu && !findMatchedRecGenTauHad && pzetaCut && tauPtCut)
              {
                  mtMuMet->Fill(MuTauMt, weight);
              } // end if findMatchedRecGenMu && !findMatchedRecGenTauHad && pzetaCut && tauPtCut

              if (findMatchedRecGenMu && !findMatchedRecGenTauHad && mutauMtCut && tauPtCut)
              {
                  pzeta->Fill(zeta, weight);
              } // end if findMatchedRecGenMu && !findMatchedRecGenTauHad && mutauMtCut && tauPtCut

              if (findMatchedRecGenMu && !findMatchedRecGenTauHad && pzetaCut && mutauMtCut && tauPtCut)
              {
                  muPt->Fill(Mu.Pt(), weight);
                  muEta->Fill(Mu.Eta(), weight);
                  muPhi->Fill(Mu.Phi(), weight);

                  tauEta->Fill(Tau.Eta(), weight);
                  tauPhi->Fill(Tau.Phi(), weight);
                  tauMass->Fill(Tau.M(), weight);
                  tauDecayMode->Fill(TauDM.at(0), weight);
                  tauIsoMVA->Fill(TauIso.at(0), weight);

                  dRMuTau->Fill(Mu.DeltaR(Tau), weight);
                  invMassMuTau->Fill(MuTau.M(), weight);
                  ptMuTau->Fill(MuTau.Pt(), weight);
                  dRInvMassMuTau->Fill(Mu.DeltaR(Tau), MuTau.M(), weight);

                  metPt->Fill(MetPt, weight);
                  metPhi->Fill(MetPhi, weight);

                  muPtVSGenMuPt->Fill(Mu.Pt(), GenMu.Pt(), weight);
                  muEtaVSGenMuEta->Fill(Mu.Eta(), GenMu.Eta(), weight);
                  muPhiVSGenMuPhi->Fill(Mu.Phi(), GenMu.Phi(), weight);

                  dRMuTauVSGenMuGenTauHad->Fill(Mu.DeltaR(Tau), GenMu.DeltaR(GenTauHad), weight);
                  invMassMuTauVSGenMuGenTauHad->Fill(MuTau.M(), (GenMu + GenTauHad).M(), weight);
              } // end if findMatchedRecGenMu && !findMatchedRecGenTauHad && pzetaCut && mutauMtCut && tauPtCut
          } // end if isMC && doWhatSample == "DYJ"

          if (doWhatSample != "ZTT" && doWhatSample != "DYB" && doWhatSample != "DYJ")
          {
              if (pzetaCut && mutauMtCut)
              {
                  tauPt->Fill(Tau.Pt(), weight);
              } // end if only pzeta cut and mtMuMet cut

              if (pzetaCut && tauPtCut)
              {
                  mtMuMet->Fill(MuTauMt, weight);
              } // end if only pzeta cut && tauPtCut

              if (mutauMtCut && tauPtCut)
              {
                  pzeta->Fill(zeta, weight);
              } // end if only mtMuMet cut && tauPtCut

              if (pzetaCut && mutauMtCut && tauPtCut)
              {
                  muPt->Fill(Mu.Pt(), weight);
                  muEta->Fill(Mu.Eta(), weight);
                  muPhi->Fill(Mu.Phi(), weight);

                  tauEta->Fill(Tau.Eta(), weight);
                  tauPhi->Fill(Tau.Phi(), weight);
                  tauMass->Fill(Tau.M(), weight);
                  tauDecayMode->Fill(TauDM.at(0), weight);
                  tauIsoMVA->Fill(TauIso.at(0), weight);

                  dRMuTau->Fill(Mu.DeltaR(Tau), weight);
                  invMassMuTau->Fill(MuTau.M(), weight);
                  ptMuTau->Fill(MuTau.Pt(), weight);
                  dRInvMassMuTau->Fill(Mu.DeltaR(Tau), MuTau.M(), weight);

                  metPt->Fill(MetPt, weight);
                  metPhi->Fill(MetPhi, weight);

                  fillRec = true;
              } // end if MT(mu,met), pzeta, and tauPt within thresholds

              // --------- implement the matching between gen particles and reco objects (MC only) -------------
              if (isMC && fillRec)
              {
                  TLorentzVector GenMu;
                  TLorentzVector GenTauMu;
                  TLorentzVector GenTauHad;

                  bool findMatchedRecGenMu = false;
                  bool findMatchedRecGenTauMu = false;
                  bool findMatchedRecGenTauHad = false;

                  if (genMuonPt->size()>0)
                  {
                      // --------- search for matched genMu for recMu --------------
                      double smallestDR = 0.15;
                      for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
                      {
                          TLorentzVector GenMuCand;
                          GenMuCand.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
                          if (Mu.DeltaR(GenMuCand) <= smallestDR)
                          {
                              smallestDR = Mu.DeltaR(GenMuCand);
                              findMatchedRecGenMu = true;
                              GenMu = GenMuCand;
                          } // end if Mu.DeltaR(GenMuCand) <= smallestDR
                      } // end for loop on GenMu

                      if (findMatchedRecGenMu)
                      {
                          muPtVSGenMuPt->Fill(Mu.Pt(), GenMu.Pt(), weight);
                          muEtaVSGenMuEta->Fill(Mu.Eta(), GenMu.Eta(), weight);
                          muPhiVSGenMuPhi->Fill(Mu.Phi(), GenMu.Phi(), weight);
                      } // end if findMatchedRecGenMu == true
                  } // end if genMuonPt->size()>0

                  if (genTauMuPt->size()>0)
                  {
                      // --------- search for matched genTauMu for Mu3 --------------
                      double smallestDR = 0.15;
                      for (unsigned int iGenTauMu=0; iGenTauMu<genTauMuPt->size(); iGenTauMu++)
                      {
                          TLorentzVector GenTauMuCand;
                          GenTauMuCand.SetPtEtaPhiM(genTauMuPt->at(iGenTauMu), genTauMuEta->at(iGenTauMu), genTauMuPhi->at(iGenTauMu), genTauMuMass->at(iGenTauMu));
                          if (Mu.DeltaR(GenTauMuCand) <= smallestDR)
                          {
                              smallestDR = Mu.DeltaR(GenTauMuCand);
                              findMatchedRecGenTauMu = true;
                              GenTauMu = GenTauMuCand;
                          } // end if Mu3.DeltaR(GenTauMuCand) <= smallestDR
                      } // end for loop on GenTauMu

                      if (findMatchedRecGenTauMu)
                      {
                          muPtVSGenTauMuPt->Fill(Mu.Pt(), GenTauMu.Pt(), weight);
                      } // end if findMatchedRecGenTauMu == true
                  } // end if genTauMuPt->size()>0

                  if (genTauHadPt->size()>0)
                  {
                      // --------- search for matched genTauHad for Tau --------------
                      double smallestDR = 0.15;
                      double GenTauHadVisiblePt = 0;

                      for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
                      {
                          TLorentzVector GenTauHadCand;
                          GenTauHadCand.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                          if (Tau.DeltaR(GenTauHadCand) <= smallestDR)
                          {
                              smallestDR = Tau.DeltaR(GenTauHadCand);
                              findMatchedRecGenTauHad = true;
                              GenTauHad = GenTauHadCand;
                              GenTauHadVisiblePt = genTauHadVisPt->at(iGenTauHad);
                          } // end if Tau.DeltaR(GenTauHad) <= smallestDR
                      } // end for loop on GenTauHad

                      if (findMatchedRecGenTauHad)
                      {
                          tauPtVSGenTauHadPt->Fill(Tau.Pt(), GenTauHad.Pt(), weight);
                          tauEtaVSGenTauHadEta->Fill(Tau.Eta(), GenTauHad.Eta(), weight);
                          tauPhiVSGenTauHadPhi->Fill(Tau.Phi(), GenTauHad.Phi(), weight);
                          tauPtVSGenTauHadVisPt->Fill(Tau.Pt(), GenTauHadVisiblePt, weight);
                          tauPtResponse->Fill(Tau.Pt()/GenTauHadVisiblePt, weight);
                          tauPtVSTauPtResponse->Fill(Tau.Pt(), Tau.Pt()/GenTauHadVisiblePt, weight);
                      } // end if findMatchedRecGenTauHad == true
                  } // end if genTauHadPt->size()>0

                  if (findMatchedRecGenMu && findMatchedRecGenTauHad)
                  {
                      TLorentzVector MuTau = Mu + Tau;
                      TLorentzVector GenMuTauHad = GenMu + GenTauHad;
                      dRMuTauVSGenMuGenTauHad->Fill(Mu.DeltaR(Tau), GenMu.DeltaR(GenTauHad), weight);
                      invMassMuTauVSGenMuGenTauHad->Fill(MuTau.M(), GenMuTauHad.M(), weight);
                  } // end if findMatchedRecGenMu && findMatchedRecGenTauHad

                  if (findMatchedRecGenTauMu && findMatchedRecGenTauHad)
                  {
                      TLorentzVector MuTau = Mu + Tau;
                      TLorentzVector GenTauMuTauHad = GenTauMu + GenTauHad;
                      dRMuTauVSGenTauMuGenTauHad->Fill(Mu.DeltaR(Tau), GenTauMu.DeltaR(GenTauHad), weight);
                      invMassMuTauVSGenTauMuGenTauHad->Fill(MuTau.M(), GenTauMuTauHad.M(), weight);
                  } // end if findMatchedRecGenTauMu && findMatchedRecGenTauHad
              } // end if isMC && fillRec == true
          } // end if doWhatSample != "ZTT" && doWhatSample != "DYB" && doWhatSample != "DYJ"
      } // end if mu-tau pairs

      for (unsigned int iMuon=0; iMuon<unMatchedMus.size(); iMuon++)
      {
          unMatchedMuPt->Fill(unMatchedMus.at(iMuon).Pt(), weight);
          unMatchedMuEta->Fill(unMatchedMus.at(iMuon).Eta(), weight);
          unMatchedMuPhi->Fill(unMatchedMus.at(iMuon).Phi(), weight);
          unMatchedMuIso->Fill(unMatchedMuIsos.at(iMuon), weight);
      } // end loop for unMatched muons

      for (unsigned int iTau=0; iTau<unMatchedTaus.size(); iTau++)
      {
          unMatchedTauIsoMVA->Fill(unMatchedTauMVAIsos.at(iTau), weight);
          unMatchedTauDecayMode->Fill(unMatchedTauDM.at(iTau), weight);
          unMatchedTauPt->Fill(unMatchedTaus.at(iTau).Pt(), weight);
          unMatchedTauEta->Fill(unMatchedTaus.at(iTau).Eta(), weight);
          unMatchedTauPhi->Fill(unMatchedTaus.at(iTau).Phi(), weight);
      } // end loop for unMatched taus
   } // end for loop on events

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
