#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "MuMuTauTauInclusiveAnalyzer.h"
#include "lumiana.h"

using namespace std;

int main(int argc, char **argv)
{
    //--- Load configuration ---
    ConfigArg cfg;

    TString inputFile       = cfg.getS("inputFile");
    TString outputDir       = cfg.getS("outputDir");
    TString doWhat          = cfg.getS("doWhat", "DYJETS");
    Long_t maxEvents        = cfg.getL("maxEvents", -1);
    double lumi             = cfg.getD("lumi", 1);
    bool invertedMu2Iso     = cfg.getB("invertedMu2Iso", false);
    bool invertedMu3Iso     = cfg.getB("invertedMu3Iso", false);
    bool invertedMu4Iso     = cfg.getB("invertedMu4Iso", false);
    bool invertedEle1Iso    = cfg.getB("invertedEle1Iso", false);
    bool invertedTauIso     = cfg.getB("invertedTauIso", false);
    double Mu1IsoThreshold  = cfg.getD("Mu1IsoThreshold", 0.25);
    double Mu2IsoThreshold  = cfg.getD("Mu2IsoThreshold", 0.25);
    double Mu3IsoThreshold  = cfg.getD("Mu3IsoThreshold", 0.25);
    double Mu4IsoThreshold  = cfg.getD("Mu4IsoThreshold", 0.25);
    double MuIsoUpperBound  = cfg.getD("MuIsoUpperBound", 0.5);
    TString MuonId          = cfg.getS("MuonId", "LOOSE");
    TString EleRelId        = cfg.getS("EleRelId", "LOOSE");
    double EleIsoUpperBound = cfg.getD("EleIsoUpperBound", 0.5);
    double diMuonMassLowThreshold  = cfg.getD("diMuonMassLowThreshold", 0);
    double diMuonMassHighThreshold = cfg.getD("diMuonMassHighThreshold", 25.0);
    bool boostDiTauOpt             = cfg.getB("boostDiTauOpt", false);
    bool tauMVAIsoRawORWP          = cfg.getB("tauMVAIsoRawORWP", false);
    double tauMVAIsoRawThreshold   = cfg.getD("tauMVAIsoRawThreshold", -0.5);
    TString tauMVAIsoWP            = cfg.getS("tauMVAIsoWP", "MEDIUM");
    TString tauAntiMuDisc          = cfg.getS("tauAntiMuDisc", "NULL");
    TString tauAntiEleDisc         = cfg.getS("tauAntiEleDisc", "NULL");
    bool deepTauID                 = cfg.getB("deepTauID", false);
    TString deepTauVSele           = cfg.getS("deepTauVSele", "VVVLOOSE");
    TString deepTauVSmu            = cfg.getS("deepTauVSmu", "VLOOSE");
    TString deepTauVSjet           = cfg.getS("deepTauVSjet", "LOOSE");
    double tauDecayModeThreshold   = cfg.getD("tauDecayModeThreshold", -1);
    TString JetId                  = cfg.getS("JetId", "LOOSE");
    bool massDecorrelation         = cfg.getB("massDecorrelation", false);
    double deepDiTauRawThreshold   = cfg.getD("deepDiTauRawThreshold", 0.5);
    double deepDiTauRawLowerBound  = cfg.getD("deepDiTauRawLowerBound", 0.2);
    int muonScaleSyst              = cfg.getI("muonScaleSyst", 0);
    int electronScaleSyst          = cfg.getI("electronScaleSyst", 0);
    double tauScaleCorr            = cfg.getD("tauScaleCorr", 1);
    TString rochesterFile          = cfg.getS("rochesterFile", "");
    int jetScaleSyst               = cfg.getI("jetScaleSyst", 0);
    TString jecSystFile            = cfg.getS("jecSystFile", "");

    //--- Parse the arguments -----------------------------------------------------
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            TString currentArg = argv[i];
            
            //--- possible options ---
            if (currentArg.BeginsWith("inputFile="))
            {
                getArg(currentArg, inputFile);
            }

            else if (currentArg.BeginsWith("outputDir="))
            {
                getArg(currentArg, outputDir);
            }

            else if (currentArg.BeginsWith("doWhat="))
            {
                getArg(currentArg, doWhat);
            }

            else if (currentArg.BeginsWith("maxEvents="))
            {
                getArg(currentArg, maxEvents);
            }

            else if (currentArg.BeginsWith("lumi="))
            {
                getArg(currentArg, lumi);
            }

            else if (currentArg.BeginsWith("invertedMu2Iso="))
            {
                getArg(currentArg, invertedMu2Iso);
            }

            else if (currentArg.BeginsWith("invertedMu3Iso="))
            {
                getArg(currentArg, invertedMu3Iso);
            }

            else if (currentArg.BeginsWith("invertedMu4Iso="))
            {
                getArg(currentArg, invertedMu4Iso);
            }

            else if (currentArg.BeginsWith("invertedEle1Iso="))
            {
                getArg(currentArg, invertedEle1Iso);
            }

            else if (currentArg.BeginsWith("invertedTauIso="))
            {
                getArg(currentArg, invertedTauIso);
            }

            else if (currentArg.BeginsWith("Mu1IsoThreshold="))
            {
                getArg(currentArg, Mu1IsoThreshold);
            }

            else if (currentArg.BeginsWith("Mu2IsoThreshold="))
            {
                getArg(currentArg, Mu2IsoThreshold);
            }

            else if (currentArg.BeginsWith("Mu3IsoThreshold="))
            {
                getArg(currentArg, Mu3IsoThreshold);
            }

            else if (currentArg.BeginsWith("Mu4IsoThreshold="))
            {
                getArg(currentArg, Mu4IsoThreshold);
            }

            else if (currentArg.BeginsWith("MuIsoUpperBound="))
            {
                getArg(currentArg, MuIsoUpperBound);
            }

            else if (currentArg.BeginsWith("MuonId="))
            {
                getArg(currentArg, MuonId);
            }

            else if (currentArg.BeginsWith("EleRelId="))
            {
                getArg(currentArg, EleRelId);
            }

            else if (currentArg.BeginsWith("EleIsoUpperBound="))
            {
                getArg(currentArg, EleIsoUpperBound);
            }

            else if (currentArg.BeginsWith("diMuonMassLowThreshold="))
            {
                getArg(currentArg, diMuonMassLowThreshold);
            }

            else if (currentArg.BeginsWith("diMuonMassHighThreshold="))
            {
                getArg(currentArg, diMuonMassHighThreshold);
            }

            else if (currentArg.BeginsWith("boostDiTauOpt="))
            {
                getArg(currentArg, boostDiTauOpt);
            }

            else if (currentArg.BeginsWith("tauMVAIsoRawORWP="))
            {
                getArg(currentArg, tauMVAIsoRawORWP);
            }

            else if (currentArg.BeginsWith("tauMVAIsoRawThreshold="))
            {
                getArg(currentArg, tauMVAIsoRawThreshold);
            }

            else if (currentArg.BeginsWith("tauMVAIsoWP="))
            {
                getArg(currentArg, tauMVAIsoWP);
            }

            else if (currentArg.BeginsWith("tauAntiMuDisc="))
            {
                getArg(currentArg, tauAntiMuDisc);
            }

            else if (currentArg.BeginsWith("tauAntiEleDisc="))
            {
                getArg(currentArg, tauAntiEleDisc);
            }

            else if (currentArg.BeginsWith("deepTauID="))
            {
                getArg(currentArg, deepTauID);
            }

            else if (currentArg.BeginsWith("deepTauVSele="))
            {
                getArg(currentArg, deepTauVSele);
            }

            else if (currentArg.BeginsWith("deepTauVSmu="))
            {
                getArg(currentArg, deepTauVSmu);
            }

            else if (currentArg.BeginsWith("deepTauVSjet="))
            {
                getArg(currentArg, deepTauVSjet);
            }

            else if (currentArg.BeginsWith("tauDecayModeThreshold="))
            {
                getArg(currentArg, tauDecayModeThreshold);
            }

            else if (currentArg.BeginsWith("JetId="))
            {
                getArg(currentArg, JetId);
            }

            else if (currentArg.BeginsWith("massDecorrelation="))
            {
                getArg(currentArg, massDecorrelation);
            }

            else if (currentArg.BeginsWith("deepDiTauRawThreshold="))
            {
                getArg(currentArg, deepDiTauRawThreshold);
            }

            else if (currentArg.BeginsWith("deepDiTauRawLowerBound="))
            {
                getArg(currentArg, deepDiTauRawLowerBound);
            }

            else if (currentArg.BeginsWith("muonScaleSyst="))
            {
                getArg(currentArg, muonScaleSyst);
            }

            else if (currentArg.BeginsWith("electronScaleSyst="))
            {
                getArg(currentArg, electronScaleSyst);
            }

            else if (currentArg.BeginsWith("tauScaleCorr="))
            {
                getArg(currentArg, tauScaleCorr);
            }

            else if (currentArg.BeginsWith("rochesterFile="))
            {
                getArg(currentArg, rochesterFile);
            }

            else if (currentArg.BeginsWith("jetScaleSyst="))
            {
                getArg(currentArg, jetScaleSyst);
            }

            else if (currentArg.BeginsWith("jecSystFile="))
            {
                getArg(currentArg, jecSystFile);
            }
        } // end for loop in argc
    } // end if argc > 1
    
    doWhat.ToUpper();
    MuonId.ToUpper();
    EleRelId.ToUpper();
    tauMVAIsoWP.ToUpper();
    tauAntiMuDisc.ToUpper();
    tauAntiEleDisc.ToUpper();
    deepTauVSele.ToUpper();
    deepTauVSmu.ToUpper();
    deepTauVSjet.ToUpper();
    JetId.ToUpper();

    //------------------------- data histograms production -------------------
    if (doWhat == "DATA" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            MuMuTauTauInclusiveAnalyzer DataHist(inputFile, outputDir, 1, 1, maxEvents, false, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
            DataHist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                MuMuTauTauInclusiveAnalyzer DataHist(fileName, outputDir, 1, 1, maxEvents, false, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
                DataHist.Loop();
            } // end while loop on file list 
        } // end else inputFile.EndsWith(".root")
    } // end if data

    // ----- This variable is to be used for MC reweighting -----
    float summedWeights = 0;

    // ------------------------ MC histogram production ------------------
    if (doWhat == "DYJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana DYJetsLumi(inputFile);
            summedWeights = DYJetsLumi.Loop();
            MuMuTauTauInclusiveAnalyzer DYJetsHist(inputFile, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
            DYJetsHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana DYJetsLumi(fileName);
                summedWeights += DYJetsLumi.Loop();
            }// end while loop for weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                MuMuTauTauInclusiveAnalyzer DYJetsHist(fileName, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
                DYJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if DYJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "DYJETSLOWMASS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana DYJetsLowMassLumi(inputFile);
            summedWeights = DYJetsLowMassLumi.Loop();
            MuMuTauTauInclusiveAnalyzer DYJetsLowMassHist(inputFile, outputDir, lumi*71310.0*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
            DYJetsLowMassHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana DYJetsLowMassLumi(fileName);
                summedWeights += DYJetsLowMassLumi.Loop();
            }// end while loop for weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                MuMuTauTauInclusiveAnalyzer DYJetsLowMassHist(fileName, outputDir, lumi*71310.0*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
                DYJetsLowMassHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if DYJetsLowMass

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "TTJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana TTJetsLumi(inputFile);
            summedWeights = TTJetsLumi.Loop();
            MuMuTauTauInclusiveAnalyzer TTJetsHist(inputFile, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
            TTJetsHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana TTJetsLumi(fileName);
                summedWeights += TTJetsLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                MuMuTauTauInclusiveAnalyzer TTJetsHist(fileName, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
                TTJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if TTJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "WZ" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana WZIncLumi(inputFile);
            summedWeights = WZIncLumi.Loop();
            MuMuTauTauInclusiveAnalyzer WZIncHist(inputFile, outputDir, lumi*5.26*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
            WZIncHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana WZIncLumi(fileName);
                summedWeights += WZIncLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                MuMuTauTauInclusiveAnalyzer WZIncHist(fileName, outputDir, lumi*5.26*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
                WZIncHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if WZInc

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "ZZ" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana ZZIncLumi(inputFile);
            summedWeights = ZZIncLumi.Loop();
            MuMuTauTauInclusiveAnalyzer ZZIncHist(inputFile, outputDir, lumi*1.212*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
            ZZIncHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana ZZIncLumi(fileName);
                summedWeights += ZZIncLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                MuMuTauTauInclusiveAnalyzer ZZIncHist(fileName, outputDir, lumi*1.212*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
                ZZIncHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if ZZInc


    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "H125AA5" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana H125AA5Lumi(inputFile);
            summedWeights = H125AA5Lumi.Loop();
            MuMuTauTauInclusiveAnalyzer H125AA5Hist(inputFile, outputDir, lumi*48.58, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
            H125AA5Hist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana H125AA5Lumi(fileName);
                summedWeights += H125AA5Lumi.Loop();
            } // end while loop for weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                MuMuTauTauInclusiveAnalyzer H125AA5Hist(fileName, outputDir, lumi*48.58, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedMu4Iso, invertedEle1Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, Mu4IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold, boostDiTauOpt, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiMuDisc, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, electronScaleSyst, tauScaleCorr, rochesterFile, jetScaleSyst, jecSystFile);
                H125AA5Hist.Loop();
            } // end while loop on input file list
        } // end else 
    } // end if H125AA5 signal

    return 0;
}
