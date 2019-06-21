#include <TH1D.h>
#include "Histomutau.h"
#include <TString.h>
#include <TAxis.h>
#define PI 3.14159265359
using namespace std;

TH1D* Histomutau::newTH1D(string name, string title, string xTitle, int nBins, double *xBins){
    TH1D* hist = new TH1D(name.c_str(), title.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH1D* Histomutau::newTH1D(string name, string title, string xTitle, vector<double>& xBinsVect)
{
    int nBins = xBinsVect.size()-1;
    double *xBins = new double[xBinsVect.size()];
    std::copy(xBinsVect.begin(), xBinsVect.end(), xBins);
    TH1D* hist = new TH1D(name.c_str(), title.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    delete [] xBins;
    histColl.push_back(hist);
    return hist;
}

TH1D* Histomutau::newTH1D(string name, string title, string xTitle, int nBins, double xLow, double xUp){
    TH1D* hist = new TH1D(name.c_str(), title.c_str(), nBins, xLow, xUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

Histomutau::Histomutau(){

    nMatchedMuPairs = newTH1D("nMatchedMuPairs", "nMatchedMuPairs", "Num(#mu_{1}#mu_{2})", 5, 0, 5);
    nMatchedMuTauPairs = newTH1D("nMatchedMuTauPairs", "nMatchedMuTauPairs", "Num(#mu#tau)", 5, 0, 5);
    nUnMatchedMu = newTH1D("nUnMatchedMu", "nUnMatchedMu", "Num_unmatch(#mu)", 5, 0, 5);
    nUnMatchedTau = newTH1D("nUnMatchedTau", "nUnMatchedTau", "Num_unmatch(#tau)", 5, 0, 5);

    invMassMuMu = newTH1D("invMassMuMu", "invMassMuMu", "M(#mu_{1}#mu_{2})[GeV]", 20, 0, 20);
    invMassMuTau = newTH1D("invMassMuTau", "invMassMuTau", "M(#mu#tau)[GeV]", 20, 0, 20);

    dRMuMu = newTH1D("dRMuMu", "dRMuMu", "#Delta R(#mu_{1}#mu_{2})", 25, 0, 5.0);
    dRMuTau = newTH1D("dRMuTau", "dRMuTau", "#Delta R(#mu#tau)", 25, 0, 5.0);

    Mu1IsoMuMuPair = newTH1D("Mu1IsoMuMuPair", "Mu1IsoMuMuPair", "#mu_{1}^{iso}(#mu#mu)", 200, 0, 200);
    Mu2IsoMuMuPair = newTH1D("Mu2IsoMuMuPair", "Mu2IsoMuMuPair", "#mu_{2}^{iso}(#mu#mu)", 200, 0, 200);
    Mu3IsoMuTauPair = newTH1D("Mu3IsoMuTauPair", "Mu3IsoMuTauPair", "#mu_{3}^{iso}(#mu#tau)", 200, 0, 200);
    TauIsoMVAMuTauPair = newTH1D("TauIsoMVAMuTauPair", "TauIsoMVAMuTauPair", "#tau^{iso}(#mu#tau)", 20, -1, 1);

    unMatchedMuIso = newTH1D("unMatchedMuIso", "unMatchedMuIso", "#mu^{iso}(unMatch)", 200, 0, 200);
    unMatchedTauIsoMVA = newTH1D("unMatchedTauIsoMVA", "unMatchedTauIsoMVA", "#tau^{iso}(unMatch)", 20, -1, 1);
}

Histomutau::~Histomutau()
{}
