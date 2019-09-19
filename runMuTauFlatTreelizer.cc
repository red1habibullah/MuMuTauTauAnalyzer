#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "MuTauFlatTreelizer.h"

using namespace std;

int main(int argc, char **argv)
{
    //--- Load configuration ---
    ConfigArg cfg;

    TString inputFile     = cfg.getS("inputFile");
    TString outputDir     = cfg.getS("outputDir");
    TString doWhat        = cfg.getS("doWhat", "DYJETS");
    Long_t maxEvents      = cfg.getL("maxEvents", -1);
    bool invertedMuIso    = cfg.getB("invertedMuIso", false);
    bool invertedTauIso   = cfg.getB("invertedTauIso", false);
    double MuIsoThreshold = cfg.getD("MuIsoThreshold", 0.25);

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

            else if (currentArg.BeginsWith("invertedMuIso="))
            {
                getArg(currentArg, invertedMuIso);
            }

            else if (currentArg.BeginsWith("invertedTauIso="))
            {
                getArg(currentArg, invertedTauIso);
            }

            else if (currentArg.BeginsWith("MuIsoThreshold="))
            {
                getArg(currentArg, MuIsoThreshold);
            }
        } // end for loop in argc
    } // end if argc > 1
    
    doWhat.ToUpper();

    //------------------------- data flat tree production -------------------
    if (doWhat == "DATA" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            MuTauFlatTreelizer DataFlatTree(inputFile, outputDir, maxEvents, false, invertedMuIso, invertedTauIso, MuIsoThreshold);
            DataFlatTree.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                MuTauFlatTreelizer DataFlatTree(fileName, outputDir, maxEvents, false, invertedMuIso, invertedTauIso, MuIsoThreshold);
                DataFlatTree.Loop();
            } // end while loop on file list 
        } // end else inputFile.EndsWith(".root")
    } // end if data

    //------------------------- MC flat tree production -------------------
    else{
        if (inputFile.EndsWith(".root"))
        {
            MuTauFlatTreelizer MCFlatTree(inputFile, outputDir, maxEvents, true, invertedMuIso, invertedTauIso, MuIsoThreshold);
            MCFlatTree.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                MuTauFlatTreelizer MCFlatTree(fileName, outputDir, maxEvents, true, invertedMuIso, invertedTauIso, MuIsoThreshold);
                MCFlatTree.Loop();
            } // end while loop on file list 
        } // end else inputFile.EndsWith(".root")
    } // end else (MC)

    return 0;
}
