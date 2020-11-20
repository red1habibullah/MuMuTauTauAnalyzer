#ifndef _functions_h_
#define _functions_h_

#include <iostream>
#include <cstdarg>
#include <vector>
#include <TLorentzVector.h>
#include <TString.h>

using namespace std;

class record{
    public:
        double ptLow, ptHi, etaLow, etaHi, effi;
        record();
        record(double, double, double, double, double);
        bool belongTo(double, double);
};

class table{
    public:
        table();
        table(TString);
        double getEfficiency(double, double);  

    private:
        vector<record> recd;
};

#endif
