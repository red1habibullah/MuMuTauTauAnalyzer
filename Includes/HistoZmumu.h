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

        TH1D* nMatchedMuPair;
        TH1D* nUnMatchedMu;

        TH1D* dRMuMu;
        TH1D* dRMuTau;
        TH1D* invMassMuMu;
        TH1D* invMassMuTau;
        TH1D* invMassMuMuTauTau;
        TH1D* ptMuMu;
        TH1D* ptMuTau;
        TH1D* ptMuMuTauTau;

        TH1D* Mu1IsoMuMuPair;
        TH1D* Mu2IsoMuMuPair;
        TH1D* Mu3IsoMuTauPair;
        TH1D* TauIsoMVAMuTauPair;

        TH1D* unMatchedMuIso;
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

        TH1D* tauPt;
        TH1D* tauEta;
        TH1D* tauPhi;
        TH1D* tauMass;
        TH1D* tauDecayMode;

        TH1D* dRMu1Mu3;
        TH1D* dRMu1Tau;
        TH1D* dRMu2Mu3;
        TH1D* dRMu2Tau;

        TH2D* dRInvMassMuMu;
        TH2D* dRInvMassMuTau;
};

#endif
