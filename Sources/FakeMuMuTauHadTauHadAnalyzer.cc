#define FakeMuMuTauHadTauHadAnalyzer_cxx
#include "FakeMuMuTauHadTauHadAnalyzer.h"
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

void FakeMuMuTauHadTauHadAnalyzer::Loop()
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

      // ---- prepare for the vector of matched muon pairs and two tau candidates ---
      vector<TLorentzVector> Mu1s;
      vector<TLorentzVector> Mu2s;
      vector<TLorentzVector> Tau1s;
      vector<TLorentzVector> Tau2s;

      vector<float> Tau1Iso;
      vector<float> Tau1DM;

      vector<float> Tau2Iso;
      vector<float> Tau2DM;

      Mu1s.clear();
      Mu2s.clear();
      Tau1s.clear();
      Tau2s.clear();

      Tau1Iso.clear();
      Tau1DM.clear();

      Tau2Iso.clear();
      Tau2DM.clear();
      // ========================================================================

      // ---- these vectors containing the rank of each matched muon and tau to avoid double counting ---
      vector<int> indexMu1s;
      vector<int> indexMu2s;
      vector<int> indexTau2s;

      indexMu1s.clear();
      indexMu2s.clear();
      indexTau2s.clear();
      // =============================================================================

      // ---- these vectors containing the muons that are not matched into pairs and taus not going into pairs --- 
      vector<TLorentzVector> unMatchedMus;
      vector<TLorentzVector> unMatchedTaus;

      vector<float> unMatchedTauIso;
      vector<float> unMatchedTauDM;

      unMatchedMus.clear();
      unMatchedTaus.clear();
      unMatchedTauIso.clear();
      unMatchedTauDM.clear();
      // ============================================================================

      // ---- define varibles that will be used to be pushed into the above vectors ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Tau1;
      TLorentzVector Tau2;
      TLorentzVector unMatchedMu;
      // ============================================================================

      // ---- start loop on muon candidates ----
      for (unsigned int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          if (recoMuonIsolation->at(iMuon) > 0.25) continue;
          Mu1.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          float highestPt = 0;
          float invMassLowThre = 60.0;
          float invMassHighThre = 120.0;
          bool findMu2 = false;
          int indexMu2 = 0;

          for (unsigned int iMuon2=iMuon+1; iMuon2<recoMuonPt->size(); iMuon2++)
          {
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
          } // end if findMu2 
      } // end loop for mu1

      // ---- search for two additional taus for fake rate study ----
      if (recoTauPt->size()>0)
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
              bool condTauAntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauAntiEleMVALoose->at(iTau)>0;
              bool condTauAntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauAntiEleMVAMedium->at(iTau)>0;
              bool condTauAntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauAntiEleMVATight->at(iTau)>0;
              bool condTauAntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

              if ((condTauMVARaw || condTauMVAWPVVLoose || condTauMVAWPVLoose || condTauMVAWPLoose || condTauMVAWPMedium || condTauMVAWPTight || condTauMVAWPVTight || condTauMVAWPVVTight) && (condTauAntiMuMVALoose || condTauAntiMuMVATight || condTauAntiMuMVANull) && (condTauAntiEleMVALoose || condTauAntiEleMVAMedium || condTauAntiEleMVATight || condTauAntiEleMVANull))
              {
                  Tau1.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
                  float smallestDR = 5.0; // dR between tau1 and tau2
                  bool findTau2 = false;
                  int indexTau2 = 0;

                  for (unsigned int iTau2=iTau+1; iTau2<recoTauPt->size(); iTau2++)
                  {
                      bool condTau2MVARaw = tauMVAIsoRawORWP == true && recoTauIsoMVArawValue->at(iTau2) > tauMVAIsoRawThreshold;
                      bool condTau2MVAWPVVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau2)>0;
                      bool condTau2MVAWPVLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau2)>0;
                      bool condTau2MVAWPLoose = tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau2)>0;
                      bool condTau2MVAWPMedium = tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau2)>0;
                      bool condTau2MVAWPTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau2)>0;
                      bool condTau2MVAWPVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau2)>0;
                      bool condTau2MVAWPVVTight = tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau2)>0;
                      bool condTau2AntiMuMVALoose = tauAntiMuDisc == "LOOSE" && recoTauAntiMuMVALoose->at(iTau2)>0;
                      bool condTau2AntiMuMVATight = tauAntiMuDisc == "TIGHT" && recoTauAntiMuMVATight->at(iTau2)>0;
                      bool condTau2AntiMuMVANull = tauAntiMuDisc != "LOOSE" && tauAntiMuDisc != "TIGHT";
                      bool condTau2AntiEleMVALoose = tauAntiEleDisc == "LOOSE" && recoTauAntiEleMVALoose->at(iTau2)>0;
                      bool condTau2AntiEleMVAMedium = tauAntiEleDisc == "MEDIUM" && recoTauAntiEleMVAMedium->at(iTau2)>0;
                      bool condTau2AntiEleMVATight = tauAntiEleDisc == "TIGHT" && recoTauAntiEleMVATight->at(iTau2)>0;
                      bool condTau2AntiEleMVANull = tauAntiEleDisc != "LOOSE" && tauAntiEleDisc != "MEDIUM" && tauAntiEleDisc != "TIGHT";

                      TLorentzVector Tau2Cand;
                      Tau2Cand.SetPtEtaPhiE(recoTauPt->at(iTau2), recoTauEta->at(iTau2), recoTauPhi->at(iTau2), recoTauEnergy->at(iTau2));
                      if (recoTauPDGId->at(iTau) == (-1) * recoTauPDGId->at(iTau2) && Tau1.DeltaR(Tau2Cand) < smallestDR && (condTau2MVARaw || condTau2MVAWPVVLoose || condTau2MVAWPVLoose || condTau2MVAWPLoose || condTau2MVAWPMedium || condTau2MVAWPTight || condTau2MVAWPVTight || condTau2MVAWPVVTight) && (condTau2AntiMuMVALoose || condTau2AntiMuMVATight || condTau2AntiMuMVANull) && (condTau2AntiEleMVALoose || condTau2AntiEleMVAMedium || condTau2AntiEleMVATight || condTau2AntiEleMVANull))
                      {
                          Tau2.SetPtEtaPhiE(recoTauPt->at(iTau2), recoTauEta->at(iTau2), recoTauPhi->at(iTau2), recoTauEnergy->at(iTau2));
                          smallestDR = Tau1.DeltaR(Tau2);
                          findTau2 = true;
                          indexTau2 = iTau2;
                      } // end if find tau2 with tau1 matched
                  } // end for loop on additional muons

                  if (findTau2 == true)
                  {
                      Tau1s.push_back(Tau1);
                      Tau2s.push_back(Tau2);

                      indexTau2s.push_back(indexTau2);

                      Tau1Iso.push_back(recoTauIsoMVArawValue->at(iTau));
                      Tau1DM.push_back(recoTauDecayMode->at(iTau));

                      Tau2Iso.push_back(recoTauIsoMVArawValue->at(indexTau2));
                      Tau2DM.push_back(recoTauDecayMode->at(indexTau2));
                  } // end if findTau2
              } // end if a tau candidate passes the requirement
              
              else{
                  unMatchedTaus.push_back(Tau1);
                  unMatchedTauIso.push_back(recoTauIsoMVArawValue->at(iTau));
                  unMatchedTauDM.push_back(recoTauDecayMode->at(iTau));
              } // end else a tau candidate passes the requirement
          } // end for loop on tau candidates
      } // end if tau cluster size > 0

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
      nUnMatchedTau->Fill(unMatchedTaus.size(), weight);
      
      if (Mu1s.size() >0 && Tau1s.size() >0)
      {
          bool fillRec = false;
          // --- filling histograms of mu-mu ---
          for (unsigned int iMuon=0; iMuon<Mu1s.size(); iMuon++)
          {
              Mu1 = Mu1s.at(iMuon);
              Mu2 = Mu2s.at(iMuon);
              TLorentzVector Mu1Mu2 = Mu1 + Mu2;
              bool passDR = false; // dR between mu-mu pair and tau

              for (unsigned int iTau=0; iTau<Tau1s.size(); iTau++)
              {
                  Tau1 = Tau1s.at(iTau);
                  Tau2 = Tau2s.at(iTau);
                  TLorentzVector TauTau = Tau1 + Tau2;
                  TLorentzVector MuMuTauTau = Mu1Mu2 + TauTau;

                  if (Mu1.DeltaR(Tau1) > 0.8 && Mu2.DeltaR(Tau1) > 0.8 && Mu1.DeltaR(Tau2) > 0.8 && Mu2.DeltaR(Tau2) > 0.8)
                  {
                      passDR = true;

                      ptTauTau->Fill(TauTau.Pt(), weight);
                      dRTauTau->Fill(Tau1.DeltaR(Tau2), weight);
                      invMassTauTau->Fill(TauTau.M(), weight);
                      dRInvMassTauTau->Fill(Tau1.DeltaR(Tau2), TauTau.M(), weight);

                      tauIsoMVA->Fill(Tau1Iso.at(iTau), weight);
                      tau2IsoMVA->Fill(Tau2Iso.at(iTau), weight);

                      tauPt->Fill(Tau1.Pt(), weight);
                      tauEta->Fill(Tau1.Eta(), weight);
                      tauPhi->Fill(Tau1.Phi(), weight);
                      tauMass->Fill(Tau1.M(), weight);
                      tauDecayMode->Fill(Tau1DM.at(iTau), weight);

                      tau2Pt->Fill(Tau2.Pt(), weight);
                      tau2Eta->Fill(Tau2.Eta(), weight);
                      tau2Phi->Fill(Tau2.Phi(), weight);
                      tau2Mass->Fill(Tau2.M(), weight);
                      tau2DecayMode->Fill(Tau2DM.at(iTau), weight);

                      dRMu1Tau->Fill(Mu1.DeltaR(Tau1), weight);
                      dRMu1Tau2->Fill(Mu1.DeltaR(Tau2), weight);
                      dRMu2Tau->Fill(Mu2.DeltaR(Tau1), weight);
                      dRMu2Tau2->Fill(Mu2.DeltaR(Tau2), weight);

                      ptMuMuTauHadTauHad->Fill(MuMuTauTau.Pt(), weight);
                      invMassMuMuTauHadTauHad->Fill(MuMuTauTau.M(), weight);

                      fillRec = true;
                      break;
                  } // end if dR between mu-mu pair and tau-tau
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
              } // end if passDR between mu-mu pair and tau-tau
          } // end loop for mu-mu pairs

          // --------- implement the matching between gen particles and reco objects (MC only) -------------
          if (isMC && matchRecGen && fillRec)
          {
              TLorentzVector GenMu1;
              TLorentzVector GenMu2;
              TLorentzVector GenTauHad1;
              TLorentzVector GenTauHad2;

              bool findMatchedRecGenMu1 = false;
              bool findMatchedRecGenMu2 = false;
              bool findMatchedRecGenTauHad1 = false;
              bool findMatchedRecGenTauHad2 = false;

              unsigned int indexGenMu1 = -1;
              unsigned int indexGenTau1 = -1;

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

              if (genTauHadPt->size()>0)
              {
                  // --------- search for matched genTauHad1 for Tau1 --------------
                  double smallestDR = 0.15;
                  double GenTauHadVisiblePt = 0;
                  for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
                  {
                      TLorentzVector GenTauHadCand;
                      GenTauHadCand.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                      if (Tau1.DeltaR(GenTauHadCand) <= smallestDR)
                      {
                          smallestDR = Tau1.DeltaR(GenTauHadCand);
                          findMatchedRecGenTauHad1 = true;
                          GenTauHad1 = GenTauHadCand;
                          GenTauHadVisiblePt = genTauHadVisPt->at(iGenTauHad);
                          indexGenTau1 = iGenTauHad;
                      } // end if Tau.DeltaR(GenTauHad) <= smallestDR
                  } // end for loop on GenTauHad1

                  if (findMatchedRecGenTauHad1)
                  {
                      tauPtVSGenTauHadPt->Fill(Tau1.Pt(), GenTauHad1.Pt(), weight);
                      tauEtaVSGenTauHadEta->Fill(Tau1.Eta(), GenTauHad1.Eta(), weight);
                      tauPhiVSGenTauHadPhi->Fill(Tau1.Phi(), GenTauHad1.Phi(), weight);
                      tauPtVSGenTauHadVisPt->Fill(Tau1.Pt(), GenTauHadVisiblePt, weight);
                  } // end if findMatchedRecGenTauHad == true

                  // --------- search for matched genTauHad2 for Tau2 --------------
                  smallestDR = 0.15;
                  GenTauHadVisiblePt = 0;
                  for (unsigned int iGenTauHad=0; iGenTauHad<genTauHadPt->size(); iGenTauHad++)
                  {
                      TLorentzVector GenTauHadCand;
                      GenTauHadCand.SetPtEtaPhiM(genTauHadPt->at(iGenTauHad), genTauHadEta->at(iGenTauHad), genTauHadPhi->at(iGenTauHad), genTauHadMass->at(iGenTauHad));
                      if (Tau2.DeltaR(GenTauHadCand) <= smallestDR && iGenTauHad != indexGenTau1)
                      {
                          smallestDR = Tau2.DeltaR(GenTauHadCand);
                          findMatchedRecGenTauHad2 = true;
                          GenTauHad2 = GenTauHadCand;
                          GenTauHadVisiblePt = genTauHadVisPt->at(iGenTauHad);
                      } // end if Tau2.DeltaR(GenTauHadCand) <= smallestDR && iGenTauHad != indexGenTau1
                  } // end for loop on GenTauHad2

                  if (findMatchedRecGenTauHad2)
                  {
                      tau2PtVSGenTauHad2Pt->Fill(Tau2.Pt(), GenTauHad2.Pt(), weight);
                      tau2EtaVSGenTauHad2Eta->Fill(Tau2.Eta(), GenTauHad2.Eta(), weight);
                      tau2PhiVSGenTauHad2Phi->Fill(Tau2.Phi(), GenTauHad2.Phi(), weight);
                      tau2PtVSGenTauHad2VisPt->Fill(Tau2.Pt(), GenTauHadVisiblePt, weight);
                  } // end if findMatchedRecGenTauHad2 == true
              } // end if genTauHadPt->size()>0

              if (findMatchedRecGenMu1 && findMatchedRecGenMu2)
              {
                  dRMu1Mu2VSGenMu1GenMu2->Fill(Mu1.DeltaR(Mu2), GenMu1.DeltaR(GenMu2), weight);
                  TLorentzVector Mu1Mu2 = Mu1 + Mu2;
                  TLorentzVector GenMu1Mu2 = GenMu1 + GenMu2;
                  invMassMu1Mu2VSGenMu1GenMu2->Fill(Mu1Mu2.M(), GenMu1Mu2.M(), weight);
              } // end if findMatchedRecGenMu1 && findMatchedRecGenMu2

              if (findMatchedRecGenTauHad1 && findMatchedRecGenTauHad2)
              {
                  TLorentzVector TauTau = Tau1 + Tau2;
                  TLorentzVector GenTauHadTauHad = GenTauHad1 + GenTauHad2;
                  dRTauTauVSGenTauHadGenTauHad->Fill(Tau1.DeltaR(Tau2), GenTauHad1.DeltaR(GenTauHad2), weight);
                  invMassTauTauVSGenTauHadGenTauHad->Fill(TauTau.M(), GenTauHadTauHad.M(), weight);
              } // end if findMatchedRecGenTauHad1 && findMatchedRecGenTauHad2
          } // end if isMC && matchRecGen && fillRec
      } // end if mu-mu pairs

      for (unsigned int iMuon=0; iMuon<unMatchedMus.size(); iMuon++)
      {
          unMatchedMuPt->Fill(unMatchedMus.at(iMuon).Pt(), weight);
          unMatchedMuEta->Fill(unMatchedMus.at(iMuon).Eta(), weight);
          unMatchedMuPhi->Fill(unMatchedMus.at(iMuon).Phi(), weight);
      } // end loop for unMatched muons

      for (unsigned int iTau=0; iTau<unMatchedTaus.size(); iTau++)
      {
          unMatchedTauIsoMVA->Fill(unMatchedTauIso.at(iTau), weight);
          unMatchedTauDecayMode->Fill(unMatchedTauDM.at(iTau), weight);
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
