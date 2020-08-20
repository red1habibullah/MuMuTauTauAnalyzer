#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "FakeMuMuTauETauEAnalyzer.h"
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
    double Mu1IsoThreshold = cfg.getD("Mu1IsoThreshold", 0.25);
    double Mu2IsoThreshold = cfg.getD("Mu2IsoThreshold", 0.25);
    TString MuonId         = cfg.getS("MuonId", "LOOSE");
    TString EleRelId      = cfg.getS("EleRelId", "LOOSE");
    double EleIsoUpperBound = cfg.getD("EleIsoUpperBound", 0.25);

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

            else if (currentArg.BeginsWith("Mu1IsoThreshold="))
            {
                getArg(currentArg, Mu1IsoThreshold);
            }

            else if (currentArg.BeginsWith("Mu2IsoThreshold="))
            {
                getArg(currentArg, Mu2IsoThreshold);
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
            FakeMuMuTauETauEAnalyzer DataHist(inputFile, outputDir, 1, 1, maxEvents, false, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
            DataHist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                FakeMuMuTauETauEAnalyzer DataHist(fileName, outputDir, 1, 1, maxEvents, false, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
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
            FakeMuMuTauETauEAnalyzer DYJetsHist(inputFile, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
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
                FakeMuMuTauETauEAnalyzer DYJetsHist(fileName, outputDir, lumi*6077.22*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
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
            FakeMuMuTauETauEAnalyzer WJetsHist(inputFile, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
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
                FakeMuMuTauETauEAnalyzer WJetsHist(fileName, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
                WJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if WJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "TTJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana TTJetsLumi(inputFile);
            summedWeights = TTJetsLumi.Loop();
            FakeMuMuTauETauEAnalyzer TTJetsHist(inputFile, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
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
                FakeMuMuTauETauEAnalyzer TTJetsHist(fileName, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
                TTJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if TTJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "WW" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana WWIncLumi(inputFile);
            summedWeights = WWIncLumi.Loop();
            FakeMuMuTauETauEAnalyzer WWIncHist(inputFile, outputDir, lumi*118.7*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
            WWIncHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana WWIncLumi(fileName);
                summedWeights += WWIncLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                FakeMuMuTauETauEAnalyzer WWIncHist(fileName, outputDir, lumi*118.7*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
                WWIncHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if WWInc

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "WZ" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana WZIncLumi(inputFile);
            summedWeights = WZIncLumi.Loop();
            FakeMuMuTauETauEAnalyzer WZIncHist(inputFile, outputDir, lumi*47.13*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
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
                FakeMuMuTauETauEAnalyzer WZIncHist(fileName, outputDir, lumi*47.13*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
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
            FakeMuMuTauETauEAnalyzer ZZIncHist(inputFile, outputDir, lumi*16.523*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
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
                FakeMuMuTauETauEAnalyzer ZZIncHist(fileName, outputDir, lumi*16.523*1000, summedWeights, maxEvents, true, Mu1IsoThreshold, Mu2IsoThreshold, MuonId, EleRelId, EleIsoUpperBound);
                ZZIncHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if ZZInc

    return 0;
}
