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
          if ((invertedMu1Iso == true && recoMuonIsolation->at(iMuon) < Mu1IsoThreshold) || (invertedMu1Iso == false && recoMuonIsolation->at(iMuon) > Mu1IsoThreshold)) continue;
          Mu.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          float highestPt = 0;
          bool findTau = false;
          int indexTau = 0;

          for (unsigned int iTau=0; iTau<recoTauPt->size(); iTau++)
          {
              std::vector<int>::iterator iter = std::find(indexTaus.begin(), indexTaus.end(), iTau);
              if (iter != indexTaus.end()) continue;

              if ((tauMVAIsoRawORWP == true && recoTauIsoMVArawValue->at(iTau) > tauMVAIsoRawThreshold) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVLOOSE" && recoTauIsoMVAVVLoose->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "VLOOSE" && recoTauIsoMVAVLoose->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "LOOSE" && recoTauIsoMVALoose->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "MEDIUM" && recoTauIsoMVAMedium->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "TIGHT" && recoTauIsoMVATight->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "VTIGHT" && recoTauIsoMVAVTight->at(iTau)>0) ||
                 (tauMVAIsoRawORWP == false && tauMVAIsoWP == "VVTIGHT" && recoTauIsoMVAVVTight->at(iTau)>0))
              {
                  bool isSameSign = recoTauPDGId->at(iTau)/fabs(recoTauPDGId->at(iTau)) == recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon));
                  bool isOppositeSign = recoTauPDGId->at(iTau)/fabs(recoTauPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon));
                  if ((isSameSign && signSameOROpposite == true) || (isOppositeSign && signSameOROpposite == false))
                  {
                      TLorentzVector TauCand;
                      TauCand.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
                      if (Mu.DeltaR(TauCand) > 0.3 && TauCand.Pt() > highestPt)
                      {
                          Tau.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
                          highestPt = TauCand.Pt();
                          findTau = true;
                          indexTau = iTau;
                      } // end if dR (mu, tau) and highest pt
                  } // end if same or opposite sign
              } // end if tau candidates satisfying MVA discriminators
          } // end for loop on taus

          if (findTau == true)
          {
              Mus.push_back(Mu);
              Taus.push_back(Tau);

              TauIso.push_back(recoTauIsoMVArawValue->at(indexTau));
              TauDM.push_back(recoTauDecayMode->at(indexTau));

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
          std::vector<int>::iterator iter2 = std::find(indexTaus.begin(), indexTaus.end(), iTau);
          if (iter2 == indexTaus.end())
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

      if (Mus.size()>0)
      {
          Mu = Mus.at(0);
          Tau = Taus.at(0);
          TLorentzVector MuTau = Mu + Tau;

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

          if ((invertedPzetaCut == false && zeta > pzetaThreshold) || (invertedPzetaCut == true && zeta < pzetaThreshold))
          {
              mtMuMet->Fill(MuTauMt, weight);
          } // end if only pzeta cut

          if ((MuTauMt > mTMuTauLowThreshold) && (MuTauMt < mTMuTauHighThreshold))
          {
              pzeta->Fill(zeta, weight);
          } // end if only mtMuMet cut

          if ((MuTauMt > mTMuTauLowThreshold) && (MuTauMt < mTMuTauHighThreshold) && ((invertedPzetaCut == false && zeta > pzetaThreshold) || (invertedPzetaCut == true && zeta < pzetaThreshold)))
          {
              muPt->Fill(Mu.Pt(), weight);
              muEta->Fill(Mu.Eta(), weight);
              muPhi->Fill(Mu.Phi(), weight);

              tauPt->Fill(Tau.Pt(), weight);
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
          } // end if MT(mu,met) and pzeta within thresholds
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
