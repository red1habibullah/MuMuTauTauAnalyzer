#define MuTauAnalyzer_cxx
#include "MuTauAnalyzer.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <sys/time.h>
#include <iomanip>
#include <TLorentzVector.h>
#include <math.h>
using namespace std;

void MuTauAnalyzer::Loop()
{
   TString outputfileName = createOutputFileName();
   TFile* outputFile = new TFile(outputfileName, "RECREATE");
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;

   struct timeval t0;
   gettimeofday(&t0, 0);
   int mess_every_n =  std::min(1000000LL, nentries/10);

   for (Long64_t jentry=0; jentry<nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;

      if (jentry % mess_every_n == 0 && jentry > 0){
          timeval t1;
          gettimeofday(&t1, 0);
          double dt = (t1.tv_sec - t0.tv_sec) + 1.e-6*(t1.tv_usec - t0.tv_usec);
          dt *= double(nentries  - jentry) / mess_every_n;
          int dt_s = int(dt + 0.5);
          int dt_h = int(dt_s) / 3600; 
          dt_s -= dt_h * 3600;
          int dt_m = dt_s / 60;
          dt_s -= dt_m *60;
          cout << TString::Format("%4.1f%%", (100. * jentry) / nentries)
              << "\t" << std::setw(11) << jentry << " / " << nentries
              << "\t " << std::setw(4) << int(dt / mess_every_n * 1.e6 + 0.5) << " us/event"
              << "\t Remaining time for this dataset loop: " 
              << std::setw(2) << dt_h << " h "
              << std::setw(2) << dt_m << " min "
              << std::setw(2) << dt_s << " s"
              << "\r" << std::flush;
          t0 = t1;
      } // end if for timer settings

      //cout << "*** iEntry: " << jentry << endl;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;

      // ---- prepare for the vector of matched muon pairs and muon-tau pairs ---
      vector<TLorentzVector> Mu1s;
      vector<TLorentzVector> Mu2s;
      vector<TLorentzVector> Mu3s;
      vector<TLorentzVector> Taus;

      vector<float> Mu1Iso;
      vector<float> Mu2Iso;
      vector<float> Mu3Iso;
      vector<float> TauIso;

      Mu1s.clear();
      Mu2s.clear();
      Mu3s.clear();
      Taus.clear();

      Mu1Iso.clear();
      Mu2Iso.clear();
      Mu3Iso.clear();
      TauIso.clear();
      // ========================================================================

      // ---- these vectors containing the rank of each matched muon to avoid double counting ---
      vector<int> indexMu1s;
      vector<int> indexMu2s;
      vector<int> indexMu3s;

      indexMu1s.clear();
      indexMu2s.clear();
      indexMu3s.clear();
      // =============================================================================

      // ---- these vectors containing the muons and taus that are not matched into pairs --- 
      vector<TLorentzVector> unMatchedMus;
      vector<TLorentzVector> unMatchedTaus;

      vector<float> unMatchedMuonIso;
      vector<float> unMatchedTauIso;

      unMatchedMus.clear();
      unMatchedTaus.clear();

      unMatchedMuonIso.clear();
      unMatchedTauIso.clear();
      // ============================================================================

      // ---- define varibles that will be used to be pushed into the above vectors ---
      TLorentzVector Mu1;
      TLorentzVector Mu2;
      TLorentzVector Mu3;
      TLorentzVector Tau;
      TLorentzVector unMatchedMu;
      // ============================================================================

      // ---- read the four momentum information of pre-ordered first and second muons ----
      Mu1.SetPtEtaPhiE(recoMuonPt->at(0), recoMuonEta->at(0), recoMuonPhi->at(0), recoMuonEnergy->at(0));
      Mu2.SetPtEtaPhiE(recoMuonPt->at(1), recoMuonEta->at(1), recoMuonPhi->at(1), recoMuonEnergy->at(1));
      
      Mu1s.push_back(Mu1);
      Mu2s.push_back(Mu2);

      indexMu1s.push_back(0);
      indexMu2s.push_back(1);

      Mu1Iso.push_back(recoMuonIsolation->at(0));
      Mu2Iso.push_back(recoMuonIsolation->at(1));

      // ---- start loop on other muon candidates ----
      for (int iMuon=2; iMuon<recoMuonPt->size(); iMuon++)
      {
          if (indexMu2s.size() > 0) 
          {
              std::vector<int>::iterator iter = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon);
              if (iter != indexMu2s.end()) continue;
          } // end if there is any matched Mu2 candidiate

          //cout << "******** Mu1 index: " << iMuon << endl;
          Mu1.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
          float smallestDR = 99.0;
          bool findMu2 = false;
          int indexMu2 = 0;

          for (int iMuon2=iMuon+1; iMuon2<recoMuonPt->size(); iMuon2++)
          {
              std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon2);
              if (iter2 != indexMu2s.end()) continue;

              //cout << "******** Mu2 index: " << iMuon2 << endl;
              Mu2.SetPtEtaPhiE(recoMuonPt->at(iMuon2), recoMuonEta->at(iMuon2), recoMuonPhi->at(iMuon2), recoMuonEnergy->at(iMuon2));
              if((Mu1.DeltaR(Mu2) < smallestDR) && (recoMuonPDGId->at(iMuon) == (-1) * recoMuonPDGId->at(iMuon2)))
              {
                  smallestDR = Mu1.DeltaR(Mu2);
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

              Mu1Iso.push_back(recoMuonIsolation->at(iMuon));
              Mu2Iso.push_back(recoMuonIsolation->at(indexMu2));
          } // end if findMu2 

      } // end loop for mu1

      // ------- start loop on tau candidates -------
      for (int iTau=0; iTau<recoTauPt->size(); iTau++)
      {
          Tau.SetPtEtaPhiE(recoTauPt->at(iTau), recoTauEta->at(iTau), recoTauPhi->at(iTau), recoTauEnergy->at(iTau));
          float smallestDR = 99.0;
          bool findMu3 = false;
          int indexMu3 = 0;

          for (int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
          {
              std::vector<int>::iterator iter1 = std::find(indexMu1s.begin(), indexMu1s.end(), iMuon);
              std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon);
              if (iter1 != indexMu1s.end() || iter2 != indexMu2s.end()) continue;

              //cout << "******** Mu3 index: " << iMuon << endl;
              Mu3.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              if ((Tau.DeltaR(Mu3) < smallestDR) && (recoTauPDGId->at(iTau)/fabs(recoTauPDGId->at(iTau)) == (-1) * recoMuonPDGId->at(iMuon)/fabs(recoMuonPDGId->at(iMuon))))
              {
                  smallestDR = Tau.DeltaR(Mu3);
                  findMu3 = true;
                  indexMu3 = iMuon;
              } // end if find mu3 with tau matched
          } // end loop for mu3

          if (findMu3 == true)
          {
              Mu3s.push_back(Mu3);
              Taus.push_back(Tau);

              indexMu3s.push_back(indexMu3);

              Mu3Iso.push_back(recoMuonIsolation->at(indexMu3));
              TauIso.push_back(recoTauIsoMVArawValue->at(iTau));
          } // end if findMu3

          else{
              unMatchedTaus.push_back(Tau);
              unMatchedTauIso.push_back(recoTauIsoMVArawValue->at(iTau));
          } // end else findMu3
      } // end loop for tau

      // ---- search for unMatched muon candidates ----
      for (int iMuon=0; iMuon<recoMuonPt->size(); iMuon++)
      {
          std::vector<int>::iterator iter1 = std::find(indexMu1s.begin(), indexMu1s.end(), iMuon);
          std::vector<int>::iterator iter2 = std::find(indexMu2s.begin(), indexMu2s.end(), iMuon);
          std::vector<int>::iterator iter3 = std::find(indexMu3s.begin(), indexMu3s.end(), iMuon);

          if (iter1 == indexMu1s.end() && iter2 == indexMu2s.end() && iter3 == indexMu3s.end())
          {
              unMatchedMu.SetPtEtaPhiE(recoMuonPt->at(iMuon), recoMuonEta->at(iMuon), recoMuonPhi->at(iMuon), recoMuonEnergy->at(iMuon));
              unMatchedMus.push_back(unMatchedMu);
              unMatchedMuonIso.push_back(recoMuonIsolation->at(iMuon));
          } // end if find unMatched Mu
      } // end loop for unMatched muon candidates

      // ---- fill histograms ----
      nMatchedMuPairs->Fill(Mu1s.size());
      nMatchedMuTauPairs->Fill(Taus.size());
      nUnMatchedMu->Fill(unMatchedMus.size());
      nUnMatchedTau->Fill(unMatchedTaus.size());

      for (int iMuon=0; iMuon<Mu1s.size(); iMuon++)
      {
          Mu1 = Mu1s.at(iMuon);
          Mu2 = Mu2s.at(iMuon);
          TLorentzVector Mu1Mu2 = Mu1 + Mu2;
          dRMuMu->Fill(Mu1.DeltaR(Mu2));
          invMassMuMu->Fill(Mu1Mu2.M());
          dRInvMassMuMu->Fill(Mu1.DeltaR(Mu2), Mu1Mu2.M());

          Mu1IsoMuMuPair->Fill(Mu1Iso.at(iMuon));
          Mu2IsoMuMuPair->Fill(Mu2Iso.at(iMuon));
      } // end loop for mu pairs

      for (int iTau=0; iTau<Taus.size(); iTau++)
      {
          Mu3 = Mu3s.at(iTau);
          Tau = Taus.at(iTau);
          TLorentzVector MuTau = Mu3 + Tau;
          dRMuTau->Fill(Mu3.DeltaR(Tau));
          invMassMuTau->Fill(MuTau.M());
          dRInvMassMuTau->Fill(Mu3.DeltaR(Tau), MuTau.M());

          Mu3IsoMuTauPair->Fill(Mu3Iso.at(iTau));
          TauIsoMVAMuTauPair->Fill(TauIso.at(iTau));
      } // end loop for mu-tau pairs

      for (int iMuon=0; iMuon<unMatchedMus.size(); iMuon++)
      {
          unMatchedMuIso->Fill(unMatchedMuonIso.at(iMuon));
      } // end loop for unMatched muons

      for (int iTau=0; iTau<unMatchedTaus.size(); iTau++)
      {
          unMatchedTauIsoMVA->Fill(unMatchedTauIso.at(iTau));
      } // end loop for unMatched taus

   }// end loop for events

   outputFile->cd();

   int numberofhist = histColl.size();
   for(int i=0; i<numberofhist; i++){
       if (!isData) histColl[i]->Scale(lumiScale/summedWeights);
       histColl[i]->Write();
   } // end loop for writing all the histograms into the output file

   for(int j=0; j<numberofhist; j++){
       delete histColl[j];
   } // end loop for deleting all the histograms

   outputFile->Write();
   outputFile->Close();
}
