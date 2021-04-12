//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 18 14:19:21 2019 by ROOT version 6.10/08
// from TTree objectTree/objectTree
// found on file: MuMuTauTauTreelization.root
//////////////////////////////////////////////////////////

#ifndef MuMuTauTauInclusiveAnalyzer_h
#define MuMuTauTauInclusiveAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "FlatTreeMuMuTauTau.h"

class MuMuTauTauInclusiveAnalyzer : public FlatTreeMuMuTauTau {
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
   vector<int>     *recoMuonRefToTauMuonCleaned;
   vector<int>     *recoMuonIdLoose;
   vector<int>     *recoMuonIdMedium;
   vector<int>     *recoMuonIdTight;
   vector<float>   *recoElectronPt;
   vector<float>   *recoElectronEta;
   vector<float>   *recoElectronPhi;
   vector<float>   *recoElectronEnergy;
   vector<int>     *recoElectronPDGId;
   vector<float>   *recoElectronIsolation;
   vector<int>     *recoElectronIdLoose;
   vector<int>     *recoElectronIdMedium;
   vector<int>     *recoElectronIdTight;
   vector<int>     *recoElectronIdLooseNoIso;
   vector<int>     *recoElectronIdMediumNoIso;
   vector<int>     *recoElectronIdTightNoIso;
   vector<float>   *recoElectronEcalTrkEnergyPostCorr;
   vector<float>   *recoElectronEcalTrkEnergyErrPostCorr;
   vector<float>   *recoElectronEnergyScaleValue;
   vector<float>   *recoElectronEnergyScaleUp;
   vector<float>   *recoElectronEnergyScaleDown;
   vector<float>   *recoElectronEnergySigmaValue;
   vector<float>   *recoElectronEnergySigmaUp;
   vector<float>   *recoElectronEnergySigmaDown;
   vector<int>     *recoElectronRefToMuon;
   vector<int>     *recoElectronRefToTau;
   vector<int>     *recoElectronRefToTauElectronCleaned;
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
   vector<float>   *recoTauMuonCleanedPt;
   vector<float>   *recoTauMuonCleanedEta;
   vector<float>   *recoTauMuonCleanedPhi;
   vector<float>   *recoTauMuonCleanedEnergy;
   vector<int>     *recoTauMuonCleanedPDGId;
   vector<float>   *recoTauMuonCleanedDecayMode;
   vector<float>   *recoTauMuonCleanedDecayModeFinding;
   vector<float>   *recoTauMuonCleanedDecayModeFindingNewDMs;
   vector<int>     *recoTauMuonCleanedRefToMuon;
   vector<int>     *recoTauMuonCleanedRefToElectron;
   vector<float>   *recoTauMuonCleanedDeepVSeraw;
   vector<float>   *recoTauMuonCleanedDeepVSjetraw;
   vector<float>   *recoTauMuonCleanedDeepVSmuraw;
   vector<float>   *recoTauMuonCleanedDeepVSeLoose;
   vector<float>   *recoTauMuonCleanedDeepVSjetLoose;
   vector<float>   *recoTauMuonCleanedDeepVSmuLoose;
   vector<float>   *recoTauMuonCleanedDeepVSeMedium;
   vector<float>   *recoTauMuonCleanedDeepVSjetMedium;
   vector<float>   *recoTauMuonCleanedDeepVSmuMedium;
   vector<float>   *recoTauMuonCleanedDeepVSeTight;
   vector<float>   *recoTauMuonCleanedDeepVSjetTight;
   vector<float>   *recoTauMuonCleanedDeepVSmuTight;
   vector<float>   *recoTauMuonCleanedDeepVSeVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSjetVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSmuVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSeVTight;
   vector<float>   *recoTauMuonCleanedDeepVSjetVTight;
   vector<float>   *recoTauMuonCleanedDeepVSeVVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSjetVVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSeVVTight;
   vector<float>   *recoTauMuonCleanedDeepVSjetVVTight;
   vector<float>   *recoTauMuonCleanedDeepVSeVVVLoose;
   vector<float>   *recoTauMuonCleanedDeepVSjetVVVLoose;
   vector<float>   *recoTauMuonCleanedIsoMVArawValue;
   vector<float>   *recoTauMuonCleanedIsoMVAVVLoose;
   vector<float>   *recoTauMuonCleanedIsoMVAVLoose;
   vector<float>   *recoTauMuonCleanedIsoMVALoose;
   vector<float>   *recoTauMuonCleanedIsoMVAMedium;
   vector<float>   *recoTauMuonCleanedIsoMVATight;
   vector<float>   *recoTauMuonCleanedIsoMVAVTight;
   vector<float>   *recoTauMuonCleanedIsoMVAVVTight;
   vector<float>   *recoTauMuonCleanedAntiMuMVALoose;
   vector<float>   *recoTauMuonCleanedAntiMuMVATight;
   vector<float>   *recoTauMuonCleanedAntiEleMVArawValue;
   vector<float>   *recoTauMuonCleanedAntiEleMVAVLoose;
   vector<float>   *recoTauMuonCleanedAntiEleMVALoose;
   vector<float>   *recoTauMuonCleanedAntiEleMVAMedium;
   vector<float>   *recoTauMuonCleanedAntiEleMVATight;
   vector<float>   *recoTauMuonCleanedAntiEleMVAVTight;
   vector<float>   *recoTauElectronCleanedPt;
   vector<float>   *recoTauElectronCleanedEta;
   vector<float>   *recoTauElectronCleanedPhi;
   vector<float>   *recoTauElectronCleanedEnergy;
   vector<int>     *recoTauElectronCleanedPDGId;
   vector<float>   *recoTauElectronCleanedDecayMode;
   vector<float>   *recoTauElectronCleanedDecayModeFinding;
   vector<float>   *recoTauElectronCleanedDecayModeFindingNewDMs;
   vector<int>     *recoTauElectronCleanedRefToMuon;
   vector<int>     *recoTauElectronCleanedRefToElectron;
   vector<float>   *recoTauElectronCleanedDeepVSeraw;
   vector<float>   *recoTauElectronCleanedDeepVSjetraw;
   vector<float>   *recoTauElectronCleanedDeepVSmuraw;
   vector<float>   *recoTauElectronCleanedDeepVSeLoose;
   vector<float>   *recoTauElectronCleanedDeepVSjetLoose;
   vector<float>   *recoTauElectronCleanedDeepVSmuLoose;
   vector<float>   *recoTauElectronCleanedDeepVSeMedium;
   vector<float>   *recoTauElectronCleanedDeepVSjetMedium;
   vector<float>   *recoTauElectronCleanedDeepVSmuMedium;
   vector<float>   *recoTauElectronCleanedDeepVSeTight;
   vector<float>   *recoTauElectronCleanedDeepVSjetTight;
   vector<float>   *recoTauElectronCleanedDeepVSmuTight;
   vector<float>   *recoTauElectronCleanedDeepVSeVLoose;
   vector<float>   *recoTauElectronCleanedDeepVSjetVLoose;
   vector<float>   *recoTauElectronCleanedDeepVSmuVLoose;
   vector<float>   *recoTauElectronCleanedDeepVSeVTight;
   vector<float>   *recoTauElectronCleanedDeepVSjetVTight;
   vector<float>   *recoTauElectronCleanedDeepVSeVVLoose;
   vector<float>   *recoTauElectronCleanedDeepVSjetVVLoose;
   vector<float>   *recoTauElectronCleanedDeepVSeVVTight;
   vector<float>   *recoTauElectronCleanedDeepVSjetVVTight;
   vector<float>   *recoTauElectronCleanedDeepVSeVVVLoose;
   vector<float>   *recoTauElectronCleanedDeepVSjetVVVLoose;
   vector<float>   *recoTauElectronCleanedIsoMVArawValue;
   vector<float>   *recoTauElectronCleanedIsoMVAVVLoose;
   vector<float>   *recoTauElectronCleanedIsoMVAVLoose;
   vector<float>   *recoTauElectronCleanedIsoMVALoose;
   vector<float>   *recoTauElectronCleanedIsoMVAMedium;
   vector<float>   *recoTauElectronCleanedIsoMVATight;
   vector<float>   *recoTauElectronCleanedIsoMVAVTight;
   vector<float>   *recoTauElectronCleanedIsoMVAVVTight;
   vector<float>   *recoTauElectronCleanedAntiMuMVALoose;
   vector<float>   *recoTauElectronCleanedAntiMuMVATight;
   vector<float>   *recoTauElectronCleanedAntiEleMVArawValue;
   vector<float>   *recoTauElectronCleanedAntiEleMVAVLoose;
   vector<float>   *recoTauElectronCleanedAntiEleMVALoose;
   vector<float>   *recoTauElectronCleanedAntiEleMVAMedium;
   vector<float>   *recoTauElectronCleanedAntiEleMVATight;
   vector<float>   *recoTauElectronCleanedAntiEleMVAVTight;
   vector<float>   *recoTauBoostedPt;
   vector<float>   *recoTauBoostedEta;
   vector<float>   *recoTauBoostedPhi;
   vector<float>   *recoTauBoostedEnergy;
   vector<int>     *recoTauBoostedPDGId;
   vector<float>   *recoTauBoostedDecayMode;
   vector<float>   *recoTauBoostedDecayModeFinding;
   vector<float>   *recoTauBoostedDecayModeFindingNewDMs;
   vector<int>     *recoTauBoostedRefToMuon;
   vector<int>     *recoTauBoostedRefToElectron;
   vector<float>   *recoTauBoostedDeepVSeraw;
   vector<float>   *recoTauBoostedDeepVSjetraw;
   vector<float>   *recoTauBoostedDeepVSmuraw;
   vector<float>   *recoTauBoostedDeepVSeLoose;
   vector<float>   *recoTauBoostedDeepVSjetLoose;
   vector<float>   *recoTauBoostedDeepVSmuLoose;
   vector<float>   *recoTauBoostedDeepVSeMedium;
   vector<float>   *recoTauBoostedDeepVSjetMedium;
   vector<float>   *recoTauBoostedDeepVSmuMedium;
   vector<float>   *recoTauBoostedDeepVSeTight;
   vector<float>   *recoTauBoostedDeepVSjetTight;
   vector<float>   *recoTauBoostedDeepVSmuTight;
   vector<float>   *recoTauBoostedDeepVSeVLoose;
   vector<float>   *recoTauBoostedDeepVSjetVLoose;
   vector<float>   *recoTauBoostedDeepVSmuVLoose;
   vector<float>   *recoTauBoostedDeepVSeVTight;
   vector<float>   *recoTauBoostedDeepVSjetVTight;
   vector<float>   *recoTauBoostedDeepVSeVVLoose;
   vector<float>   *recoTauBoostedDeepVSjetVVLoose;
   vector<float>   *recoTauBoostedDeepVSeVVTight;
   vector<float>   *recoTauBoostedDeepVSjetVVTight;
   vector<float>   *recoTauBoostedDeepVSeVVVLoose;
   vector<float>   *recoTauBoostedDeepVSjetVVVLoose;
   vector<float>   *recoTauBoostedIsoMVArawValue;
   vector<float>   *recoTauBoostedIsoMVAVVLoose;
   vector<float>   *recoTauBoostedIsoMVAVLoose;
   vector<float>   *recoTauBoostedIsoMVALoose;
   vector<float>   *recoTauBoostedIsoMVAMedium;
   vector<float>   *recoTauBoostedIsoMVATight;
   vector<float>   *recoTauBoostedIsoMVAVTight;
   vector<float>   *recoTauBoostedIsoMVAVVTight;
   vector<float>   *recoTauBoostedAntiMuMVALoose;
   vector<float>   *recoTauBoostedAntiMuMVATight;
   vector<float>   *recoTauBoostedAntiEleMVArawValue;
   vector<float>   *recoTauBoostedAntiEleMVAVLoose;
   vector<float>   *recoTauBoostedAntiEleMVALoose;
   vector<float>   *recoTauBoostedAntiEleMVAMedium;
   vector<float>   *recoTauBoostedAntiEleMVATight;
   vector<float>   *recoTauBoostedAntiEleMVAVTight;
   vector<float>   *recoJetPt;
   vector<float>   *recoJetEta;
   vector<float>   *recoJetPhi;
   vector<float>   *recoJetEnergy;
   vector<float>   *recoJetCSV;
   vector<float>   *recoJetDeepDiTauValue;
   vector<float>   *recoJetDeepDiTauValueMD;
   vector<int>     *recoJetIdLoose;
   vector<int>     *recoJetIdTight;
   vector<int>     *recoJetIdTightLepVeto;
   vector<int>     *recoJetIdPileUp;
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
   TBranch        *b_recoMuonRefToTauMuonCleaned;   //!
   TBranch        *b_recoMuonIdLoose;   //!
   TBranch        *b_recoMuonIdMedium;   //!
   TBranch        *b_recoMuonIdTight;   //!
   TBranch        *b_recoElectronPt;   //!
   TBranch        *b_recoElectronEta;   //!
   TBranch        *b_recoElectronPhi;   //!
   TBranch        *b_recoElectronEnergy;   //!
   TBranch        *b_recoElectronPDGId;   //!
   TBranch        *b_recoElectronIsolation;   //!
   TBranch        *b_recoElectronIdLoose;   //!
   TBranch        *b_recoElectronIdMedium;   //!
   TBranch        *b_recoElectronIdTight;   //!
   TBranch        *b_recoElectronIdLooseNoIso;   //!
   TBranch        *b_recoElectronIdMediumNoIso;   //!
   TBranch        *b_recoElectronIdTightNoIso;   //!
   TBranch        *b_recoElectronEcalTrkEnergyPostCorr;   //!
   TBranch        *b_recoElectronEcalTrkEnergyErrPostCorr;   //!
   TBranch        *b_recoElectronEnergyScaleValue;   //!
   TBranch        *b_recoElectronEnergyScaleUp;   //!
   TBranch        *b_recoElectronEnergyScaleDown;   //!
   TBranch        *b_recoElectronEnergySigmaValue;   //!
   TBranch        *b_recoElectronEnergySigmaUp;   //!
   TBranch        *b_recoElectronEnergySigmaDown;   //!
   TBranch        *b_recoElectronRefToMuon;   //!
   TBranch        *b_recoElectronRefToTau;   //!
   TBranch        *b_recoElectronRefToTauElectronCleaned;   //!
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
   TBranch        *b_recoTauMuonCleanedPt;   //!
   TBranch        *b_recoTauMuonCleanedEta;   //!
   TBranch        *b_recoTauMuonCleanedPhi;   //!
   TBranch        *b_recoTauMuonCleanedEnergy;   //!
   TBranch        *b_recoTauMuonCleanedPDGId;   //!
   TBranch        *b_recoTauMuonCleanedDecayMode;   //!
   TBranch        *b_recoTauMuonCleanedDecayModeFinding;   //!
   TBranch        *b_recoTauMuonCleanedDecayModeFindingNewDMs;   //!
   TBranch        *b_recoTauMuonCleanedRefToMuon;   //!
   TBranch        *b_recoTauMuonCleanedRefToElectron;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeraw;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetraw;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSmuraw;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSmuLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeMedium;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetMedium;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSmuMedium;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSmuTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSmuVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeVTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetVTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeVVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetVVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeVVTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetVVTight;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSeVVVLoose;   //!
   TBranch        *b_recoTauMuonCleanedDeepVSjetVVVLoose;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVArawValue;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVAVVLoose;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVAVLoose;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVALoose;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVAMedium;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVATight;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVAVTight;   //!
   TBranch        *b_recoTauMuonCleanedIsoMVAVVTight;   //!
   TBranch        *b_recoTauMuonCleanedAntiMuMVALoose;   //!
   TBranch        *b_recoTauMuonCleanedAntiMuMVATight;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVArawValue;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVAVLoose;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVALoose;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVAMedium;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVATight;   //!
   TBranch        *b_recoTauMuonCleanedAntiEleMVAVTight;   //!
   TBranch        *b_recoTauElectronCleanedPt;   //!
   TBranch        *b_recoTauElectronCleanedEta;   //!
   TBranch        *b_recoTauElectronCleanedPhi;   //!
   TBranch        *b_recoTauElectronCleanedEnergy;   //!
   TBranch        *b_recoTauElectronCleanedPDGId;   //!
   TBranch        *b_recoTauElectronCleanedDecayMode;   //!
   TBranch        *b_recoTauElectronCleanedDecayModeFinding;   //!
   TBranch        *b_recoTauElectronCleanedDecayModeFindingNewDMs;   //!
   TBranch        *b_recoTauElectronCleanedRefToMuon;   //!
   TBranch        *b_recoTauElectronCleanedRefToElectron;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSeraw;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSjetraw;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSmuraw;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSeLoose;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSjetLoose;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSmuLoose;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSeMedium;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSjetMedium;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSmuMedium;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSeTight;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSjetTight;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSmuTight;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSeVLoose;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSjetVLoose;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSmuVLoose;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSeVTight;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSjetVTight;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSeVVLoose;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSjetVVLoose;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSeVVTight;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSjetVVTight;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSeVVVLoose;   //!
   TBranch        *b_recoTauElectronCleanedDeepVSjetVVVLoose;   //!
   TBranch        *b_recoTauElectronCleanedIsoMVArawValue;   //!
   TBranch        *b_recoTauElectronCleanedIsoMVAVVLoose;   //!
   TBranch        *b_recoTauElectronCleanedIsoMVAVLoose;   //!
   TBranch        *b_recoTauElectronCleanedIsoMVALoose;   //!
   TBranch        *b_recoTauElectronCleanedIsoMVAMedium;   //!
   TBranch        *b_recoTauElectronCleanedIsoMVATight;   //!
   TBranch        *b_recoTauElectronCleanedIsoMVAVTight;   //!
   TBranch        *b_recoTauElectronCleanedIsoMVAVVTight;   //!
   TBranch        *b_recoTauElectronCleanedAntiMuMVALoose;   //!
   TBranch        *b_recoTauElectronCleanedAntiMuMVATight;   //!
   TBranch        *b_recoTauElectronCleanedAntiEleMVArawValue;   //!
   TBranch        *b_recoTauElectronCleanedAntiEleMVAVLoose;   //!
   TBranch        *b_recoTauElectronCleanedAntiEleMVALoose;   //!
   TBranch        *b_recoTauElectronCleanedAntiEleMVAMedium;   //!
   TBranch        *b_recoTauElectronCleanedAntiEleMVATight;   //!
   TBranch        *b_recoTauElectronCleanedAntiEleMVAVTight;   //!
   TBranch        *b_recoTauBoostedPt;   //!
   TBranch        *b_recoTauBoostedEta;   //!
   TBranch        *b_recoTauBoostedPhi;   //!
   TBranch        *b_recoTauBoostedEnergy;   //!
   TBranch        *b_recoTauBoostedPDGId;   //!
   TBranch        *b_recoTauBoostedDecayMode;   //!
   TBranch        *b_recoTauBoostedDecayModeFinding;   //!
   TBranch        *b_recoTauBoostedDecayModeFindingNewDMs;   //!
   TBranch        *b_recoTauBoostedRefToMuon;   //!
   TBranch        *b_recoTauBoostedRefToElectron;   //!
   TBranch        *b_recoTauBoostedDeepVSeraw;   //!
   TBranch        *b_recoTauBoostedDeepVSjetraw;   //!
   TBranch        *b_recoTauBoostedDeepVSmuraw;   //!
   TBranch        *b_recoTauBoostedDeepVSeLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSjetLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSmuLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSeMedium;   //!
   TBranch        *b_recoTauBoostedDeepVSjetMedium;   //!
   TBranch        *b_recoTauBoostedDeepVSmuMedium;   //!
   TBranch        *b_recoTauBoostedDeepVSeTight;   //!
   TBranch        *b_recoTauBoostedDeepVSjetTight;   //!
   TBranch        *b_recoTauBoostedDeepVSmuTight;   //!
   TBranch        *b_recoTauBoostedDeepVSeVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSjetVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSmuVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSeVTight;   //!
   TBranch        *b_recoTauBoostedDeepVSjetVTight;   //!
   TBranch        *b_recoTauBoostedDeepVSeVVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSjetVVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSeVVTight;   //!
   TBranch        *b_recoTauBoostedDeepVSjetVVTight;   //!
   TBranch        *b_recoTauBoostedDeepVSeVVVLoose;   //!
   TBranch        *b_recoTauBoostedDeepVSjetVVVLoose;   //!
   TBranch        *b_recoTauBoostedIsoMVArawValue;   //!
   TBranch        *b_recoTauBoostedIsoMVAVVLoose;   //!
   TBranch        *b_recoTauBoostedIsoMVAVLoose;   //!
   TBranch        *b_recoTauBoostedIsoMVALoose;   //!
   TBranch        *b_recoTauBoostedIsoMVAMedium;   //!
   TBranch        *b_recoTauBoostedIsoMVATight;   //!
   TBranch        *b_recoTauBoostedIsoMVAVTight;   //!
   TBranch        *b_recoTauBoostedIsoMVAVVTight;   //!
   TBranch        *b_recoTauBoostedAntiMuMVALoose;   //!
   TBranch        *b_recoTauBoostedAntiMuMVATight;   //!
   TBranch        *b_recoTauBoostedAntiEleMVArawValue;   //!
   TBranch        *b_recoTauBoostedAntiEleMVAVLoose;   //!
   TBranch        *b_recoTauBoostedAntiEleMVALoose;   //!
   TBranch        *b_recoTauBoostedAntiEleMVAMedium;   //!
   TBranch        *b_recoTauBoostedAntiEleMVATight;   //!
   TBranch        *b_recoTauBoostedAntiEleMVAVTight;   //!
   TBranch        *b_recoJetPt;   //!
   TBranch        *b_recoJetEta;   //!
   TBranch        *b_recoJetPhi;   //!
   TBranch        *b_recoJetEnergy;   //!
   TBranch        *b_recoJetCSV;   //!
   TBranch        *b_recoJetDeepDiTauValue;   //!
   TBranch        *b_recoJetDeepDiTauValueMD;   //!
   TBranch        *b_recoJetIdLoose;   //!
   TBranch        *b_recoJetIdTight;   //!
   TBranch        *b_recoJetIdTightLepVeto;   //!
   TBranch        *b_recoJetIdPileUp;   //!
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
   bool invertedMu3Iso;
   bool invertedMu4Iso;
   bool invertedEle1Iso;
   bool invertedTauIso;
   double Mu1IsoThreshold;
   double Mu2IsoThreshold;
   double Mu3IsoThreshold;
   double Mu4IsoThreshold;
   double MuIsoUpperBound;
   TString MuonId;
   TString EleRelId;
   double EleIsoUpperBound;
   double diMuonMassLowThreshold;
   double diMuonMassHighThreshold;
   bool boostDiTauOpt;
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
   TString JetId;
   bool massDecorrelation;
   double deepDiTauRawThreshold;
   double deepDiTauRawLowerBound;
   int muonScaleSyst;
   int electronScaleSyst;
   double tauScaleCorr;
   TString rochesterFile;
   int jetScaleSyst;
   TString jecSystFile;

   MuMuTauTauInclusiveAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_ = 1.0, Long_t nMaxEvents_ = 0, bool isMC_ = false, bool invertedMu2Iso_ = false, bool invertedMu3Iso_ = false, bool invertedMu4Iso_ = false, bool invertedEle1Iso_ = false, bool invertedTauIso_ = false, double Mu1IsoThreshold_ = 0.25, double Mu2IsoThreshold_ = 0.25, double Mu3IsoThreshold_ = 0.25, double Mu4IsoThreshold_ = 0.25, double MuIsoUpperBound_ = 0.5, TString MuonId_ = "LOOSE", TString EleRelId_ = "LOOSE", double EleIsoUpperBound_ = 0.6, double diMuonMassLowThreshold_ = 0, double diMuonMassHighThreshold_ = 25.0, bool boostDiTauOpt_ = false, bool tauMVAIsoRawORWP_ = false, double tauMVAIsoRawThreshold_ = -0.5, TString tauMVAIsoWP_ = "MEDIUM", TString tauAntiMuDisc_ = "NULL", TString tauAntiEleDisc_ = "NULL", bool deepTauID_ = false, TString deepTauVSele_ = "LOOSE", TString deepTauVSmu_ = "LOOSE", TString deepTauVSjet_ = "MEDIUM", double tauDecayModeThreshold_ = -1, TString JetId_ = "LOOSE", bool massDecorrelation_ = false, double deepDiTauRawThreshold_ = 0.5, double deepDiTauRawLowerBound_ = 0.2, int muonScaleSyst_ = 0, int electronScaleSyst_ = 0, double tauScaleCorr_ = 1.0, TString rochesterFile_ = "", int jetScaleSyst_ = 0, TString jecSystFile_ = "");
   string createOutputFileName();
   virtual ~MuMuTauTauInclusiveAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MuMuTauTauInclusiveAnalyzer_cxx
