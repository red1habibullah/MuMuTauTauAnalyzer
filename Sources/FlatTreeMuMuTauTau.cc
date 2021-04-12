#include "FlatTreeMuMuTauTau.h"

FlatTreeMuMuTauTau::FlatTreeMuMuTauTau(){

    // ----------- flat tree for 2mu channel -----------
    Tree2Mu = new TTree("Tree2Mu","Tree2Mu");

    Tree2Mu->Branch("invMassMu1Mu2_mm", &invMassMu1Mu2_mm, "invMassMu1Mu2_mm/D");
    Tree2Mu->Branch("visMassMu3Mu4_mm", &visMassMu3Mu4_mm, "visMassMu3Mu4_mm/D");
    Tree2Mu->Branch("visMass4Mu_mm", &visMass4Mu_mm, "visMass4Mu_mm/D");

    Tree2Mu->Branch("deltaRMu1Mu2_mm", &deltaRMu1Mu2_mm, "deltaRMu1Mu2_mm/D");
    Tree2Mu->Branch("deltaRMu3Mu4_mm", &deltaRMu3Mu4_mm, "deltaRMu3Mu4_mm/D");

    Tree2Mu->Branch("mu1Pt_mm", &mu1Pt_mm, "mu1Pt_mm/D");
    Tree2Mu->Branch("mu1Eta_mm", &mu1Eta_mm, "mu1Eta_mm/D");
    Tree2Mu->Branch("mu1Phi_mm", &mu1Phi_mm, "mu1Phi_mm/D");
    Tree2Mu->Branch("mu1Mass_mm", &mu1Mass_mm, "mu1Mass_mm/D");

    Tree2Mu->Branch("mu2Pt_mm", &mu2Pt_mm, "mu2Pt_mm/D");
    Tree2Mu->Branch("mu2Eta_mm", &mu2Eta_mm, "mu2Eta_mm/D");
    Tree2Mu->Branch("mu2Phi_mm", &mu2Phi_mm, "mu2Phi_mm/D");
    Tree2Mu->Branch("mu2Mass_mm", &mu2Mass_mm, "mu2Mass_mm/D");

    Tree2Mu->Branch("mu3Pt_mm", &mu3Pt_mm, "mu3Pt_mm/D");
    Tree2Mu->Branch("mu3Eta_mm", &mu3Eta_mm, "mu3Eta_mm/D");
    Tree2Mu->Branch("mu3Phi_mm", &mu3Phi_mm, "mu3Phi_mm/D");
    Tree2Mu->Branch("mu3Mass_mm", &mu3Mass_mm, "mu3Mass_mm/D");

    Tree2Mu->Branch("mu4Pt_mm", &mu4Pt_mm, "mu4Pt_mm/D");
    Tree2Mu->Branch("mu4Eta_mm", &mu4Eta_mm, "mu4Eta_mm/D");
    Tree2Mu->Branch("mu4Phi_mm", &mu4Phi_mm, "mu4Phi_mm/D");
    Tree2Mu->Branch("mu4Mass_mm", &mu4Mass_mm, "mu4Mass_mm/D");

    Tree2Mu->Branch("eventWeight_mm", &eventWeight_mm, "eventWeight_mm/D");

    // ----------- flat tree for mue channel -----------
    TreeMuEle = new TTree("TreeMuEle","TreeMuEle");

    TreeMuEle->Branch("invMassMu1Mu2_me", &invMassMu1Mu2_me, "invMassMu1Mu2_me/D");
    TreeMuEle->Branch("visMassMu3Ele_me", &visMassMu3Ele_me, "visMassMu3Ele_me/D");
    TreeMuEle->Branch("visMass3MuEle_me", &visMass3MuEle_me, "visMass3MuEle_me/D");

    TreeMuEle->Branch("deltaRMu1Mu2_me", &deltaRMu1Mu2_me, "deltaRMu1Mu2_me/D");
    TreeMuEle->Branch("deltaRMu3Ele_me", &deltaRMu3Ele_me, "deltaRMu3Ele_me/D");

    TreeMuEle->Branch("mu1Pt_me", &mu1Pt_me, "mu1Pt_me/D");
    TreeMuEle->Branch("mu1Eta_me", &mu1Eta_me, "mu1Eta_me/D");
    TreeMuEle->Branch("mu1Phi_me", &mu1Phi_me, "mu1Phi_me/D");
    TreeMuEle->Branch("mu1Mass_me", &mu1Mass_me, "mu1Mass_me/D");

    TreeMuEle->Branch("mu2Pt_me", &mu2Pt_me, "mu2Pt_me/D");
    TreeMuEle->Branch("mu2Eta_me", &mu2Eta_me, "mu2Eta_me/D");
    TreeMuEle->Branch("mu2Phi_me", &mu2Phi_me, "mu2Phi_me/D");
    TreeMuEle->Branch("mu2Mass_me", &mu2Mass_me, "mu2Mass_me/D");

    TreeMuEle->Branch("mu3Pt_me", &mu3Pt_me, "mu3Pt_me/D");
    TreeMuEle->Branch("mu3Eta_me", &mu3Eta_me, "mu3Eta_me/D");
    TreeMuEle->Branch("mu3Phi_me", &mu3Phi_me, "mu3Phi_me/D");
    TreeMuEle->Branch("mu3Mass_me", &mu3Mass_me, "mu3Mass_me/D");

    TreeMuEle->Branch("elePt_me", &elePt_me, "elePt_me/D");
    TreeMuEle->Branch("eleEta_me", &eleEta_me, "eleEta_me/D");
    TreeMuEle->Branch("elePhi_me", &elePhi_me, "elePhi_me/D");
    TreeMuEle->Branch("eleMass_me", &eleMass_me, "eleMass_me/D");

    TreeMuEle->Branch("eventWeight_me", &eventWeight_me, "eventWeight_me/D");

    // ----------- flat tree for mutau channel -----------
    TreeMuTau = new TTree("TreeMuTau","TreeMuTau");

    TreeMuTau->Branch("invMassMu1Mu2_mt", &invMassMu1Mu2_mt, "invMassMu1Mu2_mt/D");
    TreeMuTau->Branch("visMassMu3Tau_mt", &visMassMu3Tau_mt, "visMassMu3Tau_mt/D");
    TreeMuTau->Branch("visMass3MuTau_mt", &visMass3MuTau_mt, "visMass3MuTau_mt/D");

    TreeMuTau->Branch("deltaRMu1Mu2_mt", &deltaRMu1Mu2_mt, "deltaRMu1Mu2_mt/D");
    TreeMuTau->Branch("deltaRMu3Tau_mt", &deltaRMu3Tau_mt, "deltaRMu3Tau_mt/D");

    TreeMuTau->Branch("mu1Pt_mt", &mu1Pt_mt, "mu1Pt_mt/D");
    TreeMuTau->Branch("mu1Eta_mt", &mu1Eta_mt, "mu1Eta_mt/D");
    TreeMuTau->Branch("mu1Phi_mt", &mu1Phi_mt, "mu1Phi_mt/D");
    TreeMuTau->Branch("mu1Mass_mt", &mu1Mass_mt, "mu1Mass_mt/D");

    TreeMuTau->Branch("mu2Pt_mt", &mu2Pt_mt, "mu2Pt_mt/D");
    TreeMuTau->Branch("mu2Eta_mt", &mu2Eta_mt, "mu2Eta_mt/D");
    TreeMuTau->Branch("mu2Phi_mt", &mu2Phi_mt, "mu2Phi_mt/D");
    TreeMuTau->Branch("mu2Mass_mt", &mu2Mass_mt, "mu2Mass_mt/D");

    TreeMuTau->Branch("mu3Pt_mt", &mu3Pt_mt, "mu3Pt_mt/D");
    TreeMuTau->Branch("mu3Eta_mt", &mu3Eta_mt, "mu3Eta_mt/D");
    TreeMuTau->Branch("mu3Phi_mt", &mu3Phi_mt, "mu3Phi_mt/D");
    TreeMuTau->Branch("mu3Mass_mt", &mu3Mass_mt, "mu3Mass_mt/D");

    TreeMuTau->Branch("tauPt_mt", &tauPt_mt, "tauPt_mt/D");
    TreeMuTau->Branch("tauEta_mt", &tauEta_mt, "tauEta_mt/D");
    TreeMuTau->Branch("tauPhi_mt", &tauPhi_mt, "tauPhi_mt/D");
    TreeMuTau->Branch("tauMass_mt", &tauMass_mt, "tauMass_mt/D");
    TreeMuTau->Branch("tauDisc_mt", &tauDisc_mt, "tauDisc_mt/D");
    TreeMuTau->Branch("tauDM_mt", &tauDM_mt, "tauDM_mt/D");

    TreeMuTau->Branch("eventWeight_mt", &eventWeight_mt, "eventWeight_mt/D");

    // ----------- flat tree for etau channel -----------
    TreeEleTau = new TTree("TreeEleTau","TreeEleTau");

    TreeEleTau->Branch("invMassMu1Mu2_et", &invMassMu1Mu2_et, "invMassMu1Mu2_et/D");
    TreeEleTau->Branch("visMassEleTau_et", &visMassEleTau_et, "visMassEleTau_et/D");
    TreeEleTau->Branch("visMass2MuEleTau_et", &visMass2MuEleTau_et, "visMass2MuEleTau_et/D");

    TreeEleTau->Branch("deltaRMu1Mu2_et", &deltaRMu1Mu2_et, "deltaRMu1Mu2_et/D");
    TreeEleTau->Branch("deltaREleTau_et", &deltaREleTau_et, "deltaREleTau_et/D");

    TreeEleTau->Branch("mu1Pt_et", &mu1Pt_et, "mu1Pt_et/D");
    TreeEleTau->Branch("mu1Eta_et", &mu1Eta_et, "mu1Eta_et/D");
    TreeEleTau->Branch("mu1Phi_et", &mu1Phi_et, "mu1Phi_et/D");
    TreeEleTau->Branch("mu1Mass_et", &mu1Mass_et, "mu1Mass_et/D");

    TreeEleTau->Branch("mu2Pt_et", &mu2Pt_et, "mu2Pt_et/D");
    TreeEleTau->Branch("mu2Eta_et", &mu2Eta_et, "mu2Eta_et/D");
    TreeEleTau->Branch("mu2Phi_et", &mu2Phi_et, "mu2Phi_et/D");
    TreeEleTau->Branch("mu2Mass_et", &mu2Mass_et, "mu2Mass_et/D");

    TreeEleTau->Branch("elePt_et", &elePt_et, "elePt_et/D");
    TreeEleTau->Branch("eleEta_et", &eleEta_et, "eleEta_et/D");
    TreeEleTau->Branch("elePhi_et", &elePhi_et, "elePhi_et/D");
    TreeEleTau->Branch("eleMass_et", &eleMass_et, "eleMass_et/D");

    TreeEleTau->Branch("tauPt_et", &tauPt_et, "tauPt_et/D");
    TreeEleTau->Branch("tauEta_et", &tauEta_et, "tauEta_et/D");
    TreeEleTau->Branch("tauPhi_et", &tauPhi_et, "tauPhi_et/D");
    TreeEleTau->Branch("tauMass_et", &tauMass_et, "tauMass_et/D");
    TreeEleTau->Branch("tauDisc_et", &tauDisc_et, "tauDisc_et/D");
    TreeEleTau->Branch("tauDM_et", &tauDM_et, "tauDM_et/D");

    TreeEleTau->Branch("eventWeight_et", &eventWeight_et, "eventWeight_et/D");

    // ----------- flat tree for tautau channel -----------
    TreeTauTau = new TTree("TreeTauTau","TreeTauTau");

    TreeTauTau->Branch("invMassMu1Mu2_tt", &invMassMu1Mu2_tt, "invMassMu1Mu2_tt/D");
    TreeTauTau->Branch("visMassTauTau_tt", &visMassTauTau_tt, "visMassTauTau_tt/D");
    TreeTauTau->Branch("visMass2Mu2Tau_tt", &visMass2Mu2Tau_tt, "visMass2Mu2Tau_tt/D");

    TreeTauTau->Branch("deltaRMu1Mu2_tt", &deltaRMu1Mu2_tt, "deltaRMu1Mu2_tt/D");
    TreeTauTau->Branch("deltaRTauTau_tt", &deltaRTauTau_tt, "deltaRTauTau_tt/D");

    TreeTauTau->Branch("mu1Pt_tt", &mu1Pt_tt, "mu1Pt_tt/D");
    TreeTauTau->Branch("mu1Eta_tt", &mu1Eta_tt, "mu1Eta_tt/D");
    TreeTauTau->Branch("mu1Phi_tt", &mu1Phi_tt, "mu1Phi_tt/D");
    TreeTauTau->Branch("mu1Mass_tt", &mu1Mass_tt, "mu1Mass_tt/D");

    TreeTauTau->Branch("mu2Pt_tt", &mu2Pt_tt, "mu2Pt_tt/D");
    TreeTauTau->Branch("mu2Eta_tt", &mu2Eta_tt, "mu2Eta_tt/D");
    TreeTauTau->Branch("mu2Phi_tt", &mu2Phi_tt, "mu2Phi_tt/D");
    TreeTauTau->Branch("mu2Mass_tt", &mu2Mass_tt, "mu2Mass_tt/D");

    TreeTauTau->Branch("tauPt_tt", &tauPt_tt, "tauPt_tt/D");
    TreeTauTau->Branch("tauEta_tt", &tauEta_tt, "tauEta_tt/D");
    TreeTauTau->Branch("tauPhi_tt", &tauPhi_tt, "tauPhi_tt/D");
    TreeTauTau->Branch("tauMass_tt", &tauMass_tt, "tauMass_tt/D");
    TreeTauTau->Branch("tauDisc_tt", &tauDisc_tt, "tauDisc_tt/D");
    TreeTauTau->Branch("tauDM_tt", &tauDM_tt, "tauDM_tt/D");

    TreeTauTau->Branch("tau2Pt_tt", &tau2Pt_tt, "tau2Pt_tt/D");
    TreeTauTau->Branch("tau2Eta_tt", &tau2Eta_tt, "tau2Eta_tt/D");
    TreeTauTau->Branch("tau2Phi_tt", &tau2Phi_tt, "tau2Phi_tt/D");
    TreeTauTau->Branch("tau2Mass_tt", &tau2Mass_tt, "tau2Mass_tt/D");
    TreeTauTau->Branch("tau2Disc_tt", &tau2Disc_tt, "tau2Disc_tt/D");
    TreeTauTau->Branch("tau2DM_tt", &tau2DM_tt, "tau2DM_tt/D");

    TreeTauTau->Branch("eventWeight_tt", &eventWeight_tt, "eventWeight_tt/D");
}

FlatTreeMuMuTauTau::~FlatTreeMuMuTauTau()
{}
