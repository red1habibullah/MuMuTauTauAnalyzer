#define FakeMuMuTauETauHadAnalyzer_cxx
#include "FakeMuMuTauETauHadAnalyzer.h"
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

void FakeMuMuTauETauHadAnalyzer::Loop()
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

      // ---- prepare for the vector of matched muon pairs and a electron & tau candidate ---
      vector<TLorentzVector> Mu1s;
      vector<TLorentzVector> Mu2s;
      vector<TLorentzVector> Eles;
      vector<TLorentzVector> Taus;

      vector<float> EleIso;
      vector<float> TauIso;
      vector<float> TauDM;

      Mu1s.clear();
      Mu2s.clear();
      Eles.clear();
      Taus.clear();

      EleIso.clear();
      TauIso.clear();
      TauDM.clear();
      // ========================================================================

      // ---- these vectors containing the rank of each matched muon or electron to avoid double counting ---
      vector<int> indexMu1s;
      vector<int> indexMu2s;
      vector<int> indexEles;

      indexMu1s.clear();
      indexMu2s.clear();
      indexEles.clear();
      // =============================================================================

      // ---- these vectors containing the muons that are not matched into pairs --- 
      vector<TLorentzVector> unMatchedMus;
      vector<TLorentzVector> unMatchedEles;
      vector<TLorentzVector> unMatchedTaus;

      unMatchedMus.clear();
      unMatchedEles.clear();
      unMatchedTaus.clear();
      // ============================================================================

      // ---- define varibles that will be used to be pushed into the above vectors ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Ele;
      TLorentzVector Tau;
      TLorentzVector unMatchedMu;
      TLorentzVector unMatchedEle;
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

      // ---- search for an additional electron and tau for fake rate study ----
      if (recoElectronPt->size()>0 && recoTauPt->size()>0)
      {
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
              bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauAntiEleMVALoose->at(iTau)>0;
              bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauAntiEleMVAMedium->at(iTau)>0;
              bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauAntiEleMVATight->at(iTau)>0; 
              bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

              if ((condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight) && (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull))
              {
                  Tau.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
                  float smallestDR = 5.0; // dR between electron and tau
                  bool findEle = false;
                  int indexEle = 0;

                  for (unsigned int iEle=0; iEle<recoElectronPt->size(); iEle++)
                  {
                      TLorentzVector EleCand;
                      EleCand.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEcalTrkEnergyPostCorr->at(iEle));
                      if (recoTauPDGId->at(iTau)/fabs(recoTauPDGId->at(iTau)) == (-1) * recoElectronPDGId->at(iEle)/fabs(recoElectronPDGId->at(iEle)) && Tau.DeltaR(EleCand) < smallestDR)
                      {
                          Ele.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEcalTrkEnergyPostCorr->at(iEle));
                          smallestDR = Tau.DeltaR(Ele);
                          findEle = true;
                          indexEle = iEle;
                      } // end if find electron with opposite charge
                  } // end for loop on electrons

                  if (findEle == true)
                  {
                      Eles.push_back(Ele);
                      indexEles.push_back(indexEle);

                      Taus.push_back(Tau);
                      TauIso.push_back(recoTauIsoMVArawValue->at(iTau));
                      TauDM.push_back(recoTauDecayMode->at(iTau));
                  } // end if findEle
              } // end if a tau candidate passes the requirement
              else{
                  unMatchedTaus.push_back(Tau);
              } // end else a tau candidate passes the requirement
          } // end for loop on tau candidates
      } // end if tau cluster size > 0 && electron cluster > 0

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

      // ---- search for unMatched electron candidates ----
      for (unsigned int iEle=0; iEle<recoElectronPt->size(); iEle++)
      {
          std::vector<int>::iterator iter = std::find(indexEles.begin(), indexEles.end(), iEle);
          if (iter == indexEles.end())
          {
              unMatchedEle.SetPtEtaPhiE(recoElectronPt->at(iEle), recoElectronEta->at(iEle), recoElectronPhi->at(iEle), recoElectronEcalTrkEnergyPostCorr->at(iEle));
              unMatchedEles.push_back(unMatchedEle);
          } // end if find unMatched electron
      } // end loop for unMatched electron candidates

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
          bool fillRec = false;
          // --- filling histograms of mu-mu ---
          for (unsigned int iMuon=0; iMuon<Mu1s.size(); iMuon++)
          {
              Mu1 = Mu1s.at(iMuon);
              Mu2 = Mu2s.at(iMuon);
              TLorentzVector Mu1Mu2 = Mu1 + Mu2;
              bool passDR = false; // dR between mu-mu pair and tau

              for (unsigned int iTau=0; iTau<Taus.size(); iTau++)
              {
                  Ele = Eles.at(iTau);
                  Tau = Taus.at(iTau);
                  TLorentzVector EleTau = Ele + Tau;
                  TLorentzVector MuMuEleTau = Mu1Mu2 + EleTau;

                  if (Mu1.DeltaR(Ele) > 0.4 && Mu2.DeltaR(Ele) > 0.4 && Mu1.DeltaR(Tau) > 0.8 && Mu2.DeltaR(Tau) > 0.8)
                  {
                      passDR = true;

                      ptEleTau->Fill(EleTau.Pt(), weight);
                      dREleTau->Fill(Ele.DeltaR(Tau), weight);
                      invMassEleTau->Fill(EleTau.M(), weight);
                      dRInvMassEleTau->Fill(Ele.DeltaR(Tau), EleTau.M(), weight);

                      ele1Pt->Fill(Ele.Pt(), weight);
                      ele1Eta->Fill(Ele.Eta(), weight);
                      ele1Phi->Fill(Ele.Phi(), weight);

                      tauPt->Fill(Tau.Pt(), weight);
                      tauEta->Fill(Tau.Eta(), weight);
                      tauPhi->Fill(Tau.Phi(), weight);
                      tauMass->Fill(Tau.M(), weight);
                      tauDecayMode->Fill(TauDM.at(iTau), weight);

                      dRMu1Ele1->Fill(Mu1.DeltaR(Ele), weight);
                      dRMu1Tau->Fill(Mu1.DeltaR(Tau), weight);
                      dRMu2Ele1->Fill(Mu2.DeltaR(Ele), weight);
                      dRMu2Tau->Fill(Mu2.DeltaR(Tau), weight);

                      ptMuMuTauEleTauHad->Fill(MuMuEleTau.Pt(), weight);
                      invMassMuMuTauEleTauHad->Fill(MuMuEleTau.M(), weight);
                      
                      fillRec = true;
                      break;
                  } // end if dR between mu-mu pair and tau
              } // end for loop on taus

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
              } // end if passDR between mu-mu pair and tau and additional electron
          } // end loop for mu-mu pairs

          // --------- implement the matching between gen particles and reco objects (MC only) -------------
          if (isMC && matchRecGen && fillRec)
          {
              TLorentzVector GenMu1;
              TLorentzVector GenMu2;
              TLorentzVector GenEle;
              TLorentzVector GenTauEle;
              TLorentzVector GenTauHad;

              bool findMatchedRecGenMu1 = false;
              bool findMatchedRecGenMu2 = false;
              bool findMatchedRecGenEle = false;
              bool findMatchedRecGenTauEle = false;
              bool findMatchedRecGenTauHad = false;

              unsigned int indexGenMu1 = -1;

              if (genMuonPt->size()>0)
              {
                  // --------- search for matched genMu1 for Mu1 --------------
                  double smallestDR = 0.15;
                  for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
                  {
                      TLorentzVector GenMuCand;
                      GenMuCand.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
                      if (Mu1.DeltaR(GenMuCand) <= smallestDR)
                      {
                          smallestDR = Mu1.DeltaR(GenMuCand);
                          findMatchedRecGenMu1 = true;
                          GenMu1 = GenMuCand;
                          indexGenMu1 = iGenMu;
                      } // end if Mu1.DeltaR(GenMuCand) <= smallestDR
                  } // end for loop on GenMu1

                  if (findMatchedRecGenMu1)
                  {
                      mu1PtVSGenMu1Pt->Fill(Mu1.Pt(), GenMu1.Pt(), weight);
                      mu1EtaVSGenMu1Eta->Fill(Mu1.Eta(), GenMu1.Eta(), weight);
                      mu1PhiVSGenMu1Phi->Fill(Mu1.Phi(), GenMu1.Phi(), weight);
                  } // end if findMatchedRecGenMu1 == true

                  // --------- search for matched genMu2 for Mu2 --------------
                  smallestDR = 0.15;
                  for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
                  {
                      TLorentzVector GenMuCand;
                      GenMuCand.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
                      if (Mu2.DeltaR(GenMuCand) <= smallestDR && iGenMu != indexGenMu1)
                      {
                          smallestDR = Mu2.DeltaR(GenMuCand);
                          findMatchedRecGenMu2 = true;
                          GenMu2 = GenMuCand;
                      } // end if Mu2.DeltaR(GenMuCand) <= smallestDR && iGenMu != indexGenMu1
                  } // end for loop on GenMu2

                  if (findMatchedRecGenMu2)
                  {
                      mu2PtVSGenMu2Pt->Fill(Mu2.Pt(), GenMu2.Pt(), weight);
                      mu2EtaVSGenMu2Eta->Fill(Mu2.Eta(), GenMu2.Eta(), weight);
                      mu2PhiVSGenMu2Phi->Fill(Mu2.Phi(), GenMu2.Phi(), weight);
                  } // end if findMatchedRecGenMu2 == true
              } // end if genMuonPt->size()>0

              if (genElectronPt->size()>0)
              {
                  // --------- search for matched genEle for Ele --------------
                  double smallestDR = 0.15;
                  for (unsigned int iGenEle=0; iGenEle<genElectronPt->size(); iGenEle++)
                  {
                      TLorentzVector GenEleCand;
                      GenEleCand.SetPtEtaPhiM(genElectronPt->at(iGenEle), genElectronEta->at(iGenEle), genElectronPhi->at(iGenEle), genElectronMass->at(iGenEle));
                      if (Ele.DeltaR(GenEleCand) <= smallestDR)
                      {
                          smallestDR = Ele.DeltaR(GenEleCand);
                          findMatchedRecGenEle = true;
                          GenEle = GenEleCand;
                      } // end if Ele.DeltaR(GenEleCand) <= smallestDR
                  } // end for loop on GenEle

                  if (findMatchedRecGenEle)
                  {
                      elePtVSGenElePt->Fill(Ele.Pt(), GenEle.Pt(), weight);
                      eleEtaVSGenEleEta->Fill(Ele.Eta(), GenEle.Eta(), weight);
                      elePhiVSGenElePhi->Fill(Ele.Phi(), GenEle.Phi(), weight);
                  } // end if findMatchedRecGenEle == true
              } // end if genElectronPt->size()>0

              if (genTauElePt->size()>0)
              {
                  // --------- search for matched genTauEle for Tau --------------
                  double smallestDR = 0.15;
                  double GenTauEleVisiblePt = 0;

                  for (unsigned int iGenTauEle=0; iGenTauEle<genTauElePt->size(); iGenTauEle++)
                  {
                      TLorentzVector GenTauEleCand;
                      GenTauEleCand.SetPtEtaPhiM(genTauElePt->at(iGenTauEle), genTauEleEta->at(iGenTauEle), genTauElePhi->at(iGenTauEle), genTauEleMass->at(iGenTauEle));
                      if (Ele.DeltaR(GenTauEleCand) <= smallestDR)
                      {
                          smallestDR = Ele.DeltaR(GenTauEleCand);
                          findMatchedRecGenTauEle = true;
                          GenTauEle = GenTauEleCand;
                          GenTauEleVisiblePt = genTauEleVisPt->at(iGenTauEle);
                      } // end if Ele.DeltaR(GenTauEleCand) <= smallestDR
                  } // end for loop on genTauEle

                  if (findMatchedRecGenTauEle)
                  {
                      elePtVSGenTauElePt->Fill(Ele.Pt(), GenTauEle.Pt(), weight);
                      elePtVSGenTauEleVisPt->Fill(Ele.Pt(), GenTauEleVisiblePt, weight);
                  } // end if findMatchedRecGenTauEle == true
              } // end if genTauElePt->size()>0

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
                  } // end if findMatchedRecGenTauHad == true
              } // end if genTauHadPt->size()>0

              if (findMatchedRecGenMu1 && findMatchedRecGenMu2)
              {
                  dRMu1Mu2VSGenMu1GenMu2->Fill(Mu1.DeltaR(Mu2), GenMu1.DeltaR(GenMu2), weight);
                  TLorentzVector Mu1Mu2 = Mu1 + Mu2;
                  TLorentzVector GenMu1Mu2 = GenMu1 + GenMu2;
                  invMassMu1Mu2VSGenMu1GenMu2->Fill(Mu1Mu2.M(), GenMu1Mu2.M(), weight);
              } // end if findMatchedRecGenMu1 && findMatchedRecGenMu2

              if (findMatchedRecGenEle && findMatchedRecGenTauHad)
              {
                  TLorentzVector EleTau = Ele + Tau;
                  TLorentzVector GenEleTauHad = GenEle + GenTauHad;
                  dREleTauVSGenEleGenTauHad->Fill(Ele.DeltaR(Tau), GenEle.DeltaR(GenTauHad), weight);
                  invMassEleTauVSGenEleGenTauHad->Fill(EleTau.M(), GenEleTauHad.M(), weight);
              } // end if findMatchedRecGenEle && findMatchedRecGenTauHad

              if (findMatchedRecGenTauEle && findMatchedRecGenTauHad)
              {
                  TLorentzVector EleTau = Ele + Tau;
                  TLorentzVector GenTauEleTauHad = GenTauEle + GenTauHad;
                  dREleTauVSGenTauEleGenTauHad->Fill(Ele.DeltaR(Tau), GenTauEle.DeltaR(GenTauHad), weight);
                  invMassEleTauVSGenTauEleGenTauHad->Fill(EleTau.M(), GenTauEleTauHad.M(), weight);
              } // end if findMatchedRecGenTauEle && findMatchedRecGenTauHad
          } // end if isMC && matchRecGen && fillRec
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

      for (unsigned int iTau=0; iTau<unMatchedTaus.size(); iTau++)
      {
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
