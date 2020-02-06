#define FakeMuMuTauMuTauHadAnalyzer_cxx
#include "FakeMuMuTauMuTauHadAnalyzer.h"
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

void FakeMuMuTauMuTauHadAnalyzer::Loop()
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

      // ---- prepare for the vector of matched muon pairs and a muon & tau candidate ---
      vector<TLorentzVector> Mu1s;
      vector<TLorentzVector> Mu2s;
      vector<TLorentzVector> Mu3s;
      vector<TLorentzVector> Taus;

      vector<float> TauIso;
      vector<float> TauDM;

      Mu1s.clear();
      Mu2s.clear();
      Mu3s.clear();
      Taus.clear();

      TauIso.clear();
      TauDM.clear();
      // ========================================================================

      // ---- these vectors containing the rank of each matched muon to avoid double counting ---
      vector<int> indexMu1s;
      vector<int> indexMu2s;
      vector<int> indexMu3s;

      indexMu1s.clear();
      indexMu2s.clear();
      indexMu3s.clear();
      // =============================================================================

      // ---- these vectors containing the muons that are not matched into pairs and third muon --- 
      vector<TLorentzVector> unMatchedMus;
      unMatchedMus.clear();
      // ============================================================================

      // ---- define varibles that will be used to be pushed into the above vectors ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Mu3;
      TLorentzVector Tau;
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

      // ---- search for an additional muon and tau for fake rate study ----
      if (recoMuonPt->size()>2 && recoTauPt->size()>0)
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
              bool condTauAntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauAntiMuMVALoose->at(iTau)>0;
              bool condTauAntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauAntiMuMVATight->at(iTau)>0; 
              bool condTauAntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";

              if ((condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight) && (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull))
              {
                  Tau.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
                  float smallestDR = 5.0; // dR between Mu3 and tau
                  bool findMu3 = false;
                  int indexMu3 = 0;

                  for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
                  {
                      std::vector<int>::iterator iter1 = std::find(indexMu1s.begin(), indexMu1s.end(), iMuon);
                      std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon);
                      if (iter1 != indexMu1s.end() || iter2 != indexMu2s.end()) continue;

                      TLorentzVector Mu3Cand;
                      Mu3Cand.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
                      if (recoTauPDGId->at(iTau)/fabs(recoTauPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon)) && Tau.DeltaR(Mu3Cand) < smallestDR)
                      {
                          Mu3.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
                          smallestDR = Tau.DeltaR(Mu3);
                          findMu3 = true;
                          indexMu3 = iMuon;
                      } // end if find mu3 with opposite charge
                  } // end for loop on additional muons

                  if (findMu3 == true)
                  {
                      Mu3s.push_back(Mu3);
                      indexMu3s.push_back(indexMu3);

                      Taus.push_back(Tau);
                      TauIso.push_back(recoTauIsoMVArawValue->at(iTau));
                      TauDM.push_back(recoTauDecayMode->at(iTau));
                  } // end if findMu3
              } // end if a tau candidate passes the requirement
              else{
                  continue;
              } // end else a tau candidate passes the requirement
          } // end for loop on tau candidates
      } // end if tau cluster size > 0 && muon cluster > 2

      // ---- search for unMatched muon candidates ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          std::vector<int>::iterator iter1 = std::find(indexMu1s.begin(), indexMu1s.end(), iMuon);
          std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon);
          std::vector<int>::iterator iter3 = std::find(indexMu3s.begin(), indexMu3s.end(), iMuon);

          if (iter1 == indexMu1s.end() && iter2 == indexMu2s.end() && iter3 == indexMu3s.end())
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
                  Mu3 = Mu3s.at(iTau);
                  Tau = Taus.at(iTau);
                  TLorentzVector MuTau = Mu3 + Tau;
                  TLorentzVector MuMuTauTau = Mu1Mu2 + MuTau;

                  if (Mu1.DeltaR(Mu3) > 0.4 && Mu2.DeltaR(Mu3) > 0.4 && Mu1.DeltaR(Tau) > 0.8 && Mu2.DeltaR(Tau) > 0.8 && Mu3.DeltaR(Tau) > 0.05)
                  {
                      passDR = true;

                      ptMu3Tau->Fill(MuTau.Pt(), weight);
                      dRMu3Tau->Fill(Mu3.DeltaR(Tau), weight);
                      invMassMu3Tau->Fill(MuTau.M(), weight);
                      dRInvMassMu3Tau->Fill(Mu3.DeltaR(Tau), MuTau.M(), weight);

                      mu3Pt->Fill(Mu3.Pt(), weight);
                      mu3Eta->Fill(Mu3.Eta(), weight);
                      mu3Phi->Fill(Mu3.Phi(), weight);

                      tauPt->Fill(Tau.Pt(), weight);
                      tauEta->Fill(Tau.Eta(), weight);
                      tauPhi->Fill(Tau.Phi(), weight);
                      tauMass->Fill(Tau.M(), weight);
                      tauDecayMode->Fill(TauDM.at(iTau), weight);

                      dRMu1Mu3->Fill(Mu1.DeltaR(Mu3), weight);
                      dRMu1Tau->Fill(Mu1.DeltaR(Tau), weight);
                      dRMu2Mu3->Fill(Mu2.DeltaR(Mu3), weight);
                      dRMu2Tau->Fill(Mu2.DeltaR(Tau), weight);

                      ptMuMuTauMuTauHad->Fill(MuMuTauTau.Pt(), weight);
                      invMassMuMuTauMuTauHad->Fill(MuMuTauTau.M(), weight);
                      
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
              } // end if passDR between mu-mu pair and tau and additional muon
          } // end loop for mu-mu pairs

          // --------- implement the matching between gen particles and reco objects (MC only) -------------
          if (isMC && matchRecGen && fillRec)
          {
              TLorentzVector GenMu1;
              TLorentzVector GenMu2;
              TLorentzVector GenMu3;
              TLorentzVector GenTauMu;
              TLorentzVector GenTauHad;

              bool findMatchedRecGenMu1 = false;
              bool findMatchedRecGenMu2 = false;
              bool findMatchedRecGenMu3 = false;
              bool findMatchedRecGenTauMu = false;
              bool findMatchedRecGenTauHad = false;

              unsigned int indexGenMu1 = -1;
              unsigned int indexGenMu2 = -1;

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
                          indexGenMu2 = iGenMu;
                      } // end if Mu2.DeltaR(GenMuCand) <= smallestDR && iGenMu != indexGenMu1
                  } // end for loop on GenMu2

                  if (findMatchedRecGenMu2)
                  {
                      mu2PtVSGenMu2Pt->Fill(Mu2.Pt(), GenMu2.Pt(), weight);
                      mu2EtaVSGenMu2Eta->Fill(Mu2.Eta(), GenMu2.Eta(), weight);
                      mu2PhiVSGenMu2Phi->Fill(Mu2.Phi(), GenMu2.Phi(), weight);
                  } // end if findMatchedRecGenMu2 == true

                  // --------- search for matched genMu3 for Mu3 --------------
                  smallestDR = 0.15;
                  for (unsigned int iGenMu=0; iGenMu<genMuonPt->size(); iGenMu++)
                  {
                      TLorentzVector GenMuCand;
                      GenMuCand.SetPtEtaPhiM(genMuonPt->at(iGenMu), genMuonEta->at(iGenMu), genMuonPhi->at(iGenMu), genMuonMass->at(iGenMu));
                      if (Mu3.DeltaR(GenMuCand) <= smallestDR && iGenMu != indexGenMu1 && iGenMu != indexGenMu2)
                      {
                          smallestDR = Mu3.DeltaR(GenMuCand);
                          findMatchedRecGenMu3 = true;
                          GenMu3 = GenMuCand;
                      } // end if Mu3.DeltaR(GenMuCand) <= smallestDR && iGenMu != indexGenMu1 && iGenMu != indexGenMu2
                  } // end for loop on GenMu3

                  if (findMatchedRecGenMu3)
                  {
                      mu3PtVSGenMu3Pt->Fill(Mu3.Pt(), GenMu3.Pt(), weight);
                      mu3EtaVSGenMu3Eta->Fill(Mu3.Eta(), GenMu3.Eta(), weight);
                      mu3PhiVSGenMu3Phi->Fill(Mu3.Phi(), GenMu3.Phi(), weight);
                  } // end if findMatchedRecGenMu3 == true
              } // end if genMuonPt->size()>0

              if (genTauMuPt->size()>0)
              {
                  // --------- search for matched genTauMu for Mu3 --------------
                  double smallestDR = 0.15;
                  for (unsigned int iGenTauMu=0; iGenTauMu<genTauMuPt->size(); iGenTauMu++)
                  {
                      TLorentzVector GenTauMuCand;
                      GenTauMuCand.SetPtEtaPhiM(genTauMuPt->at(iGenTauMu), genTauMuEta->at(iGenTauMu), genTauMuPhi->at(iGenTauMu), genTauMuMass->at(iGenTauMu));
                      if (Mu3.DeltaR(GenTauMuCand) <= smallestDR)
                      {
                          smallestDR = Mu3.DeltaR(GenTauMuCand);
                          findMatchedRecGenTauMu = true;
                          GenTauMu = GenTauMuCand;
                      } // end if Mu3.DeltaR(GenTauMuCand) <= smallestDR
                  } // end for loop on GenTauMu

                  if (findMatchedRecGenTauMu)
                  {
                      mu3PtVSGenTauMuPt->Fill(Mu3.Pt(), GenTauMu.Pt(), weight);
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
                  } // end if findMatchedRecGenTauHad == true
              } // end if genTauHadPt->size()>0

              if (findMatchedRecGenMu1 && findMatchedRecGenMu2)
              {
                  dRMu1Mu2VSGenMu1GenMu2->Fill(Mu1.DeltaR(Mu2), GenMu1.DeltaR(GenMu2), weight);
                  TLorentzVector Mu1Mu2 = Mu1 + Mu2;
                  TLorentzVector GenMu1Mu2 = GenMu1 + GenMu2;
                  invMassMu1Mu2VSGenMu1GenMu2->Fill(Mu1Mu2.M(), GenMu1Mu2.M(), weight);
              } // end if findMatchedRecGenMu1 && findMatchedRecGenMu2

              if (findMatchedRecGenMu3 && findMatchedRecGenTauHad)
              {
                  TLorentzVector Mu3Tau = Mu3 + Tau;
                  TLorentzVector GenMu3TauHad = GenMu3 + GenTauHad;
                  dRMu3TauVSGenMu3GenTauHad->Fill(Mu3.DeltaR(Tau), GenMu3.DeltaR(GenTauHad), weight);
                  invMassMu3TauVSGenMu3GenTauHad->Fill(Mu3Tau.M(), GenMu3TauHad.M(), weight);
              } // end if findMatchedRecGenMu3 && findMatchedRecGenTauHad

              if (findMatchedRecGenTauMu && findMatchedRecGenTauHad)
              {
                  TLorentzVector Mu3Tau = Mu3 + Tau;
                  TLorentzVector GenTauMuTauHad = GenTauMu + GenTauHad;
                  dRMu3TauVSGenTauMuGenTauHad->Fill(Mu3.DeltaR(Tau), GenTauMu.DeltaR(GenTauHad), weight);
                  invMassMu3TauVSGenTauMuGenTauHad->Fill(Mu3Tau.M(), GenTauMuTauHad.M(), weight);
              } // end if findMatchedRecGenTauMu && findMatchedRecGenTauHad
          } // end if isMC && matchRecGen && fillRec
      } // end if mu-mu pairs

      for (unsigned int iMuon=0; iMuon<unMatchedMus.size(); iMuon++)
      {
          unMatchedMuPt->Fill(unMatchedMus.at(iMuon).Pt(), weight);
          unMatchedMuEta->Fill(unMatchedMus.at(iMuon).Eta(), weight);
          unMatchedMuPhi->Fill(unMatchedMus.at(iMuon).Phi(), weight);
      } // end loop for unMatched muons

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