MuMuTauTauInclusiveAnalyzer::MuMuTauTauInclusiveAnalyzer(TString fileName_, TString outputDir_, float lumiScale_, float summedWeights_, Long_t nMaxEvents_, bool isMC_, bool invertedMu2Iso_, bool invertedMu3Iso_, bool invertedMu4Iso_, bool invertedEle1Iso_, bool invertedTauIso_, double Mu1IsoThreshold_, double Mu2IsoThreshold_, double Mu3IsoThreshold_, double Mu4IsoThreshold_, double MuIsoUpperBound_, TString MuonId_, TString EleRelId_, double EleIsoUpperBound_, double diMuonMassLowThreshold_, double diMuonMassHighThreshold_, bool boostDiTauOpt_, bool tauMVAIsoRawORWP_, double tauMVAIsoRawThreshold_, TString tauMVAIsoWP_, TString tauAntiMuDisc_, TString tauAntiEleDisc_, bool deepTauID_, TString deepTauVSele_, TString deepTauVSmu_, TString deepTauVSjet_, double tauDecayModeThreshold_, TString JetId_, bool massDecorrelation_, double deepDiTauRawThreshold_, double deepDiTauRawLowerBound_, int muonScaleSyst_, int electronScaleSyst_, double tauScaleCorr_, TString rochesterFile_, int jetScaleSyst_, TString jecSystFile_) : FlatTreeMuMuTauTau() 
{
    fileName = fileName_;
    outputDir = outputDir_;
    lumiScale = lumiScale_;
    summedWeights = summedWeights_;
    nMaxEvents = nMaxEvents_;
    isMC = isMC_;
    invertedMu2Iso = invertedMu2Iso_;
    invertedMu3Iso = invertedMu3Iso_;
    invertedMu4Iso = invertedMu4Iso_;
    invertedEle1Iso = invertedEle1Iso_;
    invertedTauIso = invertedTauIso_;
    Mu1IsoThreshold = Mu1IsoThreshold_;
    Mu2IsoThreshold = Mu2IsoThreshold_;
    Mu3IsoThreshold = Mu3IsoThreshold_;
    Mu4IsoThreshold = Mu4IsoThreshold_;
    MuIsoUpperBound = MuIsoUpperBound_;
    MuonId = MuonId_;
    EleRelId = EleRelId_;
    EleIsoUpperBound = EleIsoUpperBound_;
    diMuonMassLowThreshold = diMuonMassLowThreshold_;
    diMuonMassHighThreshold = diMuonMassHighThreshold_;
    boostDiTauOpt = boostDiTauOpt_;
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
    JetId = JetId_;
    massDecorrelation = massDecorrelation_;
    deepDiTauRawThreshold = deepDiTauRawThreshold_;
    deepDiTauRawLowerBound = deepDiTauRawLowerBound_;
    muonScaleSyst = muonScaleSyst_;
    electronScaleSyst = electronScaleSyst_;
    tauScaleCorr = tauScaleCorr_;
    rochesterFile = rochesterFile_;
    jetScaleSyst = jetScaleSyst_;
    jecSystFile = jecSystFile_;

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

string MuMuTauTauInclusiveAnalyzer::createOutputFileName()
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

MuMuTauTauInclusiveAnalyzer::~MuMuTauTauInclusiveAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MuMuTauTauInclusiveAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MuMuTauTauInclusiveAnalyzer::LoadTree(Long64_t entry)
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

void MuMuTauTauInclusiveAnalyzer::Init()
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
   recoMuonRefToTauMuonCleaned = 0;
   recoMuonIdLoose = 0;
   recoMuonIdMedium = 0;
   recoMuonIdTight = 0;
   recoElectronPt = 0;
   recoElectronEta = 0;
   recoElectronPhi = 0;
   recoElectronEnergy = 0;
   recoElectronPDGId = 0;
   recoElectronIsolation = 0;
   recoElectronIdLoose = 0;
   recoElectronIdMedium = 0;
   recoElectronIdTight = 0;
   recoElectronIdLooseNoIso = 0;
   recoElectronIdMediumNoIso = 0;
   recoElectronIdTightNoIso = 0;
   recoElectronEcalTrkEnergyPostCorr = 0;
   recoElectronEcalTrkEnergyErrPostCorr = 0;
   recoElectronEnergyScaleValue = 0;
   recoElectronEnergyScaleUp = 0;
   recoElectronEnergyScaleDown = 0;
   recoElectronEnergySigmaValue = 0;
   recoElectronEnergySigmaUp = 0;
   recoElectronEnergySigmaDown = 0;
   recoElectronRefToMuon = 0;
   recoElectronRefToTau = 0;
   recoElectronRefToTauElectronCleaned = 0;
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
   recoTauMuonCleanedPt = 0;
   recoTauMuonCleanedEta = 0;
   recoTauMuonCleanedPhi = 0;
   recoTauMuonCleanedEnergy = 0;
   recoTauMuonCleanedPDGId = 0;
   recoTauMuonCleanedDecayMode = 0;
   recoTauMuonCleanedDecayModeFinding = 0;
   recoTauMuonCleanedDecayModeFindingNewDMs = 0;
   recoTauMuonCleanedRefToMuon = 0;
   recoTauMuonCleanedRefToElectron = 0;
   recoTauMuonCleanedDeepVSeraw = 0;
   recoTauMuonCleanedDeepVSjetraw = 0;
   recoTauMuonCleanedDeepVSmuraw = 0;
   recoTauMuonCleanedDeepVSeLoose = 0;
   recoTauMuonCleanedDeepVSjetLoose = 0;
   recoTauMuonCleanedDeepVSmuLoose = 0;
   recoTauMuonCleanedDeepVSeMedium = 0;
   recoTauMuonCleanedDeepVSjetMedium = 0;
   recoTauMuonCleanedDeepVSmuMedium = 0;
   recoTauMuonCleanedDeepVSeTight = 0;
   recoTauMuonCleanedDeepVSjetTight = 0;
   recoTauMuonCleanedDeepVSmuTight = 0;
   recoTauMuonCleanedDeepVSeVLoose = 0;
   recoTauMuonCleanedDeepVSjetVLoose = 0;
   recoTauMuonCleanedDeepVSmuVLoose = 0;
   recoTauMuonCleanedDeepVSeVTight = 0;
   recoTauMuonCleanedDeepVSjetVTight = 0;
   recoTauMuonCleanedDeepVSeVVLoose = 0;
   recoTauMuonCleanedDeepVSjetVVLoose = 0;
   recoTauMuonCleanedDeepVSeVVTight = 0;
   recoTauMuonCleanedDeepVSjetVVTight = 0;
   recoTauMuonCleanedDeepVSeVVVLoose = 0;
   recoTauMuonCleanedDeepVSjetVVVLoose = 0;
   recoTauMuonCleanedIsoMVArawValue = 0;
   recoTauMuonCleanedIsoMVAVVLoose = 0;
   recoTauMuonCleanedIsoMVAVLoose = 0;
   recoTauMuonCleanedIsoMVALoose = 0;
   recoTauMuonCleanedIsoMVAMedium = 0;
   recoTauMuonCleanedIsoMVATight = 0;
   recoTauMuonCleanedIsoMVAVTight = 0;
   recoTauMuonCleanedIsoMVAVVTight = 0;
   recoTauMuonCleanedAntiMuMVALoose = 0;
   recoTauMuonCleanedAntiMuMVATight = 0;
   recoTauMuonCleanedAntiEleMVArawValue = 0;
   recoTauMuonCleanedAntiEleMVAVLoose = 0;
   recoTauMuonCleanedAntiEleMVALoose = 0;
   recoTauMuonCleanedAntiEleMVAMedium = 0;
   recoTauMuonCleanedAntiEleMVATight = 0;
   recoTauMuonCleanedAntiEleMVAVTight = 0;
   recoTauElectronCleanedPt = 0;
   recoTauElectronCleanedEta = 0;
   recoTauElectronCleanedPhi = 0;
   recoTauElectronCleanedEnergy = 0;
   recoTauElectronCleanedPDGId = 0;
   recoTauElectronCleanedDecayMode = 0;
   recoTauElectronCleanedDecayModeFinding = 0;
   recoTauElectronCleanedDecayModeFindingNewDMs = 0;
   recoTauElectronCleanedRefToMuon = 0;
   recoTauElectronCleanedRefToElectron = 0;
   recoTauElectronCleanedDeepVSeraw = 0;
   recoTauElectronCleanedDeepVSjetraw = 0;
   recoTauElectronCleanedDeepVSmuraw = 0;
   recoTauElectronCleanedDeepVSeLoose = 0;
   recoTauElectronCleanedDeepVSjetLoose = 0;
   recoTauElectronCleanedDeepVSmuLoose = 0;
   recoTauElectronCleanedDeepVSeMedium = 0;
   recoTauElectronCleanedDeepVSjetMedium = 0;
   recoTauElectronCleanedDeepVSmuMedium = 0;
   recoTauElectronCleanedDeepVSeTight = 0;
   recoTauElectronCleanedDeepVSjetTight = 0;
   recoTauElectronCleanedDeepVSmuTight = 0;
   recoTauElectronCleanedDeepVSeVLoose = 0;
   recoTauElectronCleanedDeepVSjetVLoose = 0;
   recoTauElectronCleanedDeepVSmuVLoose = 0;
   recoTauElectronCleanedDeepVSeVTight = 0;
   recoTauElectronCleanedDeepVSjetVTight = 0;
   recoTauElectronCleanedDeepVSeVVLoose = 0;
   recoTauElectronCleanedDeepVSjetVVLoose = 0;
   recoTauElectronCleanedDeepVSeVVTight = 0;
   recoTauElectronCleanedDeepVSjetVVTight = 0;
   recoTauElectronCleanedDeepVSeVVVLoose = 0;
   recoTauElectronCleanedDeepVSjetVVVLoose = 0;
   recoTauElectronCleanedIsoMVArawValue = 0;
   recoTauElectronCleanedIsoMVAVVLoose = 0;
   recoTauElectronCleanedIsoMVAVLoose = 0;
   recoTauElectronCleanedIsoMVALoose = 0;
   recoTauElectronCleanedIsoMVAMedium = 0;
   recoTauElectronCleanedIsoMVATight = 0;
   recoTauElectronCleanedIsoMVAVTight = 0;
   recoTauElectronCleanedIsoMVAVVTight = 0;
   recoTauElectronCleanedAntiMuMVALoose = 0;
   recoTauElectronCleanedAntiMuMVATight = 0;
   recoTauElectronCleanedAntiEleMVArawValue = 0;
   recoTauElectronCleanedAntiEleMVAVLoose = 0;
   recoTauElectronCleanedAntiEleMVALoose = 0;
   recoTauElectronCleanedAntiEleMVAMedium = 0;
   recoTauElectronCleanedAntiEleMVATight = 0;
   recoTauElectronCleanedAntiEleMVAVTight = 0;
   recoTauBoostedPt = 0;
   recoTauBoostedEta = 0;
   recoTauBoostedPhi = 0;
   recoTauBoostedEnergy = 0;
   recoTauBoostedPDGId = 0;
   recoTauBoostedDecayMode = 0;
   recoTauBoostedDecayModeFinding = 0;
   recoTauBoostedDecayModeFindingNewDMs = 0;
   recoTauBoostedRefToMuon = 0;
   recoTauBoostedRefToElectron = 0;
   recoTauBoostedDeepVSeraw = 0;
   recoTauBoostedDeepVSjetraw = 0;
   recoTauBoostedDeepVSmuraw = 0;
   recoTauBoostedDeepVSeLoose = 0;
   recoTauBoostedDeepVSjetLoose = 0;
   recoTauBoostedDeepVSmuLoose = 0;
   recoTauBoostedDeepVSeMedium = 0;
   recoTauBoostedDeepVSjetMedium = 0;
   recoTauBoostedDeepVSmuMedium = 0;
   recoTauBoostedDeepVSeTight = 0;
   recoTauBoostedDeepVSjetTight = 0;
   recoTauBoostedDeepVSmuTight = 0;
   recoTauBoostedDeepVSeVLoose = 0;
   recoTauBoostedDeepVSjetVLoose = 0;
   recoTauBoostedDeepVSmuVLoose = 0;
   recoTauBoostedDeepVSeVTight = 0;
   recoTauBoostedDeepVSjetVTight = 0;
   recoTauBoostedDeepVSeVVLoose = 0;
   recoTauBoostedDeepVSjetVVLoose = 0;
   recoTauBoostedDeepVSeVVTight = 0;
   recoTauBoostedDeepVSjetVVTight = 0;
   recoTauBoostedDeepVSeVVVLoose = 0;
   recoTauBoostedDeepVSjetVVVLoose = 0;
   recoTauBoostedIsoMVArawValue = 0;
   recoTauBoostedIsoMVAVVLoose = 0;
   recoTauBoostedIsoMVAVLoose = 0;
   recoTauBoostedIsoMVALoose = 0;
   recoTauBoostedIsoMVAMedium = 0;
   recoTauBoostedIsoMVATight = 0;
   recoTauBoostedIsoMVAVTight = 0;
   recoTauBoostedIsoMVAVVTight = 0;
   recoTauBoostedAntiMuMVALoose = 0;
   recoTauBoostedAntiMuMVATight = 0;
   recoTauBoostedAntiEleMVArawValue = 0;
   recoTauBoostedAntiEleMVAVLoose = 0;
   recoTauBoostedAntiEleMVALoose = 0;
   recoTauBoostedAntiEleMVAMedium = 0;
   recoTauBoostedAntiEleMVATight = 0;
   recoTauBoostedAntiEleMVAVTight = 0;
   recoJetPt = 0;
   recoJetEta = 0;
   recoJetPhi = 0;
   recoJetEnergy = 0;
   recoJetCSV = 0;
   recoJetDeepDiTauValue = 0;
   recoJetDeepDiTauValueMD = 0;
   recoJetIdLoose = 0;
   recoJetIdTight = 0;
   recoJetIdTightLepVeto = 0;
   recoJetIdPileUp = 0;
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
   fChain->SetBranchAddress("recoMuonRefToTauMuonCleaned", &recoMuonRefToTauMuonCleaned, &b_recoMuonRefToTauMuonCleaned);
   fChain->SetBranchAddress("recoMuonIdLoose", &recoMuonIdLoose, &b_recoMuonIdLoose);
   fChain->SetBranchAddress("recoMuonIdMedium", &recoMuonIdMedium, &b_recoMuonIdMedium);
   fChain->SetBranchAddress("recoMuonIdTight", &recoMuonIdTight, &b_recoMuonIdTight);
   fChain->SetBranchAddress("recoElectronPt", &recoElectronPt, &b_recoElectronPt);
   fChain->SetBranchAddress("recoElectronEta", &recoElectronEta, &b_recoElectronEta);
   fChain->SetBranchAddress("recoElectronPhi", &recoElectronPhi, &b_recoElectronPhi);
   fChain->SetBranchAddress("recoElectronEnergy", &recoElectronEnergy, &b_recoElectronEnergy);
   fChain->SetBranchAddress("recoElectronPDGId", &recoElectronPDGId, &b_recoElectronPDGId);
   fChain->SetBranchAddress("recoElectronIsolation", &recoElectronIsolation, &b_recoElectronIsolation);
   fChain->SetBranchAddress("recoElectronIdLoose", &recoElectronIdLoose, &b_recoElectronIdLoose);
   fChain->SetBranchAddress("recoElectronIdMedium", &recoElectronIdMedium, &b_recoElectronIdMedium);
   fChain->SetBranchAddress("recoElectronIdTight", &recoElectronIdTight, &b_recoElectronIdTight);
   fChain->SetBranchAddress("recoElectronIdLooseNoIso", &recoElectronIdLooseNoIso, &b_recoElectronIdLooseNoIso);
   fChain->SetBranchAddress("recoElectronIdMediumNoIso", &recoElectronIdMediumNoIso, &b_recoElectronIdMediumNoIso);
   fChain->SetBranchAddress("recoElectronIdTightNoIso", &recoElectronIdTightNoIso, &b_recoElectronIdTightNoIso);
   fChain->SetBranchAddress("recoElectronEcalTrkEnergyPostCorr", &recoElectronEcalTrkEnergyPostCorr, &b_recoElectronEcalTrkEnergyPostCorr);
   fChain->SetBranchAddress("recoElectronEcalTrkEnergyErrPostCorr", &recoElectronEcalTrkEnergyErrPostCorr, &b_recoElectronEcalTrkEnergyErrPostCorr);
   fChain->SetBranchAddress("recoElectronEnergyScaleValue", &recoElectronEnergyScaleValue, &b_recoElectronEnergyScaleValue);
   fChain->SetBranchAddress("recoElectronEnergyScaleUp", &recoElectronEnergyScaleUp, &b_recoElectronEnergyScaleUp);
   fChain->SetBranchAddress("recoElectronEnergyScaleDown", &recoElectronEnergyScaleDown, &b_recoElectronEnergyScaleDown);
   fChain->SetBranchAddress("recoElectronEnergySigmaValue", &recoElectronEnergySigmaValue, &b_recoElectronEnergySigmaValue);
   fChain->SetBranchAddress("recoElectronEnergySigmaUp", &recoElectronEnergySigmaUp, &b_recoElectronEnergySigmaUp);
   fChain->SetBranchAddress("recoElectronEnergySigmaDown", &recoElectronEnergySigmaDown, &b_recoElectronEnergySigmaDown);
   fChain->SetBranchAddress("recoElectronRefToMuon", &recoElectronRefToMuon, &b_recoElectronRefToMuon);
   fChain->SetBranchAddress("recoElectronRefToTau", &recoElectronRefToTau, &b_recoElectronRefToTau);
   fChain->SetBranchAddress("recoElectronRefToTauElectronCleaned", &recoElectronRefToTauElectronCleaned, &b_recoElectronRefToTauElectronCleaned);
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
   fChain->SetBranchAddress("recoTauMuonCleanedPt", &recoTauMuonCleanedPt, &b_recoTauMuonCleanedPt);
   fChain->SetBranchAddress("recoTauMuonCleanedEta", &recoTauMuonCleanedEta, &b_recoTauMuonCleanedEta);
   fChain->SetBranchAddress("recoTauMuonCleanedPhi", &recoTauMuonCleanedPhi, &b_recoTauMuonCleanedPhi);
   fChain->SetBranchAddress("recoTauMuonCleanedEnergy", &recoTauMuonCleanedEnergy, &b_recoTauMuonCleanedEnergy);
   fChain->SetBranchAddress("recoTauMuonCleanedPDGId", &recoTauMuonCleanedPDGId, &b_recoTauMuonCleanedPDGId);
   fChain->SetBranchAddress("recoTauMuonCleanedDecayMode", &recoTauMuonCleanedDecayMode, &b_recoTauMuonCleanedDecayMode);
   fChain->SetBranchAddress("recoTauMuonCleanedDecayModeFinding", &recoTauMuonCleanedDecayModeFinding, &b_recoTauMuonCleanedDecayModeFinding);
   fChain->SetBranchAddress("recoTauMuonCleanedDecayModeFindingNewDMs", &recoTauMuonCleanedDecayModeFindingNewDMs, &b_recoTauMuonCleanedDecayModeFindingNewDMs);
   fChain->SetBranchAddress("recoTauMuonCleanedRefToMuon", &recoTauMuonCleanedRefToMuon, &b_recoTauMuonCleanedRefToMuon);
   fChain->SetBranchAddress("recoTauMuonCleanedRefToElectron", &recoTauMuonCleanedRefToElectron, &b_recoTauMuonCleanedRefToElectron);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeraw", &recoTauMuonCleanedDeepVSeraw, &b_recoTauMuonCleanedDeepVSeraw);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetraw", &recoTauMuonCleanedDeepVSjetraw, &b_recoTauMuonCleanedDeepVSjetraw);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSmuraw", &recoTauMuonCleanedDeepVSmuraw, &b_recoTauMuonCleanedDeepVSmuraw);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeLoose", &recoTauMuonCleanedDeepVSeLoose, &b_recoTauMuonCleanedDeepVSeLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetLoose", &recoTauMuonCleanedDeepVSjetLoose, &b_recoTauMuonCleanedDeepVSjetLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSmuLoose", &recoTauMuonCleanedDeepVSmuLoose, &b_recoTauMuonCleanedDeepVSmuLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeMedium", &recoTauMuonCleanedDeepVSeMedium, &b_recoTauMuonCleanedDeepVSeMedium);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetMedium", &recoTauMuonCleanedDeepVSjetMedium, &b_recoTauMuonCleanedDeepVSjetMedium);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSmuMedium", &recoTauMuonCleanedDeepVSmuMedium, &b_recoTauMuonCleanedDeepVSmuMedium);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeTight", &recoTauMuonCleanedDeepVSeTight, &b_recoTauMuonCleanedDeepVSeTight);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetTight", &recoTauMuonCleanedDeepVSjetTight, &b_recoTauMuonCleanedDeepVSjetTight);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSmuTight", &recoTauMuonCleanedDeepVSmuTight, &b_recoTauMuonCleanedDeepVSmuTight);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeVLoose", &recoTauMuonCleanedDeepVSeVLoose, &b_recoTauMuonCleanedDeepVSeVLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetVLoose", &recoTauMuonCleanedDeepVSjetVLoose, &b_recoTauMuonCleanedDeepVSjetVLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSmuVLoose", &recoTauMuonCleanedDeepVSmuVLoose, &b_recoTauMuonCleanedDeepVSmuVLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeVTight", &recoTauMuonCleanedDeepVSeVTight, &b_recoTauMuonCleanedDeepVSeVTight);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetVTight", &recoTauMuonCleanedDeepVSjetVTight, &b_recoTauMuonCleanedDeepVSjetVTight);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeVVLoose", &recoTauMuonCleanedDeepVSeVVLoose, &b_recoTauMuonCleanedDeepVSeVVLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetVVLoose", &recoTauMuonCleanedDeepVSjetVVLoose, &b_recoTauMuonCleanedDeepVSjetVVLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeVVTight", &recoTauMuonCleanedDeepVSeVVTight, &b_recoTauMuonCleanedDeepVSeVVTight);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetVVTight", &recoTauMuonCleanedDeepVSjetVVTight, &b_recoTauMuonCleanedDeepVSjetVVTight);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSeVVVLoose", &recoTauMuonCleanedDeepVSeVVVLoose, &b_recoTauMuonCleanedDeepVSeVVVLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedDeepVSjetVVVLoose", &recoTauMuonCleanedDeepVSjetVVVLoose, &b_recoTauMuonCleanedDeepVSjetVVVLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedIsoMVArawValue", &recoTauMuonCleanedIsoMVArawValue, &b_recoTauMuonCleanedIsoMVArawValue);
   fChain->SetBranchAddress("recoTauMuonCleanedIsoMVAVVLoose", &recoTauMuonCleanedIsoMVAVVLoose, &b_recoTauMuonCleanedIsoMVAVVLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedIsoMVAVLoose", &recoTauMuonCleanedIsoMVAVLoose, &b_recoTauMuonCleanedIsoMVAVLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedIsoMVALoose", &recoTauMuonCleanedIsoMVALoose, &b_recoTauMuonCleanedIsoMVALoose);
   fChain->SetBranchAddress("recoTauMuonCleanedIsoMVAMedium", &recoTauMuonCleanedIsoMVAMedium, &b_recoTauMuonCleanedIsoMVAMedium);
   fChain->SetBranchAddress("recoTauMuonCleanedIsoMVATight", &recoTauMuonCleanedIsoMVATight, &b_recoTauMuonCleanedIsoMVATight);
   fChain->SetBranchAddress("recoTauMuonCleanedIsoMVAVTight", &recoTauMuonCleanedIsoMVAVTight, &b_recoTauMuonCleanedIsoMVAVTight);
   fChain->SetBranchAddress("recoTauMuonCleanedIsoMVAVVTight", &recoTauMuonCleanedIsoMVAVVTight, &b_recoTauMuonCleanedIsoMVAVVTight);
   fChain->SetBranchAddress("recoTauMuonCleanedAntiMuMVALoose", &recoTauMuonCleanedAntiMuMVALoose, &b_recoTauMuonCleanedAntiMuMVALoose);
   fChain->SetBranchAddress("recoTauMuonCleanedAntiMuMVATight", &recoTauMuonCleanedAntiMuMVATight, &b_recoTauMuonCleanedAntiMuMVATight);
   fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVArawValue", &recoTauMuonCleanedAntiEleMVArawValue, &b_recoTauMuonCleanedAntiEleMVArawValue);
   fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVAVLoose", &recoTauMuonCleanedAntiEleMVAVLoose, &b_recoTauMuonCleanedAntiEleMVAVLoose);
   fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVALoose", &recoTauMuonCleanedAntiEleMVALoose, &b_recoTauMuonCleanedAntiEleMVALoose);
   fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVAMedium", &recoTauMuonCleanedAntiEleMVAMedium, &b_recoTauMuonCleanedAntiEleMVAMedium);
   fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVATight", &recoTauMuonCleanedAntiEleMVATight, &b_recoTauMuonCleanedAntiEleMVATight);
   fChain->SetBranchAddress("recoTauMuonCleanedAntiEleMVAVTight", &recoTauMuonCleanedAntiEleMVAVTight, &b_recoTauMuonCleanedAntiEleMVAVTight);
   fChain->SetBranchAddress("recoTauElectronCleanedPt", &recoTauElectronCleanedPt, &b_recoTauElectronCleanedPt);
   fChain->SetBranchAddress("recoTauElectronCleanedEta", &recoTauElectronCleanedEta, &b_recoTauElectronCleanedEta);
   fChain->SetBranchAddress("recoTauElectronCleanedPhi", &recoTauElectronCleanedPhi, &b_recoTauElectronCleanedPhi);
   fChain->SetBranchAddress("recoTauElectronCleanedEnergy", &recoTauElectronCleanedEnergy, &b_recoTauElectronCleanedEnergy);
   fChain->SetBranchAddress("recoTauElectronCleanedPDGId", &recoTauElectronCleanedPDGId, &b_recoTauElectronCleanedPDGId);
   fChain->SetBranchAddress("recoTauElectronCleanedDecayMode", &recoTauElectronCleanedDecayMode, &b_recoTauElectronCleanedDecayMode);
   fChain->SetBranchAddress("recoTauElectronCleanedDecayModeFinding", &recoTauElectronCleanedDecayModeFinding, &b_recoTauElectronCleanedDecayModeFinding);
   fChain->SetBranchAddress("recoTauElectronCleanedDecayModeFindingNewDMs", &recoTauElectronCleanedDecayModeFindingNewDMs, &b_recoTauElectronCleanedDecayModeFindingNewDMs);
   fChain->SetBranchAddress("recoTauElectronCleanedRefToMuon", &recoTauElectronCleanedRefToMuon, &b_recoTauElectronCleanedRefToMuon);
   fChain->SetBranchAddress("recoTauElectronCleanedRefToElectron", &recoTauElectronCleanedRefToElectron, &b_recoTauElectronCleanedRefToElectron);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSeraw", &recoTauElectronCleanedDeepVSeraw, &b_recoTauElectronCleanedDeepVSeraw);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSjetraw", &recoTauElectronCleanedDeepVSjetraw, &b_recoTauElectronCleanedDeepVSjetraw);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSmuraw", &recoTauElectronCleanedDeepVSmuraw, &b_recoTauElectronCleanedDeepVSmuraw);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSeLoose", &recoTauElectronCleanedDeepVSeLoose, &b_recoTauElectronCleanedDeepVSeLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSjetLoose", &recoTauElectronCleanedDeepVSjetLoose, &b_recoTauElectronCleanedDeepVSjetLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSmuLoose", &recoTauElectronCleanedDeepVSmuLoose, &b_recoTauElectronCleanedDeepVSmuLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSeMedium", &recoTauElectronCleanedDeepVSeMedium, &b_recoTauElectronCleanedDeepVSeMedium);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSjetMedium", &recoTauElectronCleanedDeepVSjetMedium, &b_recoTauElectronCleanedDeepVSjetMedium);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSmuMedium", &recoTauElectronCleanedDeepVSmuMedium, &b_recoTauElectronCleanedDeepVSmuMedium);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSeTight", &recoTauElectronCleanedDeepVSeTight, &b_recoTauElectronCleanedDeepVSeTight);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSjetTight", &recoTauElectronCleanedDeepVSjetTight, &b_recoTauElectronCleanedDeepVSjetTight);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSmuTight", &recoTauElectronCleanedDeepVSmuTight, &b_recoTauElectronCleanedDeepVSmuTight);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSeVLoose", &recoTauElectronCleanedDeepVSeVLoose, &b_recoTauElectronCleanedDeepVSeVLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSjetVLoose", &recoTauElectronCleanedDeepVSjetVLoose, &b_recoTauElectronCleanedDeepVSjetVLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSmuVLoose", &recoTauElectronCleanedDeepVSmuVLoose, &b_recoTauElectronCleanedDeepVSmuVLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSeVTight", &recoTauElectronCleanedDeepVSeVTight, &b_recoTauElectronCleanedDeepVSeVTight);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSjetVTight", &recoTauElectronCleanedDeepVSjetVTight, &b_recoTauElectronCleanedDeepVSjetVTight);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSeVVLoose", &recoTauElectronCleanedDeepVSeVVLoose, &b_recoTauElectronCleanedDeepVSeVVLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSjetVVLoose", &recoTauElectronCleanedDeepVSjetVVLoose, &b_recoTauElectronCleanedDeepVSjetVVLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSeVVTight", &recoTauElectronCleanedDeepVSeVVTight, &b_recoTauElectronCleanedDeepVSeVVTight);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSjetVVTight", &recoTauElectronCleanedDeepVSjetVVTight, &b_recoTauElectronCleanedDeepVSjetVVTight);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSeVVVLoose", &recoTauElectronCleanedDeepVSeVVVLoose, &b_recoTauElectronCleanedDeepVSeVVVLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedDeepVSjetVVVLoose", &recoTauElectronCleanedDeepVSjetVVVLoose, &b_recoTauElectronCleanedDeepVSjetVVVLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedIsoMVArawValue", &recoTauElectronCleanedIsoMVArawValue, &b_recoTauElectronCleanedIsoMVArawValue);
   fChain->SetBranchAddress("recoTauElectronCleanedIsoMVAVVLoose", &recoTauElectronCleanedIsoMVAVVLoose, &b_recoTauElectronCleanedIsoMVAVVLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedIsoMVAVLoose", &recoTauElectronCleanedIsoMVAVLoose, &b_recoTauElectronCleanedIsoMVAVLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedIsoMVALoose", &recoTauElectronCleanedIsoMVALoose, &b_recoTauElectronCleanedIsoMVALoose);
   fChain->SetBranchAddress("recoTauElectronCleanedIsoMVAMedium", &recoTauElectronCleanedIsoMVAMedium, &b_recoTauElectronCleanedIsoMVAMedium);
   fChain->SetBranchAddress("recoTauElectronCleanedIsoMVATight", &recoTauElectronCleanedIsoMVATight, &b_recoTauElectronCleanedIsoMVATight);
   fChain->SetBranchAddress("recoTauElectronCleanedIsoMVAVTight", &recoTauElectronCleanedIsoMVAVTight, &b_recoTauElectronCleanedIsoMVAVTight);
   fChain->SetBranchAddress("recoTauElectronCleanedIsoMVAVVTight", &recoTauElectronCleanedIsoMVAVVTight, &b_recoTauElectronCleanedIsoMVAVVTight);
   fChain->SetBranchAddress("recoTauElectronCleanedAntiMuMVALoose", &recoTauElectronCleanedAntiMuMVALoose, &b_recoTauElectronCleanedAntiMuMVALoose);
   fChain->SetBranchAddress("recoTauElectronCleanedAntiMuMVATight", &recoTauElectronCleanedAntiMuMVATight, &b_recoTauElectronCleanedAntiMuMVATight);
   fChain->SetBranchAddress("recoTauElectronCleanedAntiEleMVArawValue", &recoTauElectronCleanedAntiEleMVArawValue, &b_recoTauElectronCleanedAntiEleMVArawValue);
   fChain->SetBranchAddress("recoTauElectronCleanedAntiEleMVAVLoose", &recoTauElectronCleanedAntiEleMVAVLoose, &b_recoTauElectronCleanedAntiEleMVAVLoose);
   fChain->SetBranchAddress("recoTauElectronCleanedAntiEleMVALoose", &recoTauElectronCleanedAntiEleMVALoose, &b_recoTauElectronCleanedAntiEleMVALoose);
   fChain->SetBranchAddress("recoTauElectronCleanedAntiEleMVAMedium", &recoTauElectronCleanedAntiEleMVAMedium, &b_recoTauElectronCleanedAntiEleMVAMedium);
   fChain->SetBranchAddress("recoTauElectronCleanedAntiEleMVATight", &recoTauElectronCleanedAntiEleMVATight, &b_recoTauElectronCleanedAntiEleMVATight);
   fChain->SetBranchAddress("recoTauElectronCleanedAntiEleMVAVTight", &recoTauElectronCleanedAntiEleMVAVTight, &b_recoTauElectronCleanedAntiEleMVAVTight);
   fChain->SetBranchAddress("recoTauBoostedPt", &recoTauBoostedPt, &b_recoTauBoostedPt);
   fChain->SetBranchAddress("recoTauBoostedEta", &recoTauBoostedEta, &b_recoTauBoostedEta);
   fChain->SetBranchAddress("recoTauBoostedPhi", &recoTauBoostedPhi, &b_recoTauBoostedPhi);
   fChain->SetBranchAddress("recoTauBoostedEnergy", &recoTauBoostedEnergy, &b_recoTauBoostedEnergy);
   fChain->SetBranchAddress("recoTauBoostedPDGId", &recoTauBoostedPDGId, &b_recoTauBoostedPDGId);
   fChain->SetBranchAddress("recoTauBoostedDecayMode", &recoTauBoostedDecayMode, &b_recoTauBoostedDecayMode);
   fChain->SetBranchAddress("recoTauBoostedDecayModeFinding", &recoTauBoostedDecayModeFinding, &b_recoTauBoostedDecayModeFinding);
   fChain->SetBranchAddress("recoTauBoostedDecayModeFindingNewDMs", &recoTauBoostedDecayModeFindingNewDMs, &b_recoTauBoostedDecayModeFindingNewDMs);
   fChain->SetBranchAddress("recoTauBoostedRefToMuon", &recoTauBoostedRefToMuon, &b_recoTauBoostedRefToMuon);
   fChain->SetBranchAddress("recoTauBoostedRefToElectron", &recoTauBoostedRefToElectron, &b_recoTauBoostedRefToElectron);
   fChain->SetBranchAddress("recoTauBoostedDeepVSeraw", &recoTauBoostedDeepVSeraw, &b_recoTauBoostedDeepVSeraw);
   fChain->SetBranchAddress("recoTauBoostedDeepVSjetraw", &recoTauBoostedDeepVSjetraw, &b_recoTauBoostedDeepVSjetraw);
   fChain->SetBranchAddress("recoTauBoostedDeepVSmuraw", &recoTauBoostedDeepVSmuraw, &b_recoTauBoostedDeepVSmuraw);
   fChain->SetBranchAddress("recoTauBoostedDeepVSeLoose", &recoTauBoostedDeepVSeLoose, &b_recoTauBoostedDeepVSeLoose);
   fChain->SetBranchAddress("recoTauBoostedDeepVSjetLoose", &recoTauBoostedDeepVSjetLoose, &b_recoTauBoostedDeepVSjetLoose);
   fChain->SetBranchAddress("recoTauBoostedDeepVSmuLoose", &recoTauBoostedDeepVSmuLoose, &b_recoTauBoostedDeepVSmuLoose);
   fChain->SetBranchAddress("recoTauBoostedDeepVSeMedium", &recoTauBoostedDeepVSeMedium, &b_recoTauBoostedDeepVSeMedium);
   fChain->SetBranchAddress("recoTauBoostedDeepVSjetMedium", &recoTauBoostedDeepVSjetMedium, &b_recoTauBoostedDeepVSjetMedium);
   fChain->SetBranchAddress("recoTauBoostedDeepVSmuMedium", &recoTauBoostedDeepVSmuMedium, &b_recoTauBoostedDeepVSmuMedium);
   fChain->SetBranchAddress("recoTauBoostedDeepVSeTight", &recoTauBoostedDeepVSeTight, &b_recoTauBoostedDeepVSeTight);
   fChain->SetBranchAddress("recoTauBoostedDeepVSjetTight", &recoTauBoostedDeepVSjetTight, &b_recoTauBoostedDeepVSjetTight);
   fChain->SetBranchAddress("recoTauBoostedDeepVSmuTight", &recoTauBoostedDeepVSmuTight, &b_recoTauBoostedDeepVSmuTight);
   fChain->SetBranchAddress("recoTauBoostedDeepVSeVLoose", &recoTauBoostedDeepVSeVLoose, &b_recoTauBoostedDeepVSeVLoose);
   fChain->SetBranchAddress("recoTauBoostedDeepVSjetVLoose", &recoTauBoostedDeepVSjetVLoose, &b_recoTauBoostedDeepVSjetVLoose);
   fChain->SetBranchAddress("recoTauBoostedDeepVSmuVLoose", &recoTauBoostedDeepVSmuVLoose, &b_recoTauBoostedDeepVSmuVLoose);
   fChain->SetBranchAddress("recoTauBoostedDeepVSeVTight", &recoTauBoostedDeepVSeVTight, &b_recoTauBoostedDeepVSeVTight);
   fChain->SetBranchAddress("recoTauBoostedDeepVSjetVTight", &recoTauBoostedDeepVSjetVTight, &b_recoTauBoostedDeepVSjetVTight);
   fChain->SetBranchAddress("recoTauBoostedDeepVSeVVLoose", &recoTauBoostedDeepVSeVVLoose, &b_recoTauBoostedDeepVSeVVLoose);
   fChain->SetBranchAddress("recoTauBoostedDeepVSjetVVLoose", &recoTauBoostedDeepVSjetVVLoose, &b_recoTauBoostedDeepVSjetVVLoose);
   fChain->SetBranchAddress("recoTauBoostedDeepVSeVVTight", &recoTauBoostedDeepVSeVVTight, &b_recoTauBoostedDeepVSeVVTight);
   fChain->SetBranchAddress("recoTauBoostedDeepVSjetVVTight", &recoTauBoostedDeepVSjetVVTight, &b_recoTauBoostedDeepVSjetVVTight);
   fChain->SetBranchAddress("recoTauBoostedDeepVSeVVVLoose", &recoTauBoostedDeepVSeVVVLoose, &b_recoTauBoostedDeepVSeVVVLoose);
   fChain->SetBranchAddress("recoTauBoostedDeepVSjetVVVLoose", &recoTauBoostedDeepVSjetVVVLoose, &b_recoTauBoostedDeepVSjetVVVLoose);
   fChain->SetBranchAddress("recoTauBoostedIsoMVArawValue", &recoTauBoostedIsoMVArawValue, &b_recoTauBoostedIsoMVArawValue);
   fChain->SetBranchAddress("recoTauBoostedIsoMVAVVLoose", &recoTauBoostedIsoMVAVVLoose, &b_recoTauBoostedIsoMVAVVLoose);
   fChain->SetBranchAddress("recoTauBoostedIsoMVAVLoose", &recoTauBoostedIsoMVAVLoose, &b_recoTauBoostedIsoMVAVLoose);
   fChain->SetBranchAddress("recoTauBoostedIsoMVALoose", &recoTauBoostedIsoMVALoose, &b_recoTauBoostedIsoMVALoose);
   fChain->SetBranchAddress("recoTauBoostedIsoMVAMedium", &recoTauBoostedIsoMVAMedium, &b_recoTauBoostedIsoMVAMedium);
   fChain->SetBranchAddress("recoTauBoostedIsoMVATight", &recoTauBoostedIsoMVATight, &b_recoTauBoostedIsoMVATight);
   fChain->SetBranchAddress("recoTauBoostedIsoMVAVTight", &recoTauBoostedIsoMVAVTight, &b_recoTauBoostedIsoMVAVTight);
   fChain->SetBranchAddress("recoTauBoostedIsoMVAVVTight", &recoTauBoostedIsoMVAVVTight, &b_recoTauBoostedIsoMVAVVTight);
   fChain->SetBranchAddress("recoTauBoostedAntiMuMVALoose", &recoTauBoostedAntiMuMVALoose, &b_recoTauBoostedAntiMuMVALoose);
   fChain->SetBranchAddress("recoTauBoostedAntiMuMVATight", &recoTauBoostedAntiMuMVATight, &b_recoTauBoostedAntiMuMVATight);
   fChain->SetBranchAddress("recoTauBoostedAntiEleMVArawValue", &recoTauBoostedAntiEleMVArawValue, &b_recoTauBoostedAntiEleMVArawValue);
   fChain->SetBranchAddress("recoTauBoostedAntiEleMVAVLoose", &recoTauBoostedAntiEleMVAVLoose, &b_recoTauBoostedAntiEleMVAVLoose);
   fChain->SetBranchAddress("recoTauBoostedAntiEleMVALoose", &recoTauBoostedAntiEleMVALoose, &b_recoTauBoostedAntiEleMVALoose);
   fChain->SetBranchAddress("recoTauBoostedAntiEleMVAMedium", &recoTauBoostedAntiEleMVAMedium, &b_recoTauBoostedAntiEleMVAMedium);
   fChain->SetBranchAddress("recoTauBoostedAntiEleMVATight", &recoTauBoostedAntiEleMVATight, &b_recoTauBoostedAntiEleMVATight);
   fChain->SetBranchAddress("recoTauBoostedAntiEleMVAVTight", &recoTauBoostedAntiEleMVAVTight, &b_recoTauBoostedAntiEleMVAVTight);
   fChain->SetBranchAddress("recoJetPt", &recoJetPt, &b_recoJetPt);
   fChain->SetBranchAddress("recoJetEta", &recoJetEta, &b_recoJetEta);
   fChain->SetBranchAddress("recoJetPhi", &recoJetPhi, &b_recoJetPhi);
   fChain->SetBranchAddress("recoJetEnergy", &recoJetEnergy, &b_recoJetEnergy);
   fChain->SetBranchAddress("recoJetCSV", &recoJetCSV, &b_recoJetCSV);
   fChain->SetBranchAddress("recoJetDeepDiTauValue", &recoJetDeepDiTauValue, &b_recoJetDeepDiTauValue);
   fChain->SetBranchAddress("recoJetDeepDiTauValueMD", &recoJetDeepDiTauValueMD, &b_recoJetDeepDiTauValueMD);
   fChain->SetBranchAddress("recoJetIdLoose", &recoJetIdLoose, &b_recoJetIdLoose);
   fChain->SetBranchAddress("recoJetIdTight", &recoJetIdTight, &b_recoJetIdTight);
   fChain->SetBranchAddress("recoJetIdTightLepVeto", &recoJetIdTightLepVeto, &b_recoJetIdTightLepVeto);
   fChain->SetBranchAddress("recoJetIdPileUp", &recoJetIdPileUp, &b_recoJetIdPileUp);
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

Bool_t MuMuTauTauInclusiveAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MuMuTauTauInclusiveAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MuMuTauTauInclusiveAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MuMuTauTauInclusiveAnalyzer_cxx
