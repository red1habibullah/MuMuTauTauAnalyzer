#ifndef _Histomutau_h_
#define _Histomutau_h_

#include "TH1.h"
#include <iostream>
#include <vector>
#include <string>
#include "TArray.h"
using namespace std;

class Histomutau{

    public:

        vector<TH1D*> histColl;

        TH1D* newTH1D(string, string, string, int, double*);
        TH1D* newTH1D(string, string, string, int, double, double);
        TH1D* newTH1D(string, string, string, vector<double>&);

        Histomutau();
        ~Histomutau();

        TH1D* nMatchedMuPairs;
        TH1D* nMatchedMuTauPairs;
        TH1D* nUnMatchedMu;
        TH1D* nUnMatchedTau;

        TH1D* dRMuMu;
        TH1D* dRMuTau;
        TH1D* invMassMuMu;
        TH1D* invMassMuTau;
};

#endif
