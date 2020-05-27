#ifndef _Histomutau_h_
#define _Histomutau_h_

#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include <vector>
#include <string>
#include "TArray.h"
using namespace std;

class Histomutau{

    public:

        vector<TH1*> histColl;

        TH1D* newTH1D(string, string, int, double*);
        TH1D* newTH1D(string, string, int, double, double);
        TH1D* newTH1D(string, string, vector<double>&);

        TH2D* newTH2D(string, string, string, int, double*, int, double*);
        TH2D* newTH2D(string, string, string, int, double*, int, double, double);
        TH2D* newTH2D(string, string, string, int, double, double, int, double*);
        TH2D* newTH2D(string, string, string, int, double, double, int, double, double);

        Histomutau();
        ~Histomutau();

        TH1D* dRMu1Mu2;
        TH1D* dRMu3Mu4;
        TH1D* dRMu3Ele;
        TH1D* dREleEle;
        TH1D* dRMu3Tau;
        TH1D* dREleTau;
        TH1D* dRTauTau;

        TH1D* invMassMu1Mu2;
        TH1D* invMassMu3Mu4;
        TH1D* invMassMu3Ele;
        TH1D* invMassEleEle;
        TH1D* invMassMu3Tau;
        TH1D* invMassEleTau;
        TH1D* invMassTauTau;

        TH1D* invMassMuMuTauMuTauMu;
        TH1D* invMassMuMuTauMuTauEle;
        TH1D* invMassMuMuTauEleTauEle;
        TH1D* invMassMuMuTauMuTauHad;
        TH1D* invMassMuMuTauEleTauHad;
        TH1D* invMassMuMuTauHadTauHad;

        TH1D* ptMu1Mu2;
        TH1D* ptMu3Mu4;
        TH1D* ptMu3Ele;
        TH1D* ptEleEle;
        TH1D* ptMu3Tau;
        TH1D* ptEleTau;
        TH1D* ptTauTau;

        TH1D* ptMuMuTauMuTauMu;
        TH1D* ptMuMuTauMuTauEle;
        TH1D* ptMuMuTauEleTauEle;
        TH1D* ptMuMuTauMuTauHad;
        TH1D* ptMuMuTauEleTauHad;
        TH1D* ptMuMuTauHadTauHad;

        TH1D* mu1Iso;
        TH1D* mu2Iso;
        TH1D* mu3Iso;
        TH1D* mu4Iso;
        TH1D* ele1Iso;
        TH1D* ele2Iso;
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

        TH1D* mu4Pt;
        TH1D* mu4Eta;
        TH1D* mu4Phi;

        TH1D* ele1Pt;
        TH1D* ele1Eta;
        TH1D* ele1Phi;

        TH1D* ele2Pt;
        TH1D* ele2Eta;
        TH1D* ele2Phi;

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
        TH1D* dRMu1Mu4;
        TH1D* dRMu1Ele1;
        TH1D* dRMu1Ele2;
        TH1D* dRMu1Tau;
        TH1D* dRMu1Tau2;

        TH1D* dRMu2Mu3;
        TH1D* dRMu2Mu4;
        TH1D* dRMu2Ele1;
        TH1D* dRMu2Ele2;
        TH1D* dRMu2Tau;
        TH1D* dRMu2Tau2;

        TH2D* dRInvMassMu1Mu2;
        TH2D* dRInvMassMu3Mu4;
        TH2D* dRInvMassMu3Ele;
        TH2D* dRInvMassEleEle;
        TH2D* dRInvMassMu3Tau;
        TH2D* dRInvMassEleTau;
        TH2D* dRInvMassTauTau;

        // ----------- flat tree for fit -----------
        TTree* TreeMuMuTauTau;
        
        double invMassMuMu;
        double visMassTauTau;
        double visMassMuMuTauTau;

        double deltaRMuMu;
        double deltaRTauTau;

        double Mu1Pt;
        double Mu1Eta;
        double Mu1Phi;
        double Mu1Energy;
        double Mu1Charge;
        double Mu1NTrackerLayers;

        double Mu2Pt;
        double Mu2Eta;
        double Mu2Phi;
        double Mu2Energy;
        double Mu2Charge;
        double Mu2NTrackerLayers;

        double Tau1Pt;
        double Tau1Eta;
        double Tau1Isolation;
        double Tau1DecayMode;

        double Tau2Pt;
        double Tau2Eta;
        double Tau2Isolation;
        double Tau2DecayMode;

        double eventWeight;
};

#endif
