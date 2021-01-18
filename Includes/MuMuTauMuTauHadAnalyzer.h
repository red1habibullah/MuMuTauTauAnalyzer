//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 18 14:19:21 2019 by ROOT version 6.10/08
// from TTree objectTree/objectTree
// found on file: MuMuTauTauTreelization.root
//////////////////////////////////////////////////////////

#ifndef MuMuTauMuTauHadAnalyzer_h
#define MuMuTauMuTauHadAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Histomutau.h"

class MuMuTauMuTauHadAnalyzer : public Histomutau {
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
   vector<int>     *recoMuonRefToElectron;
   vector<int>     *recoMuonRefToTau;
   vector<int>     *recoMuonIdLoose;
   vector<int>     *recoMuonIdMedium;
   vector<int>     *recoMuonIdTight;
   vector<float>   *recoTauPt;
   vector<float>   *recoTauEta;
   vector<float>   *recoTauPhi;
   vector<float>   *recoTauEnergy;
   vector<int>     *recoTauPDGId;
   vector<float>   *recoTauDecayMode;
   vector<float>   *recoTauDecayModeFinding;
   vector<float>   *recoTauDecayModeFindingNewDMs;
   vector<int>     *recoTauRefToMuon;
   vector<int>     *recoTauRefToElectron;
   vector<float>   *recoTauDeepVSeraw;
   vector<float>   *recoTauDeepVSjetraw;
   vector<float>   *recoTauDeepVSmuraw;
   vector<float>   *recoTauDeepVSeLoose;
   vector<float>   *recoTauDeepVSjetLoose;
   vector<float>   *recoTauDeepVSmuLoose;
   vector<float>   *recoTauDeepVSeMedium;
   vector<float>   *recoTauDeepVSjetMedium;
   vector<float>   *recoTauDeepVSmuMedium;
   vector<float>   *recoTauDeepVSeTight;
   vector<float>   *recoTauDeepVSjetTight;
   vector<float>   *recoTauDeepVSmuTight;
   vector<float>   *recoTauDeepVSeVLoose;
   vector<float>   *recoTauDeepVSjetVLoose;
   vector<float>   *recoTauDeepVSmuVLoose;
   vector<float>   *recoTauDeepVSeVTight;
   vector<float>   *recoTauDeepVSjetVTight;
   vector<float>   *recoTauDeepVSeVVLoose;
   vector<float>   *recoTauDeepVSjetVVLoose;
   vector<float>   *recoTauDeepVSeVVTight;
   vector<float>   *recoTauDeepVSjetVVTight;
   vector<float>   *recoTauDeepVSeVVVLoose;
   vector<float>   *recoTauDeepVSjetVVVLoose;
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
   TBranch        *b_recoMuonRefToElectron;   //!
   TBranch        *b_recoMuonRefToTau;   //!
   TBranch        *b_recoMuonIdLoose;   //!
   TBranch        *b_recoMuonIdMedium;   //!
   TBranch        *b_recoMuonIdTight;   //!
   TBranch        *b_recoTauPt;   //!
   TBranch        *b_recoTauEta;   //!
   TBranch        *b_recoTauPhi;   //!
   TBranch        *b_recoTauEnergy;   //!
   TBranch        *b_recoTauPDGId;   //!
   TBranch        *b_recoTauDecayMode;   //!
   TBranch        *b_recoTauDecayModeFinding;   //!
   TBranch        *b_recoTauDecayModeFindingNewDMs;   //!
   TBranch        *b_recoTauRefToMuon;   //!
   TBranch        *b_recoTauRefToElectron;   //!
   TBranch        *b_recoTauDeepVSeraw;   //!
   TBranch        *b_recoTauDeepVSjetraw;   //!
   TBranch        *b_recoTauDeepVSmuraw;   //!
   TBranch        *b_recoTauDeepVSeLoose;   //!
   TBranch        *b_recoTauDeepVSjetLoose;   //!
   TBranch        *b_recoTauDeepVSmuLoose;   //!
   TBranch        *b_recoTauDeepVSeMedium;   //!
   TBranch        *b_recoTauDeepVSjetMedium;   //!
   TBranch        *b_recoTauDeepVSmuMedium;   //!
   TBranch        *b_recoTauDeepVSeTight;   //!
   TBranch        *b_recoTauDeepVSjetTight;   //!
   TBranch        *b_recoTauDeepVSmuTight;   //!
   TBranch        *b_recoTauDeepVSeVLoose;   //!
   TBranch        *b_recoTauDeepVSjetVLoose;   //!
   TBranch        *b_recoTauDeepVSmuVLoose;   //!
   TBranch        *b_recoTauDeepVSeVTight;   //!
   TBranch        *b_recoTauDeepVSjetVTight;   //!
   TBranch        *b_recoTauDeepVSeVVLoose;   //!
   TBranch        *b_recoTauDeepVSjetVVLoose;   //!
   TBranch        *b_recoTauDeepVSeVVTight;   //!
   TBranch        *b_recoTauDeepVSjetVVTight;   //!
   TBranch        *b_recoTauDeepVSeVVVLoose;   //!
   TBranch        *b_recoTauDeepVSjetVVVLoose;   //!
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
   double Mu1IsoThreshold;
   double Mu2IsoThreshold;
   double MuIsoUpperBound;
   TString MuonId;
   double diMuonMassLowThreshold;
   double diMuonMassHighThreshold;
   bool tauMVAIsoRawORWP;
   double tauMVAIsoRawThreshold;
   TString tauMVAIsoWP;
   TString tauAntiMuDisc;
   TString tauAntiEleDisc;
   bool deepTauID;
   TString deepTauVSele;
   TString deepTauVSmu;
   TString deepTauVSjet;
   double tauDecayModeThreshold;
   int muonScaleSyst;
   double tauScaleCorr;
   TString rochesterFile;

   MuMuTauMuTauHadAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_ = 1.0, Long_t nMaxEvents_ = 0, bool isMC_ = false, bool invertedMu2Iso_ = false, bool invertedTauIso_ = false, double Mu1IsoThreshold_ = 0.25, double Mu2IsoThreshold_ = 0.25, double MuIsoUpperBound_ = 0.4, TString MuonId_ = "LOOSE", double diMuonMassLowThreshold_ = 0, double diMuonMassHighThreshold_ = 25.0, bool tauMVAIsoRawORWP_ = false, double tauMVAIsoRawThreshold_ = -0.5, TString tauMVAIsoWP_ = "MEDIUM", TString tauAntiMuDisc_ = "NULL", TString tauAntiEleDisc_ = "NULL", bool deepTauID_ = false, TString deepTauVSele_ = "LOOSE", TString deepTauVSmu_ = "LOOSE", TString deepTauVSjet_ = "MEDIUM", double tauDecayModeThreshold_ = -1, int muonScaleSyst_ = 0, double tauScaleCorr_ = 1.0, TString rochesterFile_ = "");
   string createOutputFileName();
   virtual ~MuMuTauMuTauHadAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MuMuTauMuTauHadAnalyzer_cxx
MuMuTauMuTauHadAnalyzer::MuMuTauMuTauHadAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_, Long_t nMaxEvents_, bool isMC_, bool invertedMu2Iso_, bool invertedTauIso_, double Mu1IsoThreshold_, double Mu2IsoThreshold_, double MuIsoUpperBound_, TString MuonId_, double diMuonMassLowThreshold_, double diMuonMassHighThreshold_, bool tauMVAIsoRawORWP_, double tauMVAIsoRawThreshold_, TString tauMVAIsoWP_, TString tauAntiMuDisc_, TString tauAntiEleDisc_, bool deepTauID_, TString deepTauVSele_, TString deepTauVSmu_, TString deepTauVSjet_, double tauDecayModeThreshold_, int muonScaleSyst_, double tauScaleCorr_, TString rochesterFile_) : Histomutau() 
{
    fileName = fileName_;
    outputDir = outputDir_;
    lumiScale = lumiScale_;
    summedWeights = summedWeights_;
    nMaxEvents = nMaxEvents_;
    isMC = isMC_;
    invertedMu2Iso = invertedMu2Iso_;
    invertedTauIso = invertedTauIso_;
    Mu1IsoThreshold = Mu1IsoThreshold_;
    Mu2IsoThreshold = Mu2IsoThreshold_;
    MuIsoUpperBound = MuIsoUpperBound_;
    MuonId = MuonId_;
    diMuonMassLowThreshold = diMuonMassLowThreshold_;
    diMuonMassHighThreshold = diMuonMassHighThreshold_;
    tauMVAIsoRawORWP = tauMVAIsoRawORWP_;
    tauMVAIsoRawThreshold = tauMVAIsoRawThreshold_;
    tauMVAIsoWP = tauMVAIsoWP_;
    tauAntiMuDisc = tauAntiMuDisc_;
    tauAntiEleDisc = tauAntiEleDisc_;
    deepTauID = deepTauID_;
    deepTauVSele = deepTauVSele_;
    deepTauVSmu = deepTauVSmu_;
    deepTauVSjet = deepTauVSjet_;
    tauDecayModeThreshold = tauDecayModeThreshold_;
    muonScaleSyst = muonScaleSyst_;
    tauScaleCorr = tauScaleCorr_;
    rochesterFile = rochesterFile_;
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

string MuMuTauMuTauHadAnalyzer::createOutputFileName()
{
    ostringstream outputName;
    fileName.Replace(0, fileName.Last('/'), "");
    fileName.ReplaceAll(".root","");
    outputName << outputDir;
    outputName << "/";
    outputName << fileName;
    outputName << "_histogram";
    outputName << "_dRTest";
    outputName << ".root";
    return outputName.str();
}

MuMuTauMuTauHadAnalyzer::~MuMuTauMuTauHadAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MuMuTauMuTauHadAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MuMuTauMuTauHadAnalyzer::LoadTree(Long64_t entry)
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

void MuMuTauMuTauHadAnalyzer::Init()
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
   recoMuonRefToElectron = 0;
   recoMuonRefToTau = 0;
   recoMuonIdLoose = 0;
   recoMuonIdMedium = 0;
   recoMuonIdTight = 0;
   recoTauPt = 0;
   recoTauEta = 0;
   recoTauPhi = 0;
   recoTauEnergy = 0;
   recoTauPDGId = 0;
   recoTauDecayMode = 0;
   recoTauDecayModeFinding = 0;
   recoTauDecayModeFindingNewDMs = 0;
   recoTauRefToMuon = 0;
   recoTauRefToElectron = 0;
   recoTauDeepVSeraw = 0;
   recoTauDeepVSjetraw = 0;
   recoTauDeepVSmuraw = 0;
   recoTauDeepVSeLoose = 0;
   recoTauDeepVSjetLoose = 0;
   recoTauDeepVSmuLoose = 0;
   recoTauDeepVSeMedium = 0;
   recoTauDeepVSjetMedium = 0;
   recoTauDeepVSmuMedium = 0;
   recoTauDeepVSeTight = 0;
   recoTauDeepVSjetTight = 0;
   recoTauDeepVSmuTight = 0;
   recoTauDeepVSeVLoose = 0;
   recoTauDeepVSjetVLoose = 0;
   recoTauDeepVSmuVLoose = 0;
   recoTauDeepVSeVTight = 0;
   recoTauDeepVSjetVTight = 0;
   recoTauDeepVSeVVLoose = 0;
   recoTauDeepVSjetVVLoose = 0;
   recoTauDeepVSeVVTight = 0;
   recoTauDeepVSjetVVTight = 0;
   recoTauDeepVSeVVVLoose = 0;
   recoTauDeepVSjetVVVLoose = 0;
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
   fChain->SetBranchAddress("recoMuonRefToElectron", &recoMuonRefToElectron, &b_recoMuonRefToElectron);
   fChain->SetBranchAddress("recoMuonRefToTau", &recoMuonRefToTau, &b_recoMuonRefToTau);
   fChain->SetBranchAddress("recoMuonIdLoose", &recoMuonIdLoose, &b_recoMuonIdLoose);
   fChain->SetBranchAddress("recoMuonIdMedium", &recoMuonIdMedium, &b_recoMuonIdMedium);
   fChain->SetBranchAddress("recoMuonIdTight", &recoMuonIdTight, &b_recoMuonIdTight);
   fChain->SetBranchAddress("recoTauPt", &recoTauPt, &b_recoTauPt);
   fChain->SetBranchAddress("recoTauEta", &recoTauEta, &b_recoTauEta);
   fChain->SetBranchAddress("recoTauPhi", &recoTauPhi, &b_recoTauPhi);
   fChain->SetBranchAddress("recoTauEnergy", &recoTauEnergy, &b_recoTauEnergy);
   fChain->SetBranchAddress("recoTauPDGId", &recoTauPDGId, &b_recoTauPDGId);
   fChain->SetBranchAddress("recoTauDecayMode", &recoTauDecayMode, &b_recoTauDecayMode);
   fChain->SetBranchAddress("recoTauDecayModeFinding", &recoTauDecayModeFinding, &b_recoTauDecayModeFinding);
   fChain->SetBranchAddress("recoTauDecayModeFindingNewDMs", &recoTauDecayModeFindingNewDMs, &b_recoTauDecayModeFindingNewDMs);
   fChain->SetBranchAddress("recoTauRefToMuon", &recoTauRefToMuon, &b_recoTauRefToMuon);
   fChain->SetBranchAddress("recoTauRefToElectron", &recoTauRefToElectron, &b_recoTauRefToElectron);
   
   if (deepTauID)
   {
       fChain->SetBranchAddress("recoTauDeepVSeraw", &recoTauDeepVSeraw, &b_recoTauDeepVSeraw);
       fChain->SetBranchAddress("recoTauDeepVSjetraw", &recoTauDeepVSjetraw, &b_recoTauDeepVSjetraw);
       fChain->SetBranchAddress("recoTauDeepVSmuraw", &recoTauDeepVSmuraw, &b_recoTauDeepVSmuraw);
       fChain->SetBranchAddress("recoTauDeepVSeLoose", &recoTauDeepVSeLoose, &b_recoTauDeepVSeLoose);
       fChain->SetBranchAddress("recoTauDeepVSjetLoose", &recoTauDeepVSjetLoose, &b_recoTauDeepVSjetLoose);
       fChain->SetBranchAddress("recoTauDeepVSmuLoose", &recoTauDeepVSmuLoose, &b_recoTauDeepVSmuLoose);
       fChain->SetBranchAddress("recoTauDeepVSeMedium", &recoTauDeepVSeMedium, &b_recoTauDeepVSeMedium);
       fChain->SetBranchAddress("recoTauDeepVSjetMedium", &recoTauDeepVSjetMedium, &b_recoTauDeepVSjetMedium);
       fChain->SetBranchAddress("recoTauDeepVSmuMedium", &recoTauDeepVSmuMedium, &b_recoTauDeepVSmuMedium);
       fChain->SetBranchAddress("recoTauDeepVSeTight", &recoTauDeepVSeTight, &b_recoTauDeepVSeTight);
       fChain->SetBranchAddress("recoTauDeepVSjetTight", &recoTauDeepVSjetTight, &b_recoTauDeepVSjetTight);
       fChain->SetBranchAddress("recoTauDeepVSmuTight", &recoTauDeepVSmuTight, &b_recoTauDeepVSmuTight);
       fChain->SetBranchAddress("recoTauDeepVSeVLoose", &recoTauDeepVSeVLoose, &b_recoTauDeepVSeVLoose);
       fChain->SetBranchAddress("recoTauDeepVSjetVLoose", &recoTauDeepVSjetVLoose, &b_recoTauDeepVSjetVLoose);
       fChain->SetBranchAddress("recoTauDeepVSmuVLoose", &recoTauDeepVSmuVLoose, &b_recoTauDeepVSmuVLoose);
       fChain->SetBranchAddress("recoTauDeepVSeVTight", &recoTauDeepVSeVTight, &b_recoTauDeepVSeVTight);
       fChain->SetBranchAddress("recoTauDeepVSjetVTight", &recoTauDeepVSjetVTight, &b_recoTauDeepVSjetVTight);
       fChain->SetBranchAddress("recoTauDeepVSeVVLoose", &recoTauDeepVSeVVLoose, &b_recoTauDeepVSeVVLoose);
       fChain->SetBranchAddress("recoTauDeepVSjetVVLoose", &recoTauDeepVSjetVVLoose, &b_recoTauDeepVSjetVVLoose);
       fChain->SetBranchAddress("recoTauDeepVSeVVTight", &recoTauDeepVSeVVTight, &b_recoTauDeepVSeVVTight);
       fChain->SetBranchAddress("recoTauDeepVSjetVVTight", &recoTauDeepVSjetVVTight, &b_recoTauDeepVSjetVVTight);
       fChain->SetBranchAddress("recoTauDeepVSeVVVLoose", &recoTauDeepVSeVVVLoose, &b_recoTauDeepVSeVVVLoose);
       fChain->SetBranchAddress("recoTauDeepVSjetVVVLoose", &recoTauDeepVSjetVVVLoose, &b_recoTauDeepVSjetVVVLoose);
   } // end if deepTauID

   else{
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
   } // end if not deepTauID

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

Bool_t MuMuTauMuTauHadAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MuMuTauMuTauHadAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MuMuTauMuTauHadAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MuMuTauMuTauHadAnalyzer_cxx
