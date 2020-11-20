#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <TH1.h>
#include <TH2.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <vector>
#include <cstdarg>
#include "functions.h"

using namespace std;

record::record(): 
    ptLow(0), ptHi(0), etaLow(0), etaHi(0), effi(0)
{
}

record::record(double pt1, double pt2, double eta1, double eta2, double eff):
    ptLow(pt1), ptHi(pt2), etaLow(eta1), etaHi(eta2), effi(eff)
{
}

bool record::belongTo(double pt, double eta)
{
    return (pt < ptHi && pt >= ptLow) && (eta < etaHi && eta >= etaLow);
}

table::table()
{
}

table::table(TString filename)
{
    ifstream file(filename.Data());
    if (!file) {
        cerr << "Could not open " << filename << endl;
    }
    double data[5];
    while (file) {
        for (int i(0); i < 5; i++) {
            file >> data[i];
        }
        recd.push_back(record(data[2], data[3], data[0], data[1], data[4]));
    }

}

double table::getEfficiency(double pt, double eta){
    double hiPtBin= 0;
    for (unsigned int i=0; i != recd.size(); i++) {
        // if finds the proper bin, then return the efficiency
        if ((recd[i]).belongTo(pt, eta)) return recd[i].effi;
        // else store the average pt of the current bin efficency but do not return and try the next bin
        if ((recd[i]).belongTo(0.5*(recd[i].ptHi + recd[i].ptLow), eta)) hiPtBin = recd[i].effi;
    }
    return hiPtBin;
}
