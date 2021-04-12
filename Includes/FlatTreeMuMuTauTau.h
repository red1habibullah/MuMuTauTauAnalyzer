#ifndef _FlatTreeMuMuTauTau_h_
#define _FlatTreeMuMuTauTau_h_

#include "TTree.h"
#include <iostream>
#include <vector>
#include <string>
#include "TArray.h"
using namespace std;

class FlatTreeMuMuTauTau{

    public:

        FlatTreeMuMuTauTau();
        ~FlatTreeMuMuTauTau();

        // ----------- flat tree for 2mu channel -----------
        TTree* Tree2Mu;
        
        double invMassMu1Mu2_mm;
        double visMassMu3Mu4_mm;
        double visMass4Mu_mm;

        double deltaRMu1Mu2_mm;
        double deltaRMu3Mu4_mm;

        double mu1Pt_mm;
        double mu1Eta_mm;
        double mu1Phi_mm;
        double mu1Mass_mm;

        double mu2Pt_mm;
        double mu2Eta_mm;
        double mu2Phi_mm;
        double mu2Mass_mm;

        double mu3Pt_mm;
        double mu3Eta_mm;
        double mu3Phi_mm;
        double mu3Mass_mm;

        double mu4Pt_mm;
        double mu4Eta_mm;
        double mu4Phi_mm;
        double mu4Mass_mm;
        
        double eventWeight_mm;

        // ----------- flat tree for mue channel -----------
        TTree* TreeMuEle;
        
        double invMassMu1Mu2_me;
        double visMassMu3Ele_me;
        double visMass3MuEle_me;

        double deltaRMu1Mu2_me;
        double deltaRMu3Ele_me;

        double mu1Pt_me;
        double mu1Eta_me;
        double mu1Phi_me;
        double mu1Mass_me;

        double mu2Pt_me;
        double mu2Eta_me;
        double mu2Phi_me;
        double mu2Mass_me;

        double mu3Pt_me;
        double mu3Eta_me;
        double mu3Phi_me;
        double mu3Mass_me;

        double elePt_me;
        double eleEta_me;
        double elePhi_me;
        double eleMass_me;
        
        double eventWeight_me;

        // ----------- flat tree for mutau channel -----------
        TTree* TreeMuTau;
        
        double invMassMu1Mu2_mt;
        double visMassMu3Tau_mt;
        double visMass3MuTau_mt;

        double deltaRMu1Mu2_mt;
        double deltaRMu3Tau_mt;

        double mu1Pt_mt;
        double mu1Eta_mt;
        double mu1Phi_mt;
        double mu1Mass_mt;

        double mu2Pt_mt;
        double mu2Eta_mt;
        double mu2Phi_mt;
        double mu2Mass_mt;

        double mu3Pt_mt;
        double mu3Eta_mt;
        double mu3Phi_mt;
        double mu3Mass_mt;

        double tauPt_mt;
        double tauEta_mt;
        double tauPhi_mt;
        double tauMass_mt;
        double tauDisc_mt;
        double tauDM_mt;
        
        double eventWeight_mt;

        // ----------- flat tree for etau channel -----------
        TTree* TreeEleTau;
        
        double invMassMu1Mu2_et;
        double visMassEleTau_et;
        double visMass2MuEleTau_et;

        double deltaRMu1Mu2_et;
        double deltaREleTau_et;

        double mu1Pt_et;
        double mu1Eta_et;
        double mu1Phi_et;
        double mu1Mass_et;

        double mu2Pt_et;
        double mu2Eta_et;
        double mu2Phi_et;
        double mu2Mass_et;

        double elePt_et;
        double eleEta_et;
        double elePhi_et;
        double eleMass_et;

        double tauPt_et;
        double tauEta_et;
        double tauPhi_et;
        double tauMass_et;
        double tauDisc_et;
        double tauDM_et;
        
        double eventWeight_et;

        // ----------- flat tree for tautau channel -----------
        TTree* TreeTauTau;
        
        double invMassMu1Mu2_tt;
        double visMassTauTau_tt;
        double visMass2Mu2Tau_tt;

        double deltaRMu1Mu2_tt;
        double deltaRTauTau_tt;

        double mu1Pt_tt;
        double mu1Eta_tt;
        double mu1Phi_tt;
        double mu1Mass_tt;

        double mu2Pt_tt;
        double mu2Eta_tt;
        double mu2Phi_tt;
        double mu2Mass_tt;

        double tauPt_tt;
        double tauEta_tt;
        double tauPhi_tt;
        double tauMass_tt;
        double tauDisc_tt;
        double tauDM_tt;
        
        double tau2Pt_tt;
        double tau2Eta_tt;
        double tau2Phi_tt;
        double tau2Mass_tt;
        double tau2Disc_tt;
        double tau2DM_tt;

        double eventWeight_tt;
};

#endif
