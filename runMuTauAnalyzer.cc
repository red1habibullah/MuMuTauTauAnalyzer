#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "MuTauAnalyzer.h"
#include "lumiana.h"

using namespace std;

int main(int argc, char **argv)
{
    //--- Load configuration ---
    ConfigArg cfg;

    TString inputFile  = cfg.getS("inputFile");
    TString outputDir  = cfg.getS("outputDir");
    TString doWhat     = cfg.getS("doWhat", "DYJETS");
    Long_t maxEvents   = cfg.getL("maxEvents", -1);
    double lumi        = cfg.getD("lumi", 1);

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

            if (currentArg.BeginsWith("outputDir="))
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
        } // end for loop in argc
    } // end if argc > 1
    
    doWhat.ToUpper();

    // ----- This variable is to be used for MC reweighting -----
    float summedWeights = 0;

    //------------------------- data histograms production -------------------

    // ------------------------ MC histogram production ------------------
    if (doWhat == "DYJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana DYJetsLumi(inputFile);
            summedWeights = DYJetsLumi.Loop();
            MuTauAnalyzer DYJetsHist(inputFile, outputDir, lumi*2075.14*3*1000, summedWeights, maxEvents);
            DYJetsHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream fin;
            fin.open(inputFile);
            string fileName;
            while (getline(fin, fileName))
            {
                lumiana DYJetsLumi(fileName);
                summedWeights = DYJetsLumi.Loop();
                MuTauAnalyzer DYJetsHist(fileName, outputDir, lumi*2075.14*3*1000, summedWeights, maxEvents);
                DYJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if DYJets

    if (doWhat == "H125AA5" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana H125AA5Lumi(inputFile);
            summedWeights = H125AA5Lumi.Loop();
            MuTauAnalyzer H125AA5Hist(inputFile, outputDir, 1, 1, maxEvents);
            H125AA5Hist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream fin;
            fin.open(inputFile);
            string fileName;
            while (getline(fin, fileName))
            {
                lumiana H125AA5Lumi(fileName);
                summedWeights = H125AA5Lumi.Loop();
                MuTauAnalyzer H125AA5Hist(fileName, outputDir, 1, 1, maxEvents);
                H125AA5Hist.Loop();
            } // end while loop on input file list
        } // end else 
    } // end if H125AA5 signal

    return 0;
}
