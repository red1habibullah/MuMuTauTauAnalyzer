//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 18 14:19:21 2019 by ROOT version 6.10/08
// from TTree objectTree/objectTree
// found on file: MuMuTauTauTreelization.root
//////////////////////////////////////////////////////////

#ifndef MuMuTauETauHadAnalyzer_h
#define MuMuTauETauHadAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Histomutau.h"

class MuMuTauETauHadAnalyzer : public Histomutau {
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
   vector<float>   *recoTauPt;
   vector<float>   *recoTauEta;
   vector<float>   *recoTauPhi;
   vector<float>   *recoTauEnergy;
   vector<int>     *recoTauPDGId;
   vector<float>   *recoTauDecayMode;
   vector<float>   *recoTauIsoMVArawValue;
   vector<float>   *recoTauIsoMVAVVLoose;
   vector<float>   *recoTauIsoMVAVLoose;
   vector<float>   *recoTauIsoMVALoose;
   vector<float>   *recoTauIsoMVAMedium;
   vector<float>   *recoTauIsoMVATight;
   vector<float>   *recoTauIsoMVAVTight;
   vector<float>   *recoTauIsoMVAVVTight;
   vector<float>   *recoTauAntiMuMVALoose;
   vector<float>   *recoTauAntiMuMVATight;
   vector<float>   *recoTauAntiEleMVArawValue;
   vector<float>   *recoTauAntiEleMVAVLoose;
   vector<float>   *recoTauAntiEleMVALoose;
   vector<float>   *recoTauAntiEleMVAMedium;
   vector<float>   *recoTauAntiEleMVATight;
   vector<float>   *recoTauAntiEleMVAVTight;
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
   TBranch        *b_recoTauPt;   //!
   TBranch        *b_recoTauEta;   //!
   TBranch        *b_recoTauPhi;   //!
   TBranch        *b_recoTauEnergy;   //!
   TBranch        *b_recoTauPDGId;   //!
   TBranch        *b_recoTauDecayMode;   //!
   TBranch        *b_recoTauIsoMVArawValue;   //!
   TBranch        *b_recoTauIsoMVAVVLoose;   //!
   TBranch        *b_recoTauIsoMVAVLoose;   //!
   TBranch        *b_recoTauIsoMVALoose;   //!
   TBranch        *b_recoTauIsoMVAMedium;   //!
   TBranch        *b_recoTauIsoMVATight;   //!
   TBranch        *b_recoTauIsoMVAVTight;   //!
   TBranch        *b_recoTauIsoMVAVVTight;   //!
   TBranch        *b_recoTauAntiMuMVALoose;   //!
   TBranch        *b_recoTauAntiMuMVATight;   //!
   TBranch        *b_recoTauAntiEleMVArawValue;   //!
   TBranch        *b_recoTauAntiEleMVAVLoose;   //!
   TBranch        *b_recoTauAntiEleMVALoose;   //!
   TBranch        *b_recoTauAntiEleMVAMedium;   //!
   TBranch        *b_recoTauAntiEleMVATight;   //!
   TBranch        *b_recoTauAntiEleMVAVTight;   //!
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
   bool invertedMu2Iso;
   bool invertedTauIso;
   double Mu2IsoThreshold;
   double diMuonMassLowThreshold;
   double diMuonMassHighThreshold;

   MuMuTauETauHadAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_ = 1.0, Long_t nMaxEvents_ = 0, bool isMC_ = false, bool invertedMu2Iso_ = false, bool invertedTauIso_ = false, double Mu2IsoThreshold_ = 0.25, double diMuonMassLowThreshold_ = 0, double diMuonMassHighThreshold_ = 25.0);
   string createOutputFileName();
   virtual ~MuMuTauETauHadAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MuMuTauETauHadAnalyzer_cxx
MuMuTauETauHadAnalyzer::MuMuTauETauHadAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_, Long_t nMaxEvents_, bool isMC_, bool invertedMu2Iso_, bool invertedTauIso_, double Mu2IsoThreshold_, double diMuonMassLowThreshold_, double diMuonMassHighThreshold_) : Histomutau() 
{
    fileName = fileName_;
    outputDir = outputDir_;
    lumiScale = lumiScale_;
    summedWeights = summedWeights_;
    nMaxEvents = nMaxEvents_;
    isMC = isMC_;
    invertedMu2Iso = invertedMu2Iso_;
    invertedTauIso = invertedTauIso_;
    Mu2IsoThreshold = Mu2IsoThreshold_;
    diMuonMassLowThreshold = diMuonMassLowThreshold_;
    diMuonMassHighThreshold = diMuonMassHighThreshold_;
    invMassMu1Mu2->SetBins(20, diMuonMassLowThreshold, diMuonMassHighThreshold);

    //--- Create output directory if necessary ---
    if (nMaxEvents > 0) {
        outputDir.Remove(TString::kTrailing, '/');
        outputDir += TString::Format("_%ldevts/", nMaxEvents);
        cout << "Output directory has been changed to " << outputDir << endl;
    }

    TString command = "mkdir -p " + outputDir;
    system(command);

    TChain *chain = new TChain("", "");
    TString treePath = fileName + "/DiMuDiTauAnalyzer/objectTree";
    chain->Add(treePath);
    fChain = chain;
    Init();
}

