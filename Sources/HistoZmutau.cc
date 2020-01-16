#include <TH1D.h>
#include "HistoZmutau.h"
#include <TString.h>
#include <TAxis.h>
#define PI 3.14159265359
using namespace std;

// ---------- customize the axis settings of TH1D and TH2D ----------------
TH1D* HistoZmutau::newTH1D(string name, string xTitle, int nBins, double *xBins){
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH1D* HistoZmutau::newTH1D(string name, string xTitle, vector<double>& xBinsVect)
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

TH1D* HistoZmutau::newTH1D(string name, string xTitle, int nBins, double xLow, double xUp){
    TH1D* hist = new TH1D(name.c_str(), name.c_str(), nBins, xLow, xUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoZmutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double *xBins, int nBinsY, double *yBinsY){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xBins, nBinsY, yBinsY);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoZmutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double *xBins, int nBinsY, double yLow, double yUp){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xBins, nBinsY, yLow, yUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoZmutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double xLow, double xUp, int nBinsY, double *yBins){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xLow, xUp, nBinsY, yBins);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    histColl.push_back(hist);
    return hist;
}

TH2D* HistoZmutau::newTH2D(string name, string xTitle, string yTitle, int nBinsX, double xLow, double xUp, int nBinsY, double yLow, double yUp){
    TH2D* hist = new TH2D(name.c_str(), name.c_str(), nBinsX, xLow, xUp, nBinsY, yLow, yUp);
    hist->GetXaxis()->SetTitle(xTitle.c_str());
    hist->GetYaxis()->SetTitle(yTitle.c_str());
    hist->GetZaxis()->SetTitle("# Events");
    hist->SetOption("HIST");
    histColl.push_back(hist);
    return hist;
}

