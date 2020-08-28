#ifndef _HistoZmumu_h_
#define _HistoZmumu_h_

#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include <vector>
#include <string>
#include "TArray.h"
using namespace std;

class HistoZmumu{

    public:

        vector<TH1*> histColl;

        TH1D* newTH1D(string, string, int, double*);
        TH1D* newTH1D(string, string, int, double, double);
        TH1D* newTH1D(string, string, vector<double>&);

        TH2D* newTH2D(string, string, string, int, double*, int, double*);
        TH2D* newTH2D(string, string, string, int, double*, int, double, double);
        TH2D* newTH2D(string, string, string, int, double, double, int, double*);
        TH2D* newTH2D(string, string, string, int, double, double, int, double, double);

        HistoZmumu();
        ~HistoZmumu();

        // ------ reco-histograms ------
        TH1D* dRMu1Mu2;
        TH1D* dRMu3Tau;
        TH1D* dREleTau;
        TH1D* dRTauTau;

        TH1D* invMassMu1Mu2;
        TH1D* invMassMu1Mu3;
        TH1D* invMassMu2Mu3;
        TH1D* invMassMu1Ele;
        TH1D* invMassMu2Ele;
        TH1D* invMassMu3Tau;
        TH1D* invMassEleTau;
        TH1D* invMassTauTau;

        TH1D* invMassMuMuTauMuTauHad;
        TH1D* invMassMuMuTauEleTauHad;
        TH1D* invMassMuMuTauHadTauHad;

        TH1D* ptMu1Mu2;
        TH1D* ptMu3Tau;
        TH1D* ptEleTau;
        TH1D* ptTauTau;

        TH1D* ptMuMuTauMuTauHad;
        TH1D* ptMuMuTauEleTauHad;
        TH1D* ptMuMuTauHadTauHad;

        TH1D* mu1Iso;
        TH1D* mu2Iso;
        TH1D* mu3Iso;
        TH1D* ele1Iso;
        TH1D* tauIsoMVA;
        TH1D* tau2IsoMVA;

        TH1D* mu1Pt;
        TH1D* mu1Eta;
        TH1D* mu1Phi;
        
        TH1D* mu2Pt;
        TH1D* mu2Eta;
        TH1D* mu2Phi;

        TH1D* mu3Pt;
        TH1D* mu3Eta;
        TH1D* mu3Phi;

        TH1D* ele1Pt;
        TH1D* ele1Eta;
        TH1D* ele1Phi;

        TH1D* tauPt;
        TH1D* tauEta;
        TH1D* tauPhi;
        TH1D* tauMass;
        TH1D* tauDecayMode;

        TH1D* tau2Pt;
        TH1D* tau2Eta;
        TH1D* tau2Phi;
        TH1D* tau2Mass;
        TH1D* tau2DecayMode;

        TH1D* dRMu1Mu3;
        TH1D* dRMu1Ele1;
        TH1D* dRMu1Tau;
        TH1D* dRMu1Tau2;

        TH1D* dRMu2Mu3;
        TH1D* dRMu2Ele1;
        TH1D* dRMu2Tau;
        TH1D* dRMu2Tau2;

        TH2D* dRInvMassMu1Mu2;
        TH2D* dRInvMassMu3Tau;
        TH2D* dRInvMassEleTau;
        TH2D* dRInvMassTauTau;

        // ------ reco-gen response histograms ------
        TH2D* dRMu1Mu2VSGenMu1GenMu2;
        TH2D* dRMu3TauVSGenMu3GenTauHad;
        TH2D* dRMu3TauVSGenTauMuGenTauHad;
        TH2D* dREleTauVSGenEleGenTauHad;
        TH2D* dREleTauVSGenTauEleGenTauHad;
        TH2D* dRTauTauVSGenTauHadGenTauHad;

        TH2D* invMassMu1Mu2VSGenMu1GenMu2;
        TH2D* invMassMu3TauVSGenMu3GenTauHad;
        TH2D* invMassMu3TauVSGenTauMuGenTauHad;
        TH2D* invMassEleTauVSGenEleGenTauHad;
        TH2D* invMassEleTauVSGenTauEleGenTauHad;
        TH2D* invMassTauTauVSGenTauHadGenTauHad;

        TH2D* mu1PtVSGenMu1Pt;
        TH2D* mu1EtaVSGenMu1Eta;
        TH2D* mu1PhiVSGenMu1Phi;

        TH2D* mu2PtVSGenMu2Pt;
        TH2D* mu2EtaVSGenMu2Eta;
        TH2D* mu2PhiVSGenMu2Phi;

        TH2D* mu3PtVSGenMu3Pt;
        TH2D* mu3EtaVSGenMu3Eta;
        TH2D* mu3PhiVSGenMu3Phi;
        TH2D* mu3PtVSGenTauMuPt;

        TH2D* elePtVSGenElePt;
        TH2D* eleEtaVSGenEleEta;
        TH2D* elePhiVSGenElePhi;
        TH2D* elePtVSGenTauElePt;
        TH2D* elePtVSGenTauEleVisPt;

        TH2D* tauPtVSGenTauHadPt;
        TH2D* tauEtaVSGenTauHadEta;
        TH2D* tauPhiVSGenTauHadPhi;
        TH2D* tauPtVSGenTauHadVisPt;

        TH2D* tau2PtVSGenTauHad2Pt;
        TH2D* tau2EtaVSGenTauHad2Eta;
        TH2D* tau2PhiVSGenTauHad2Phi;
        TH2D* tau2PtVSGenTauHad2VisPt;
};

#endif
