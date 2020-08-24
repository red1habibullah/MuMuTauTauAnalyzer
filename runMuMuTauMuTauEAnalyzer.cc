#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "MuMuTauMuTauEAnalyzer.h"
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
    bool invertedEle1Iso    = cfg.getB("invertedEle1Iso", false);
    double Mu1IsoThreshold  = cfg.getD("Mu1IsoThreshold", 0.25);
    double Mu2IsoThreshold  = cfg.getD("Mu2IsoThreshold", 0.25);
    double Mu3IsoThreshold  = cfg.getD("Mu3IsoThreshold", 0.25);
    double MuIsoUpperBound  = cfg.getD("MuIsoUpperBound", 0.5);
    TString MuonId          = cfg.getS("MuonId", "LOOSE");
    TString EleRelId        = cfg.getS("EleRelId", "LOOSE");
    double EleIsoUpperBound = cfg.getD("EleIsoUpperBound", 0.5);
    double diMuonMassLowThreshold  = cfg.getD("diMuonMassLowThreshold", 0);
    double diMuonMassHighThreshold = cfg.getD("diMuonMassHighThreshold", 25.0);

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

            else if (currentArg.BeginsWith("invertedEle1Iso="))
            {
                getArg(currentArg, invertedEle1Iso);
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

            else if (currentArg.BeginsWith("MuIsoUpperBound="))
            {
                getArg(currentArg, MuIsoUpperBound);
            }

            else if (currentArg.BeginsWith("MuonId="))
            {
                getArg(currentArg, MuonId);
            }

            if (currentArg.BeginsWith("EleRelId="))
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
        } // end for loop in argc
    } // end if argc > 1
    
    doWhat.ToUpper();
    MuonId.ToUpper();
    EleRelId.ToUpper();

    //------------------------- data histograms production -------------------
    if (doWhat == "DATA" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            MuMuTauMuTauEAnalyzer DataHist(inputFile, outputDir, 1, 1, maxEvents, false, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
            DataHist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                MuMuTauMuTauEAnalyzer DataHist(fileName, outputDir, 1, 1, maxEvents, false, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
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
            MuMuTauMuTauEAnalyzer DYJetsHist(inputFile, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
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
                MuMuTauMuTauEAnalyzer DYJetsHist(fileName, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
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
            MuMuTauMuTauEAnalyzer DYJetsLowMassHist(inputFile, outputDir, lumi*71310.0*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
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
                MuMuTauMuTauEAnalyzer DYJetsLowMassHist(fileName, outputDir, lumi*71310.0*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
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
            lumiana ttjetsLumi(inputFile);
            summedWeights = ttjetsLumi.Loop();
            MuMuTauMuTauEAnalyzer ttjetsHist(inputFile, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
            ttjetsHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana ttjetsLumi(fileName);
                summedWeights += ttjetsLumi.Loop();
            }// end while loop for weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                MuMuTauMuTauEAnalyzer ttjetsHist(fileName, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
                ttjetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if ttjets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "WZ" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana WZLumi(inputFile);
            summedWeights = WZLumi.Loop();
            MuMuTauMuTauEAnalyzer WZHist(inputFile, outputDir, lumi*5.26*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
            WZHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana WZLumi(fileName);
                summedWeights += WZLumi.Loop();
            }// end while loop for weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                MuMuTauMuTauEAnalyzer WZHist(fileName, outputDir, lumi*5.26*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
                WZHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if WZ

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "ZZ" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana ZZLumi(inputFile);
            summedWeights = ZZLumi.Loop();
            MuMuTauMuTauEAnalyzer ZZHist(inputFile, outputDir, lumi*1.212*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
            ZZHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana ZZLumi(fileName);
                summedWeights += ZZLumi.Loop();
            }// end while loop for weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                MuMuTauMuTauEAnalyzer ZZHist(fileName, outputDir, lumi*1.212*1000, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
                ZZHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if ZZ

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "H125AA5" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana H125AA5Lumi(inputFile);
            summedWeights = H125AA5Lumi.Loop();
            MuMuTauMuTauEAnalyzer H125AA5Hist(inputFile, outputDir, 1, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
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
                MuMuTauMuTauEAnalyzer H125AA5Hist(fileName, outputDir, 1, summedWeights, maxEvents, true, invertedMu2Iso, invertedMu3Iso, invertedEle1Iso, Mu1IsoThreshold, Mu2IsoThreshold, Mu3IsoThreshold, MuIsoUpperBound, MuonId, EleRelId, EleIsoUpperBound, diMuonMassLowThreshold, diMuonMassHighThreshold);
                H125AA5Hist.Loop();
            } // end while loop on input file list
        } // end else 
    } // end if H125AA5 signal

    return 0;
}