// --------------- customize the binning of output histograms -----------------
HistoZmutau::HistoZmutau(){

    double MuPtBin [] = {3, 18, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 65, 69, 73, 77, 81, 85, 89, 93, 97, 101, 105, 110, 115, 120, 126, 133, 141, 150, 160, 171, 183, 196, 210, 225, 241, 258, 276, 300};
    double tauPtBin [] = {8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 66, 74, 84, 96, 110, 126, 144, 164, 186, 210};
    double MuTauPtBin [] = {0, 5, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66, 70, 75, 80, 86, 92, 99, 107, 116, 126, 137, 149, 162, 176, 200};
    double metPtBin [] = {4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 66, 74, 84, 96, 110, 126, 144, 164, 186, 210};

    int NBinsMuPt = sizeof(MuPtBin)/sizeof(MuPtBin[0])-1;
    int NBinsTauPt = sizeof(tauPtBin)/sizeof(tauPtBin[0])-1;
    int NBinsMuTauPt = sizeof(MuTauPtBin)/sizeof(MuTauPtBin[0])-1;
    int NBinsMetPt = sizeof(metPtBin)/sizeof(metPtBin[0])-1;

    nMatchedMuTauPair = newTH1D("nMatchedMuTauPair", "N(#mu#tau)", 5, 0, 5);
    nUnMatchedMu = newTH1D("nUnMatchedMu", "N_{#mu}(unMatch)", 5, 0, 5);
    nUnMatchedTau = newTH1D("nUnMatchedTau", "N_{#tau}(unMatch)", 5, 0, 5);

    dRMuMu = newTH1D("dRMuMu", "#Delta R(#mu_{1}#mu_{2})", 25, 0, 5.0);
    dRMuTau = newTH1D("dRMuTau", "#Delta R(#mu#tau)", 25, 0, 5.0);

    invMassMuMu = newTH1D("invMassMuMu", "M(#mu_{1}#mu_{2})[GeV]", 20, 60, 120);
    invMassMuTau = newTH1D("invMassMuTau", "M(#mu#tau)[GeV]", 25, 0, 150);

    ptMuMu = newTH1D("ptMuMu", "p_{T}(#mu_{1}#mu_{2})[GeV]", NBinsMuTauPt, MuTauPtBin);
    ptMuTau = newTH1D("ptMuTau", "p_{T}(#mu#tau)[GeV]", NBinsMuTauPt, MuTauPtBin);

    mtMuMet = newTH1D("mtMuMet", "M_{T}(#mu#slash{E_{T}})[GeV]", 20, 20, 180);
    pzeta = newTH1D("pzeta", "D_{#zeta}[GeV]", 40, -125, 75);

    unMatchedMuPt = newTH1D("unMatchedMuPt", "p_{T}(#mu_{unMatched}) [GeV]", NBinsMuPt, MuPtBin);
    unMatchedMuEta = newTH1D("unMatchedMuEta", "#eta(#mu_{unMatched})", 20, -2.1, 2.1);
    unMatchedMuPhi = newTH1D("unMatchedMuPhi", "#phi(#mu_{unMatched})", 20, -2.5, 2.5);
    unMatchedMuIso = newTH1D("unMatchedMuIso", "#mu^{iso}(unMatch)", 200, 0, 200);

    unMatchedTauPt = newTH1D("unMatchedTauPt", "p_{T}(#tau_{unMatched}) [GeV]", 50, 3, 203);
    unMatchedTauEta = newTH1D("unMatchedTauEta", "#eta(#tau_{unMatched})", 20, -2.1, 2.1);
    unMatchedTauPhi = newTH1D("unMatchedTauPhi", "#phi(#tau_{unMatched})", 20, -2.5, 2.5);
    unMatchedTauIsoMVA = newTH1D("unMatchedTauIsoMVA", "#tau^{iso}(unMatch)", 20, -1, 1);
    unMatchedTauDecayMode = newTH1D("unMatchedTauDecayMode", "DM(unMatch #tau)", 11, 0, 11);

    muPt = newTH1D("muPt", "p_{T}(#mu) [GeV]", NBinsMuPt, MuPtBin);
    muEta = newTH1D("muEta", "#eta(#mu)", 20, -2.1, 2.1);
    muPhi = newTH1D("muPhi", "#phi(#mu)", 20, -2.5, 2.5);

    mu2Pt = newTH1D("mu2Pt", "p_{T}(#mu_{2}) [GeV]", NBinsMuPt, MuPtBin);
    mu2Eta = newTH1D("mu2Eta", "#eta(#mu_{2})", 20, -2.1, 2.1);
    mu2Phi = newTH1D("mu2Phi", "#phi(#mu_{2})", 20, -2.5, 2.5);

    tauPt = newTH1D("tauPt", "p_{T}(#tau) [GeV]", NBinsTauPt, tauPtBin);
    tauEta = newTH1D("tauEta", "#eta(#tau)", 20, -2.1, 2.1);
    tauPhi = newTH1D("tauPhi", "#phi(#tau)", 20, -2.5, 2.5);
    tauMass = newTH1D("tauMass", "M(#tau) [GeV]", 10, 0, 3);
    tauDecayMode = newTH1D("tauDecayMode", "DecayMode(#tau)", 11, 0, 11);
    tauIsoMVA = newTH1D("tauIsoMVA", "#tau^{iso}", 20, -1, 1);

    metPt = newTH1D("metPt", "#slash{E_{T}} [GeV]", NBinsMetPt, metPtBin);
    metPhi = newTH1D("metPhi", "#phi(#slash{E_{T}})", 20, -2.5, 2.5);

    dRInvMassMuMu = newTH2D("dRInvMassMuMu", "#Delta R(#mu_{1}#mu_{2})", "M(#mu_{1}#mu_{2})[GeV]", 25, 0, 5, 20, 60, 120);
    dRInvMassMuTau = newTH2D("dRInvMassMuTau", "#Delta R(#mu#tau)", "M(#mu#tau)[GeV]", 25, 0, 5, 50, 0, 150);

    // -------------- reco-gen response histograms ------------------
    dRMuMuVSGenMuGenMu = newTH2D("dRMuMuVSGenMuGenMu", "#DeltaR(#mu_{1}^{rec}#mu_{2}^{rec})", "#DeltaR(#mu_{1}^{gen}#mu_{2}^{gen})", 25, 0, 5, 25, 0, 5);
    dRMuTauVSGenMuGenTauHad = newTH2D("dRMuTauVSGenMuGenTauHad", "#DeltaR(#mu^{rec}#tau_{h}^{rec})", "#DeltaR(#mu^{gen}#tau_{h}^{gen})", 25, 0, 5, 25, 0, 5);
    dRMuTauVSGenTauMuGenTauHad = newTH2D("dRMuTauVSGenTauMuGenTauHad", "#DeltaR(#mu^{rec}#tau_{h}^{rec})", "#DeltaR(#tau_{#mu}^{gen}#tau_{h}^{gen})", 25, 0, 5, 25, 0, 5);

    invMassMuMuVSGenMuGenMu = newTH2D("invMassMuMuVSGenMuGenMu", "M(#mu_{1}^{rec}#mu_{2}^{rec})[GeV]", "M(#mu_{1}^{gen}#mu_{2}^{gen})[GeV]", 20, 60, 120, 20, 60, 120);
    invMassMuTauVSGenMuGenTauHad = newTH2D("invMassMuTauVSGenMuGenTauHad", "M(#mu_^{rec}#tau_{h}^{rec})[GeV]", "M(#mu^{gen}#tau_{h}^{gen})[GeV]", 25, 0, 150, 25, 0, 150);
    invMassMuTauVSGenTauMuGenTauHad = newTH2D("invMassMuTauVSGenTauMuGenTauHad", "M(#mu_^{rec}#tau_{h}^{rec})[GeV]", "M(#tau_{#mu}^{gen}#tau_{h}^{gen})[GeV]", 25, 0, 150, 25, 0, 150);

    muPtVSGenMuPt = newTH2D("muPtVSGenMuPt", "p_{T}^{rec}(#mu)[GeV]", "p_{T}^{gen}(#mu)[GeV]", NBinsMuPt, MuPtBin, NBinsMuPt, MuPtBin);
    muEtaVSGenMuEta = newTH2D("muEtaVSGenMuEta", "#eta^{rec}(#mu)", "#eta^{gen}(#mu)", 20, -2.1, 2.1, 20, -2.1, 2.1);
    muPhiVSGenMuPhi = newTH2D("muPhiVSGenMuPhi", "#phi^{rec}(#mu)", "#phi^{gen}(#mu)", 20, -2.1, 2.1, 20, -2.1, 2.1);
    muPtVSGenTauMuPt = newTH2D("muPtVSGenTauMuPt", "p_{T}^{rec}(#mu)[GeV]", "p_{T}^{gen}(#tau_{#mu})[GeV]", NBinsMuPt, MuPtBin, NBinsMuPt, MuPtBin);

    mu2PtVSGenMu2Pt = newTH2D("mu2PtVSGenMu2Pt", "p_{T}^{rec}(#mu_{2})[GeV]", "p_{T}^{gen}(#mu_{2})[GeV]", NBinsMuPt, MuPtBin, NBinsMuPt, MuPtBin);
    mu2EtaVSGenMu2Eta = newTH2D("mu2EtaVSGenMu2Eta", "#eta^{rec}(#mu_{2})", "#eta^{gen}(#mu_{2})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    mu2PhiVSGenMu2Phi = newTH2D("mu2PhiVSGenMu2Phi", "#phi^{rec}(#mu_{2})", "#phi^{gen}(#mu_{2})", 20, -2.1, 2.1, 20, -2.1, 2.1);

    tauPtVSGenTauHadPt = newTH2D("tauPtVSGenTauHadPt", "p_{T}^{rec}(#tau)[GeV]", "p_{T}^{gen}(#tau_{h})[GeV]", NBinsTauPt, tauPtBin, NBinsTauPt, tauPtBin);
    tauEtaVSGenTauHadEta = newTH2D("tauEtaVSGenTauHadEta", "#eta^{rec}(#tau)", "#eta^{gen}(#tau_{h})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    tauPhiVSGenTauHadPhi = newTH2D("tauPhiVSGenTauHadPhi", "#phi^{rec}(#tau)", "#phi^{gen}(#tau_{h})", 20, -2.1, 2.1, 20, -2.1, 2.1);
    tauPtVSGenTauHadVisPt = newTH2D("tauPtVSGenTauHadVisPt", "p_{T}^{rec}(#tau)[GeV]", "p_{T}^{gen}(#tau_{h}^{vis})[GeV]", NBinsTauPt, tauPtBin, NBinsTauPt, tauPtBin);

    tauPtVSTauPtResponse = newTH2D("tauPtVSTauPtResponse", "p_{T}^{rec}(#tau)[GeV]", "p_{T}^{rec}(#tau)/p_{T}^{gen}(#tau_{h}^{vis})", NBinsTauPt, tauPtBin, 20, 0, 2);
    tauPtResponse = newTH1D("tauPtResponse", "p_{T}^{rec}(#tau)/p_{T}^{gen}(#tau_{h}^{vis})", 20, 0, 2);
}

HistoZmutau::~HistoZmutau()
{}
