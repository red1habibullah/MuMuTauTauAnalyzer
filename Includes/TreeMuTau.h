#ifndef _TreeMuTau_h_
#define _TreeMuTau_h_

#include "TTree.h"
#include <iostream>
#include <vector>
#include <string>
#include "TArray.h"
using namespace std;

class TreeMuTau{

    public:

        TreeMuTau();
        ~TreeMuTau();

        TTree* TreeMuMuTauTau;

        double invMassMuMu;
        double invMassMuTau;
        double invMassMuMuTauTau;

};

#endif
