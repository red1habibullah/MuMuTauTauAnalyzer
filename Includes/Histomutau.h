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
        TH1D* nMatchedMuTauPair;
        TH1D* nUnMatchedMu;
        TH1D* nUnMatchedTau;

        TH1D* dRMuMu;
        TH1D* dRMuTau;
        TH1D* invMassMuMu;
        TH1D* invMassMuTau;

        TH1D* Mu1IsoMuMuPair;
        TH1D* Mu2IsoMuMuPair;
        TH1D* Mu3IsoMuTauPair;
        TH1D* TauIsoMVAMuTauPair;

        TH1D* unMatchedMuIso;
        TH1D* unMatchedTauIsoMVA;

        TH2D* dRInvMassMuMu;
        TH2D* dRInvMassMuTau;
        TH2D* nMatchedMuPairNMatchedMuTauPair;
};

#endif
