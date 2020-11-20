#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "MuMuTauHadTauHadAnalyzer.h"
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
    double Mu1IsoThreshold = cfg.getD("Mu1IsoThreshold", 0.25);
    double Mu2IsoThreshold = cfg.getD("Mu2IsoThreshold", 0.25);
    double MuIsoUpperBound = cfg.getD("MuIsoUpperBound", 0.5);
    TString MuonId         = cfg.getS("MuonId", "LOOSE");
    double diMuonMassLowThreshold  = cfg.getD("diMuonMassLowThreshold", 0);
    double diMuonMassHighThreshold = cfg.getD("diMuonMassHighThreshold", 25.0);
    TString JetId                  = cfg.getS("JetId", "LOOSE");
    bool massDecorrelation         = cfg.getB("massDecorrelation", false);
    double deepDiTauRawThreshold   = cfg.getD("deepDiTauRawThreshold", 0.5);
    double deepDiTauRawLowerBound  = cfg.getD("deepDiTauRawLowerBound", 0.2);
    int muonScaleSyst              = cfg.getI("muonScaleSyst", 0);
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

            else if (currentArg.BeginsWith("MuIsoUpperBound="))
            {
                getArg(currentArg, MuIsoUpperBound);
            }

            else if (currentArg.BeginsWith("MuonId="))
            {
                getArg(currentArg, MuonId);
            }

            else if (currentArg.BeginsWith("diMuonMassLowThreshold="))
            {
                getArg(currentArg, diMuonMassLowThreshold);
            }

            else if (currentArg.BeginsWith("diMuonMassHighThreshold="))
            {
                getArg(currentArg, diMuonMassHighThreshold);
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
    JetId.ToUpper();

    //------------------------- data histograms production -------------------
    if (doWhat == "DATA" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            MuMuTauHadTauHadAnalyzer DataHist(inputFile, outputDir, 1, 1, maxEvents, false, invertedMu2Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, MuIsoUpperBound, MuonId, diMuonMassLowThreshold, diMuonMassHighThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, rochesterFile, jetScaleSyst, jecSystFile);
            DataHist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                MuMuTauHadTauHadAnalyzer DataHist(fileName, outputDir, 1, 1, maxEvents, false, invertedMu2Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, MuIsoUpperBound, MuonId, diMuonMassLowThreshold, diMuonMassHighThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, rochesterFile, jetScaleSyst, jecSystFile);
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
            MuMuTauHadTauHadAnalyzer DYJetsHist(inputFile, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, MuIsoUpperBound, MuonId, diMuonMassLowThreshold, diMuonMassHighThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, rochesterFile, jetScaleSyst, jecSystFile);
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
                MuMuTauHadTauHadAnalyzer DYJetsHist(fileName, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, MuIsoUpperBound, MuonId, diMuonMassLowThreshold, diMuonMassHighThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, rochesterFile, jetScaleSyst, jecSystFile);
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
            MuMuTauHadTauHadAnalyzer WJetsHist(inputFile, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, MuIsoUpperBound, MuonId, diMuonMassLowThreshold, diMuonMassHighThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, rochesterFile, jetScaleSyst, jecSystFile);
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
                MuMuTauHadTauHadAnalyzer WJetsHist(fileName, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, MuIsoUpperBound, MuonId, diMuonMassLowThreshold, diMuonMassHighThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, rochesterFile, jetScaleSyst, jecSystFile);
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
            MuMuTauHadTauHadAnalyzer H125AA5Hist(inputFile, outputDir, 1, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, MuIsoUpperBound, MuonId, diMuonMassLowThreshold, diMuonMassHighThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, rochesterFile, jetScaleSyst, jecSystFile);
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
                MuMuTauHadTauHadAnalyzer H125AA5Hist(fileName, outputDir, 1, summedWeights, maxEvents, true, invertedMu2Iso, invertedTauIso, Mu1IsoThreshold, Mu2IsoThreshold, MuIsoUpperBound, MuonId, diMuonMassLowThreshold, diMuonMassHighThreshold, JetId, massDecorrelation, deepDiTauRawThreshold, deepDiTauRawLowerBound, muonScaleSyst, rochesterFile, jetScaleSyst, jecSystFile);
                H125AA5Hist.Loop();
            } // end while loop on input file list
        } // end else 
    } // end if H125AA5 signal

    return 0;
}
