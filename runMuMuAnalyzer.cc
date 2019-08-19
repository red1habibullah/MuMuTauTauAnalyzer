#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "MuMuAnalyzer.h"
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
        } // end for loop in argc
    } // end if argc > 1
    
    doWhat.ToUpper();

    // ----- This two variables to be used for MC reweighting -----
    //double lumi = 41.9; // fb-1
    float summedWeights = 0;

    //------------------------- data histograms production -------------------
    
    // ------------------------ MC histogram production ------------------
    if (doWhat == "DYJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana DYJetsLumi(inputFile);
            summedWeights = DYJetsLumi.Loop();
            MuMuAnalyzer DYJetsHist(inputFile, outputDir, 1, 1, maxEvents);
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
                MuMuAnalyzer DYJetsHist(fileName, outputDir, 1, 1, maxEvents);
                DYJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if DYJets

    return 0;
}