string MuMuTauETauHadAnalyzer::createOutputFileName()
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

MuMuTauETauHadAnalyzer::~MuMuTauETauHadAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MuMuTauETauHadAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MuMuTauETauHadAnalyzer::LoadTree(Long64_t entry)
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

void MuMuTauETauHadAnalyzer::Init()
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
   recoTauPt = 0;
   recoTauEta = 0;
   recoTauPhi = 0;
   recoTauEnergy = 0;
   recoTauPDGId = 0;
   recoTauDecayMode = 0;
   recoTauIsoMVArawValue = 0;
   recoTauIsoMVAVVLoose = 0;
   recoTauIsoMVAVLoose = 0;
   recoTauIsoMVALoose = 0;
   recoTauIsoMVAMedium = 0;
   recoTauIsoMVATight = 0;
   recoTauIsoMVAVTight = 0;
   recoTauIsoMVAVVTight = 0;
   recoTauAntiMuMVALoose = 0;
   recoTauAntiMuMVATight = 0;
   recoTauAntiEleMVArawValue = 0;
   recoTauAntiEleMVAVLoose = 0;
   recoTauAntiEleMVALoose = 0;
   recoTauAntiEleMVAMedium = 0;
   recoTauAntiEleMVATight = 0;
   recoTauAntiEleMVAVTight = 0;
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
   fChain->SetBranchAddress("recoTauPt", &recoTauPt, &b_recoTauPt);
   fChain->SetBranchAddress("recoTauEta", &recoTauEta, &b_recoTauEta);
   fChain->SetBranchAddress("recoTauPhi", &recoTauPhi, &b_recoTauPhi);
   fChain->SetBranchAddress("recoTauEnergy", &recoTauEnergy, &b_recoTauEnergy);
   fChain->SetBranchAddress("recoTauPDGId", &recoTauPDGId, &b_recoTauPDGId);
   fChain->SetBranchAddress("recoTauDecayMode", &recoTauDecayMode, &b_recoTauDecayMode);
   fChain->SetBranchAddress("recoTauIsoMVArawValue", &recoTauIsoMVArawValue, &b_recoTauIsoMVArawValue);
   fChain->SetBranchAddress("recoTauIsoMVAVVLoose", &recoTauIsoMVAVVLoose, &b_recoTauIsoMVAVVLoose);
   fChain->SetBranchAddress("recoTauIsoMVAVLoose", &recoTauIsoMVAVLoose, &b_recoTauIsoMVAVLoose);
   fChain->SetBranchAddress("recoTauIsoMVALoose", &recoTauIsoMVALoose, &b_recoTauIsoMVALoose);
   fChain->SetBranchAddress("recoTauIsoMVAMedium", &recoTauIsoMVAMedium, &b_recoTauIsoMVAMedium);
   fChain->SetBranchAddress("recoTauIsoMVATight", &recoTauIsoMVATight, &b_recoTauIsoMVATight);
   fChain->SetBranchAddress("recoTauIsoMVAVTight", &recoTauIsoMVAVTight, &b_recoTauIsoMVAVTight);
   fChain->SetBranchAddress("recoTauIsoMVAVVTight", &recoTauIsoMVAVVTight, &b_recoTauIsoMVAVVTight);
   fChain->SetBranchAddress("recoTauAntiMuMVALoose", &recoTauAntiMuMVALoose, &b_recoTauAntiMuMVALoose);
   fChain->SetBranchAddress("recoTauAntiMuMVATight", &recoTauAntiMuMVATight, &b_recoTauAntiMuMVATight);
   fChain->SetBranchAddress("recoTauAntiEleMVArawValue", &recoTauAntiEleMVArawValue, &b_recoTauAntiEleMVArawValue);
   fChain->SetBranchAddress("recoTauAntiEleMVAVLoose", &recoTauAntiEleMVAVLoose, &b_recoTauAntiEleMVAVLoose);
   fChain->SetBranchAddress("recoTauAntiEleMVALoose", &recoTauAntiEleMVALoose, &b_recoTauAntiEleMVALoose);
   fChain->SetBranchAddress("recoTauAntiEleMVAMedium", &recoTauAntiEleMVAMedium, &b_recoTauAntiEleMVAMedium);
   fChain->SetBranchAddress("recoTauAntiEleMVATight", &recoTauAntiEleMVATight, &b_recoTauAntiEleMVATight);
   fChain->SetBranchAddress("recoTauAntiEleMVAVTight", &recoTauAntiEleMVAVTight, &b_recoTauAntiEleMVAVTight);
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

Bool_t MuMuTauETauHadAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MuMuTauETauHadAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MuMuTauETauHadAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MuMuTauETauHadAnalyzer_cxx
