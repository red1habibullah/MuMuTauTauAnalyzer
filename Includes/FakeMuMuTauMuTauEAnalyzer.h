//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 18 14:19:21 2019 by ROOT version 6.10/08
// from TTree objectTree/objectTree
// found on file: MuMuTauTauTreelization.root
//////////////////////////////////////////////////////////

#ifndef FakeMuMuTauMuTauEAnalyzer_h
#define FakeMuMuTauMuTauEAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "HistoZmumu.h"

class FakeMuMuTauMuTauEAnalyzer : public HistoZmumu {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float>   *recoMuonPt;
   vector<float>   *recoMuonEta;
   vector<float>   *recoMuonPhi;
   vector<float>   *recoMuonEnergy;
   vector<int>     *recoMuonPDGId;
   vector<float>   *recoMuonIsolation;
   vector<float>   *recoMuonDXY;
   vector<float>   *recoMuonDZ;
   vector<int>     *recoMuonNTrackerLayers;
   vector<int>     *recoMuonTriggerFlag;
   vector<float>   *recoElectronPt;
   vector<float>   *recoElectronEta;
   vector<float>   *recoElectronPhi;
   vector<float>   *recoElectronEnergy;
   vector<int>     *recoElectronPDGId;
   vector<float>   *recoElectronIsolation;
   vector<float>   *recoElectronEcalTrkEnergyPostCorr;
   vector<float>   *recoElectronEcalTrkEnergyErrPostCorr;
   vector<float>   *recoJetPt;
   vector<float>   *recoJetEta;
   vector<float>   *recoJetPhi;
   vector<float>   *recoJetEnergy;
   vector<float>   *recoJetCSV;
   vector<float>   *recoMET;
   vector<float>   *recoMETPhi;
   vector<float>   *recoMETPx;
   vector<float>   *recoMETPy;
   Int_t           recoNPrimaryVertex;
   Int_t           eventID;
   Int_t           recoNPU;
   Int_t           trueNInteraction;
   Float_t         genEventWeight;

   // List of branches
   TBranch        *b_recoMuonPt;   //!
   TBranch        *b_recoMuonEta;   //!
   TBranch        *b_recoMuonPhi;   //!
   TBranch        *b_recoMuonEnergy;   //!
   TBranch        *b_recoMuonPDGId;   //!
   TBranch        *b_recoMuonIsolation;   //!
   TBranch        *b_recoMuonDXY;   //!
   TBranch        *b_recoMuonDZ;   //!
   TBranch        *b_recoMuonNTrackerLayers;   //!
   TBranch        *b_recoMuonTriggerFlag;   //!
   TBranch        *b_recoElectronPt;   //!
   TBranch        *b_recoElectronEta;   //!
   TBranch        *b_recoElectronPhi;   //!
   TBranch        *b_recoElectronEnergy;   //!
   TBranch        *b_recoElectronPDGId;   //!
   TBranch        *b_recoElectronIsolation;   //!
   TBranch        *b_recoElectronEcalTrkEnergyPostCorr;   //!
   TBranch        *b_recoElectronEcalTrkEnergyErrPostCorr;   //!
   TBranch        *b_recoJetPt;   //!
   TBranch        *b_recoJetEta;   //!
   TBranch        *b_recoJetPhi;   //!
   TBranch        *b_recoJetEnergy;   //!
   TBranch        *b_recoJetCSV;   //!
   TBranch        *b_recoMET;   //!
   TBranch        *b_recoMETPhi;   //!
   TBranch        *b_recoMETPx;   //!
   TBranch        *b_recoMETPy;   //!
   TBranch        *b_recoNPrimaryVertex;   //!
   TBranch        *b_eventID;   //!
   TBranch        *b_recoNPU;   //!
   TBranch        *b_trueNInteraction;   //!
   TBranch        *b_genEventWeight;   //!

   TString fileName;
   TString outputDir;
   Long_t  nMaxEvents;
   float lumiScale;
   float summedWeights; // these two factors contribute to the MC normalization
   bool isMC;
   bool invertedEle1Iso;
   double Ele1IsoThreshold;

   FakeMuMuTauMuTauEAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_ = 1.0, Long_t nMaxEvents_ = 0, bool isMC_ = false, bool invertedEle1Iso_ = false, double Ele1IsoThreshold_ = 0.25);
   string createOutputFileName();
   virtual ~FakeMuMuTauMuTauEAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef FakeMuMuTauMuTauEAnalyzer_cxx
FakeMuMuTauMuTauEAnalyzer::FakeMuMuTauMuTauEAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_, Long_t nMaxEvents_, bool isMC_, bool invertedEle1Iso_, double Ele1IsoThreshold_) : HistoZmumu() 
{
    fileName = fileName_;
    outputDir = outputDir_;
    lumiScale = lumiScale_;
    summedWeights = summedWeights_;
    nMaxEvents = nMaxEvents_;
    isMC = isMC_;
    invertedEle1Iso = invertedEle1Iso_;
    Ele1IsoThreshold = Ele1IsoThreshold_;

    //--- Create output directory if necessary ---
    if (nMaxEvents > 0) {
        outputDir.Remove(TString::kTrailing, '/');
        outputDir += TString::Format("_%ldevts/", nMaxEvents);
        cout << "Output directory has been changed to " << outputDir << endl;
    }

    TString command = "mkdir -p " + outputDir;
    system(command);

    TChain *chain = new TChain("", "");
    TString treePath = fileName + "/ZMuMuInclusiveAnalyzer/objectTree";
    chain->Add(treePath);
    fChain = chain;
    Init();
}

