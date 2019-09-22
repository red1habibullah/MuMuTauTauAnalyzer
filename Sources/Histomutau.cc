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

    nMatchedMuPair = newTH1D("nMatchedMuPair", "N(#mu_{1}#mu_{2})", 5, 0, 5);
    nMatchedMuTauPair = newTH1D("nMatchedMuTauPair", "N(#mu#tau)", 5, 0, 5);
    nUnMatchedMu = newTH1D("nUnMatchedMu", "N_{#mu}(unMatch)", 5, 0, 5);
    nUnMatchedTau = newTH1D("nUnMatchedTau", "N_{#tau}(unMatch)", 5, 0, 5);

    invMassMuMu = newTH1D("invMassMuMu", "M(#mu_{1}#mu_{2})[GeV]", 100, 0, 100);
    invMassMuTau = newTH1D("invMassMuTau", "M(#mu#tau)[GeV]", 100, 0, 100);
    invMassMuMuTauTau = newTH1D("invMassMuMuTauTau", "M(#mu#mu#tau#tau)[GeV]", 100, 20, 300);

    dRMuMu = newTH1D("dRMuMu", "#Delta R(#mu_{1}#mu_{2})", 25, 0, 1.0);
    dRMuTau = newTH1D("dRMuTau", "#Delta R(#mu#tau)", 25, 0, 1.0);

    Mu1IsoMuMuPair = newTH1D("Mu1IsoMuMuPair", "#mu_{1}^{iso}(#mu#mu)", 20, 0, 0.25);
    Mu2IsoMuMuPair = newTH1D("Mu2IsoMuMuPair", "#mu_{2}^{iso}(#mu#mu)", 20, 0, 0.25);
    Mu3IsoMuTauPair = newTH1D("Mu3IsoMuTauPair", "#mu_{3}^{iso}(#mu#tau)", 20, 0, 20);
    TauIsoMVAMuTauPair = newTH1D("TauIsoMVAMuTauPair", "#tau^{iso}(#mu#tau)", 20, -1, 1);

    unMatchedMuIso = newTH1D("unMatchedMuIso", "#mu^{iso}(unMatch)", 200, 0, 200);
    unMatchedTauIsoMVA = newTH1D("unMatchedTauIsoMVA", "#tau^{iso}(unMatch)", 20, -1, 1);
    unMatchedTauDecayMode = newTH1D("unMatchedTauDecayMode", "DM(unMatch #tau)", 11, 0, 11);

    mu1Pt = newTH1D("mu1Pt", "p_{T}(#mu_{1}) [GeV]", 50, 5, 205);
    mu1Eta = newTH1D("mu1Eta", "#eta(#mu_{1})", 20, -2.1, 2.1);
    mu1Phi = newTH1D("mu1Phi", "#phi(#mu_{1})", 20, -2.5, 2.5);

    mu2Pt = newTH1D("mu2Pt", "p_{T}(#mu_{2}) [GeV]", 50, 3, 203);
    mu2Eta = newTH1D("mu2Eta", "#eta(#mu_{2})", 20, -2.1, 2.1);
    mu2Phi = newTH1D("mu2Phi", "#phi(#mu_{2})", 20, -2.5, 2.5);

    mu3Pt = newTH1D("mu3Pt", "p_{T}(#mu_{3}) [GeV]", 50, 3, 203);
    mu3Eta = newTH1D("mu3Eta", "#eta(#mu_{3})", 20, -2.1, 2.1);
    mu3Phi = newTH1D("mu3Phi", "#phi(#mu_{3})", 20, -2.5, 2.5);

    tauPt = newTH1D("tauPt", "p_{T}(#tau) [GeV]", 50, 3, 203);
    tauEta = newTH1D("tauEta", "#eta(#tau)", 20, -2.1, 2.1);
    tauPhi = newTH1D("tauPhi", "#phi(#tau)", 20, -2.5, 2.5);
    tauMass = newTH1D("tauMass", "M(#tau) [GeV]", 20, 0, 20);
    tauDecayMode = newTH1D("tauDecayMode", "DecayMode(#tau)", 11, 0, 11);

    dRMu1Mu3 = newTH1D("dRMu1Mu3", "#Delta R(#mu_{1}#mu_{3})", 25, 0, 5);
    dRMu1Tau = newTH1D("dRMu1Tau", "#Delta R(#mu_{1}#tau)", 25, 0, 5);
    dRMu2Mu3 = newTH1D("dRMu2Mu3", "#Delta R(#mu_{2}#mu_{3})", 25, 0, 5);
    dRMu2Tau = newTH1D("dRMu2Tau", "#Delta R(#mu_{2}#tau)", 25, 0, 5);

    dRInvMassMuMu = newTH2D("dRInvMassMuMu", "#Delta R(#mu_{1}#mu_{2})", "M(#mu_{1}#mu_{2})[GeV]", 25, 0, 1, 100, 0, 100);
    dRInvMassMuTau = newTH2D("dRInvMassMuTau", "#Delta R(#mu#tau)", "M(#mu#tau)[GeV]", 25, 0, 1, 100, 0, 100);
    nMatchedMuPairNMatchedMuTauPair = newTH2D("nMatchedMuPairNMatchedMuTauPair", "N(#mu_{1}#mu_{2})", "N(#mu#tau)", 4, 0, 4, 4, 0, 4);
}

Histomutau::~Histomutau()
{}
