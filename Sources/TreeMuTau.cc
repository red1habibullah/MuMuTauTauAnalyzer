#include "TreeMuTau.h"
#include <TString.h>
#include <TAxis.h>
#define PI 3.14159265359
using namespace std;

TreeMuTau::TreeMuTau(){

    TreeMuMuTauTau = new TTree("TreeMuMuTauTau","TreeMuMuTauTau");
    TreeMuMuTauTau->Branch("invMassMuMu", &invMassMuMu, "invMassMuMu/D");
    TreeMuMuTauTau->Branch("invMassMuTau", &invMassMuTau, "invMassMuTau/D");
    TreeMuMuTauTau->Branch("invMassMuMuTauTau", &invMassMuMuTauTau, "invMassMuMuTauTau/D");
    TreeMuMuTauTau->Branch("eventWeight", &eventWeight, "eventWeight/D");
}

TreeMuTau::~TreeMuTau()
{}