string FakeMuMuTauMuTauEAnalyzer::createOutputFileName()
{
    ostringstream outputName;
    fileName.Replace(0, fileName.Last('/'), "");
    fileName.ReplaceAll(".root","");
    outputName << outputDir;
    outputName << "/";
    outputName << fileName;
    outputName << "_histogram";
    outputName << ".root";
    return outputName.str();
}

FakeMuMuTauMuTauEAnalyzer::~FakeMuMuTauMuTauEAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FakeMuMuTauMuTauEAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FakeMuMuTauMuTauEAnalyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void FakeMuMuTauMuTauEAnalyzer::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   recoMuonPt = 0;
   recoMuonEta = 0;
   recoMuonPhi = 0;
   recoMuonEnergy = 0;
   recoMuonPDGId = 0;
   recoMuonIsolation = 0;
   recoMuonDXY = 0;
   recoMuonDZ = 0;
   recoMuonNTrackerLayers = 0;
   recoMuonTriggerFlag = 0;
   recoElectronPt = 0;
   recoElectronEta = 0;
   recoElectronPhi = 0;
   recoElectronEnergy = 0;
   recoElectronPDGId = 0;
   recoElectronIsolation = 0;
   recoElectronEcalTrkEnergyPostCorr = 0;
   recoElectronEcalTrkEnergyErrPostCorr = 0;
   recoJetPt = 0;
   recoJetEta = 0;
   recoJetPhi = 0;
   recoJetEnergy = 0;
   recoJetCSV = 0;
   recoMET = 0;
   recoMETPhi = 0;
   recoMETPx = 0;
   recoMETPy = 0;
   // Set branch addresses and branch pointers
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("recoMuonPt", &recoMuonPt, &b_recoMuonPt);
   fChain->SetBranchAddress("recoMuonEta", &recoMuonEta, &b_recoMuonEta);
   fChain->SetBranchAddress("recoMuonPhi", &recoMuonPhi, &b_recoMuonPhi);
   fChain->SetBranchAddress("recoMuonEnergy", &recoMuonEnergy, &b_recoMuonEnergy);
   fChain->SetBranchAddress("recoMuonPDGId", &recoMuonPDGId, &b_recoMuonPDGId);
   fChain->SetBranchAddress("recoMuonIsolation", &recoMuonIsolation, &b_recoMuonIsolation);
   fChain->SetBranchAddress("recoMuonDXY", &recoMuonDXY, &b_recoMuonDXY);
   fChain->SetBranchAddress("recoMuonDZ", &recoMuonDZ, &b_recoMuonDZ);
   fChain->SetBranchAddress("recoMuonNTrackerLayers", &recoMuonNTrackerLayers, &b_recoMuonNTrackerLayers);
   fChain->SetBranchAddress("recoMuonTriggerFlag", &recoMuonTriggerFlag, &b_recoMuonTriggerFlag);
   fChain->SetBranchAddress("recoElectronPt", &recoElectronPt, &b_recoElectronPt);
   fChain->SetBranchAddress("recoElectronEta", &recoElectronEta, &b_recoElectronEta);
   fChain->SetBranchAddress("recoElectronPhi", &recoElectronPhi, &b_recoElectronPhi);
   fChain->SetBranchAddress("recoElectronEnergy", &recoElectronEnergy, &b_recoElectronEnergy);
   fChain->SetBranchAddress("recoElectronPDGId", &recoElectronPDGId, &b_recoElectronPDGId);
   fChain->SetBranchAddress("recoElectronIsolation", &recoElectronIsolation, &b_recoElectronIsolation);
   fChain->SetBranchAddress("recoElectronEcalTrkEnergyPostCorr", &recoElectronEcalTrkEnergyPostCorr, &b_recoElectronEcalTrkEnergyPostCorr);
   fChain->SetBranchAddress("recoElectronEcalTrkEnergyErrPostCorr", &recoElectronEcalTrkEnergyErrPostCorr, &b_recoElectronEcalTrkEnergyErrPostCorr);
   fChain->SetBranchAddress("recoJetPt", &recoJetPt, &b_recoJetPt);
   fChain->SetBranchAddress("recoJetEta", &recoJetEta, &b_recoJetEta);
   fChain->SetBranchAddress("recoJetPhi", &recoJetPhi, &b_recoJetPhi);
   fChain->SetBranchAddress("recoJetEnergy", &recoJetEnergy, &b_recoJetEnergy);
   fChain->SetBranchAddress("recoJetCSV", &recoJetCSV, &b_recoJetCSV);
   fChain->SetBranchAddress("recoMET", &recoMET, &b_recoMET);
   fChain->SetBranchAddress("recoMETPhi", &recoMETPhi, &b_recoMETPhi);
   fChain->SetBranchAddress("recoMETPx", &recoMETPx, &b_recoMETPx);
   fChain->SetBranchAddress("recoMETPy", &recoMETPy, &b_recoMETPy);
   fChain->SetBranchAddress("recoNPrimaryVertex", &recoNPrimaryVertex, &b_recoNPrimaryVertex);
   fChain->SetBranchAddress("eventID", &eventID, &b_eventID);
   if (isMC) 
   {
       fChain->SetBranchAddress("recoNPU", &recoNPU, &b_recoNPU);
       fChain->SetBranchAddress("trueNInteraction", &trueNInteraction, &b_trueNInteraction);
       fChain->SetBranchAddress("genEventWeight", &genEventWeight, &b_genEventWeight);
   } // end if isMC
   Notify();
}

Bool_t FakeMuMuTauMuTauEAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void FakeMuMuTauMuTauEAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t FakeMuMuTauMuTauEAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef FakeMuMuTauMuTauEAnalyzer_cxx
