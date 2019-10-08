#ifndef _Histomutau_h_
#define _Histomutau_h_

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

        TH1D* nMatchedMuPair;
        TH1D* nMatchedMuMuPair;
        TH1D* nMatchedMuTauPair;
        TH1D* nUnMatchedMu;
        TH1D* nUnMatchedTau;

        TH1D* dRMu1Mu2;
        TH1D* dRMu3Mu4;
        TH1D* dRMu3Tau;

        TH1D* invMassMu1Mu2;
        TH1D* invMassMu3Mu4;
        TH1D* invMassMu3Tau;

        TH1D* invMassMuMuTauMuTauMu;
        TH1D* invMassMuMuTauMuTauHad;

        TH1D* ptMu1Mu2;
        TH1D* ptMu3Mu4;
        TH1D* ptMu3Tau;

        TH1D* ptMuMuTauMuTauMu;
        TH1D* ptMuMuTauMuTauHad;

        TH1D* mu1Iso;
        TH1D* mu2Iso;
        TH1D* mu3Iso;
        TH1D* mu4Iso;
        TH1D* tauIsoMVA;

        TH1D* unMatchedMuIso;
        TH1D* unMatchedTauIsoMVA;
        TH1D* unMatchedTauDecayMode;

        TH1D* unMatchedMuPt;
        TH1D* unMatchedMuEta;
        TH1D* unMatchedMuPhi;

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

        TH1D* tauPt;
        TH1D* tauEta;
        TH1D* tauPhi;
        TH1D* tauMass;
        TH1D* tauDecayMode;

        TH1D* dRMu1Mu3;
        TH1D* dRMu1Mu4;
        TH1D* dRMu1Tau;

        TH1D* dRMu2Mu3;
        TH1D* dRMu2Mu4;
        TH1D* dRMu2Tau;

        TH2D* dRInvMassMu1Mu2;
        TH2D* dRInvMassMu3Mu4;
        TH2D* dRInvMassMu3Tau;
        
        TH2D* nMatchedMuPairNMatchedMuMuPair;
        TH2D* nMatchedMuPairNMatchedMuTauPair;
};

#endif
