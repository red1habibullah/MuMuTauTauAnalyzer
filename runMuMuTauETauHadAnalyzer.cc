#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "MuMuTauETauHadAnalyzer.h"
#include "lumiana.h"

using namespace std;

int main(int argc, char **argv)
{
    //--- Load configuration ---
    ConfigArg cfg;

    TString inputFile      = cfg.getS("inputFile");
    TString outputDir      = cfg.getS("outputDir");
    TString doWhat         = cfg.getS("doWhat", "DYJETS");
    Long_t maxEvents       = cfg.getL("maxEvents", -1);
    double lumi            = cfg.getD("lumi", 1);
    bool invertedMu2Iso    = cfg.getB("invertedMu2Iso", false);
    bool invertedTauIso    = cfg.getB("invertedTauIso", false);
    double Mu2IsoThreshold = cfg.getD("Mu2IsoThreshold", 0.25);
    double diMuonMassLowThreshold  = cfg.getD("diMuonMassLowThreshold", 0);
    double diMuonMassHighThreshold = cfg.getD("diMuonMassHighThreshold", 25.0);
    bool tauMVAIsoRawORWP          = cfg.getB("tauMVAIsoRawORWP", false);
    double tauMVAIsoRawThreshold   = cfg.getD("tauMVAIsoRawThreshold", -0.5);
    TString tauMVAIsoWP            = cfg.getS("tauMVAIsoWP", "MEDIUM");
    TString tauAntiEleDisc         = cfg.getS("tauAntiEleDisc", "NULL");
    bool deepTauID                 = cfg.getB("deepTauID", false);
    TString deepTauVSele           = cfg.getS("deepTauVSele", "VVVLOOSE");
    TString deepTauVSmu            = cfg.getS("deepTauVSmu", "VLOOSE");
    TString deepTauVSjet           = cfg.getS("deepTauVSjet", "LOOSE");
    double tauDecayModeThreshold   = cfg.getD("tauDecayModeThreshold", -1);

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

            else if (currentArg.BeginsWith("invertedTauIso="))
            {
                getArg(currentArg, invertedTauIso);
            }

            else if (currentArg.BeginsWith("Mu2IsoThreshold="))
            {
                getArg(currentArg, Mu2IsoThreshold);
            }

            else if (currentArg.BeginsWith("diMuonMassLowThreshold="))
            {
                getArg(currentArg, diMuonMassLowThreshold);
            }

            else if (currentArg.BeginsWith("diMuonMassHighThreshold="))
            {
                getArg(currentArg, diMuonMassHighThreshold);
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

        } // end for loop in argc
    } // end if argc > 1
    
    doWhat.ToUpper();
    tauMVAIsoWP.ToUpper();
    tauAntiEleDisc.ToUpper();
    deepTauVSele.ToUpper();
    deepTauVSmu.ToUpper();
    deepTauVSjet.ToUpper();

    //------------------------- data histograms production -------------------
    if (doWhat == "DATA" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            MuMuTauETauHadAnalyzer DataHist(inputFile, outputDir, 1, 1, maxEvents, false, invertedMu2Iso, invertedTauIso, Mu2IsoThreshold, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold);
            DataHist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                MuMuTauETauHadAnalyzer DataHist(fileName, outputDir, 1, 1, maxEvents, false, invertedMu2Iso, invertedTauIso, Mu2IsoThreshold, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold);
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
            MuMuTauETauHadAnalyzer DYJetsHist(inputFile, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu2IsoThreshold, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold);
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
                MuMuTauETauHadAnalyzer DYJetsHist(fileName, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu2IsoThreshold, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold);
                DYJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if DYJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;


    if (doWhat == "WJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana WJetsLumi(inputFile);
            summedWeights = WJetsLumi.Loop();
            MuMuTauETauHadAnalyzer WJetsHist(inputFile, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu2IsoThreshold, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold);
            WJetsHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana WJetsLumi(fileName);
                summedWeights += WJetsLumi.Loop();
            }// end while loop for weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                MuMuTauETauHadAnalyzer WJetsHist(fileName, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu2IsoThreshold, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold);
                WJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if WJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;


    if (doWhat == "H125AA5" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana H125AA5Lumi(inputFile);
            summedWeights = H125AA5Lumi.Loop();
            MuMuTauETauHadAnalyzer H125AA5Hist(inputFile, outputDir, 1, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu2IsoThreshold, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold);
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
                MuMuTauETauHadAnalyzer H125AA5Hist(fileName, outputDir, 1, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu2IsoThreshold, diMuonMassLowThreshold, diMuonMassHighThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, tauAntiEleDisc, deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet, tauDecayModeThreshold);
                H125AA5Hist.Loop();
            } // end while loop on input file list
        } // end else 
    } // end if H125AA5 signal

    return 0;
}
