#include <TH1D.h>
#include "Histomutau.h"
#include <TString.h>
#include <TAxis.h>
#define PI 3.14159265359
using namespace std;

// ---------- customize the axis settings of TH1D and TH2D ----------------
TH1D* Histomutau::newTH1D(string name, string xTitle, int nBins, double *xBins){
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH1D* Histomutau::newTH1D(string name, string xTitle, vector<double>& xBinsVect)
{
    int nBins = xBinsVect.size()-1;
    double *xBins = new double[xBinsVect.size()];
    std::copy(xBinsVect.begin(), xBinsVect.end(), xBins);
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    delete [] xBins;
    histColl.push_back(hist);
    return hist;
}

TH1D* Histomutau::newTH1D(string name, string xTitle, int nBins, double xLow, double xUp){
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xLow, xUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

TH2D* Histomutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double *xBins, int nBinsY, double *yBinsY){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xBins, nBinsY, yBinsY);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* Histomutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double *xBins, int nBinsY, double yLow, double yUp){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xBins, nBinsY, yLow, yUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* Histomutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double xLow, double xUp, int nBinsY, double *yBins){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xLow, xUp, nBinsY, yBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* Histomutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double xLow, double xUp, int nBinsY, double yLow, double yUp){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

// --------------- customize the binning of output histograms -----------------
Histomutau::Histomutau(){

    nMatchedMuPairs = newTH1D("nMatchedMuPairs", "Num(#mu_{1}#mu_{2})", 5, 0, 5);
    nMatchedMuTauPairs = newTH1D("nMatchedMuTauPairs", "Num(#mu#tau)", 5, 0, 5);
    nUnMatchedMu = newTH1D("nUnMatchedMu", "Num_unmatch(#mu)", 5, 0, 5);
    nUnMatchedTau = newTH1D("nUnMatchedTau", "Num_unmatch(#tau)", 5, 0, 5);

    invMassMuMu = newTH1D("invMassMuMu", "M(#mu_{1}#mu_{2})[GeV]", 100, 0, 100);
    invMassMuTau = newTH1D("invMassMuTau", "M(#mu#tau)[GeV]", 100, 0, 100);

    dRMuMu = newTH1D("dRMuMu", "#Delta R(#mu_{1}#mu_{2})", 25, 0, 5.0);
    dRMuTau = newTH1D("dRMuTau", "#Delta R(#mu#tau)", 25, 0, 5.0);

    Mu1IsoMuMuPair = newTH1D("Mu1IsoMuMuPair", "#mu_{1}^{iso}(#mu#mu)", 200, 0, 200);
    Mu2IsoMuMuPair = newTH1D("Mu2IsoMuMuPair", "#mu_{2}^{iso}(#mu#mu)", 200, 0, 200);
    Mu3IsoMuTauPair = newTH1D("Mu3IsoMuTauPair", "#mu_{3}^{iso}(#mu#tau)", 200, 0, 200);
    TauIsoMVAMuTauPair = newTH1D("TauIsoMVAMuTauPair", "#tau^{iso}(#mu#tau)", 20, -1, 1);

    unMatchedMuIso = newTH1D("unMatchedMuIso", "#mu^{iso}(unMatch)", 200, 0, 200);
    unMatchedTauIsoMVA = newTH1D("unMatchedTauIsoMVA", "#tau^{iso}(unMatch)", 20, -1, 1);

    dRInvMassMuMu = newTH2D("dRInvMassMuMu", "#Delta R(#mu_{1}#mu_{2})", "M(#mu_{1}#mu_{2})[GeV]", 25, 0, 5, 100, 0, 100);
    dRInvMassMuTau = newTH2D("dRInvMassMuTau", "#Delta R(#mu#tau)", "M(#mu#tau)[GeV]", 25, 0, 5, 100, 0, 100);
}

Histomutau::~Histomutau()
{}
