#include <fstream>
#include <TString.h>
#include "ArgParser.h"
#include "ConfigArg.h"
#include "ZTauMuTauHadAnalyzer.h"
#include "lumiana.h"

using namespace std;

int main(int argc, char **argv)
{
    //--- Load configuration ---
    ConfigArg cfg;

    TString inputFile            = cfg.getS("inputFile");
    TString outputDir            = cfg.getS("outputDir");
    TString doWhat               = cfg.getS("doWhat", "DYJETS");
    Long_t maxEvents             = cfg.getL("maxEvents", -1);
    double lumi                  = cfg.getD("lumi", 1);
    bool invertedMu1Iso          = cfg.getB("invertedMu1Iso", false);
    float Mu1IsoThreshold        = cfg.getF("Mu1IsoThreshold", 0.25); 
    bool tauMVAIsoRawORWP        = cfg.getB("tauMVAIsoRawORWP", false);
    double tauMVAIsoRawThreshold = cfg.getD("tauMVAIsoRawThreshold", -0.5);
    TString tauMVAIsoWP          = cfg.getS("tauMVAIsoWP", "MEDIUM");
    bool signSameOROpposite      = cfg.getB("signSameOROpposite", false);
    float mTMuMetLowThreshold    = cfg.getF("mTMuMetLowThreshold", 0);
    float mTMuMetHighThreshold   = cfg.getF("mTMuMetHighThreshold", 160.0);
    bool invertedPzetaCut        = cfg.getB("invertedPzetaCut", false);
    float pzetaThreshold         = cfg.getF("pzetaThreshold", -125.0);
    float tauPtLowThreshold      = cfg.getF("tauPtLowThreshold", 10.0);
    float tauPtHighThreshold     = cfg.getF("tauPtHighThreshold", 10000.0);
    TString tauAntiMuDisc        = cfg.getS("tauAntiMuDisc", "LOOSE");
    TString tauAntiEleDisc       = cfg.getS("tauAntiEleDisc", "LOOSE");
    bool deepTauID               = cfg.getB("deepTauID", false);
    TString deepTauVSele         = cfg.getS("deepTauVSele", "VVVLOOSE");
    TString deepTauVSmu          = cfg.getS("deepTauVSmu", "VLOOSE");
    TString deepTauVSjet         = cfg.getS("deepTauVSjet", "LOOSE");

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

            else if (currentArg.BeginsWith("invertedMu1Iso="))
            {
                getArg(currentArg, invertedMu1Iso);
            }

            else if (currentArg.BeginsWith("Mu1IsoThreshold="))
            {
                getArg(currentArg, Mu1IsoThreshold);
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

            else if (currentArg.BeginsWith("signSameOROpposite="))
            {
                getArg(currentArg, signSameOROpposite);
            }

            else if (currentArg.BeginsWith("mTMuMetLowThreshold="))
            {
                getArg(currentArg, mTMuMetLowThreshold);
            }

            else if (currentArg.BeginsWith("mTMuMetHighThreshold="))
            {
                getArg(currentArg, mTMuMetHighThreshold);
            }

            else if (currentArg.BeginsWith("invertedPzetaCut="))
            {
                getArg(currentArg, invertedPzetaCut);
            }

            else if (currentArg.BeginsWith("pzetaThreshold="))
            {
                getArg(currentArg, pzetaThreshold);
            }

            else if (currentArg.BeginsWith("tauPtLowThreshold="))
            {
                getArg(currentArg, tauPtLowThreshold);
            }

            else if (currentArg.BeginsWith("tauPtHighThreshold="))
            {
                getArg(currentArg, tauPtHighThreshold);
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

        } // end for loop in argc
    } // end if argc > 1
    
    doWhat.ToUpper();
    tauMVAIsoWP.ToUpper();
    tauAntiMuDisc.ToUpper();
    tauAntiEleDisc.ToUpper();
    deepTauVSele.ToUpper();
    deepTauVSmu.ToUpper();
    deepTauVSjet.ToUpper();

    //------------------------- data histograms production -------------------
    if (doWhat == "DATA" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            ZTauMuTauHadAnalyzer DataHist(inputFile, outputDir, 1, 1, maxEvents, false, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "DATA", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
            DataHist.Loop();
        } // end if inputFile.EndsWith(".root")
        
        else{
            ifstream finTree;
            finTree.open(inputFile);
            string fileName;
            while (getline(finTree, fileName))
            {
                ZTauMuTauHadAnalyzer DataHist(fileName, outputDir, 1, 1, maxEvents, false, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "DATA", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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

            ZTauMuTauHadAnalyzer DYJetsHist(inputFile, outputDir, lumi*2075.14*3*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "DYJ", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                ZTauMuTauHadAnalyzer DYJetsHist(fileName, outputDir, lumi*2075.14*3*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "DYJ", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
                DYJetsHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if DYJets

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "ZTT" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana DYJetsLumi(inputFile);
            summedWeights = DYJetsLumi.Loop();

            ZTauMuTauHadAnalyzer ZTauTauHist(inputFile, outputDir, lumi*2075.14*3*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "ZTT", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
            ZTauTauHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana DYJetsLumi(fileName);
                summedWeights += DYJetsLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                // ----------------- ZTauTau -------------------
                ZTauMuTauHadAnalyzer ZTauTauHist(fileName, outputDir, lumi*2075.14*3*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "ZTT", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
                ZTauTauHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if ZTT

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "DYB" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana DYJetsLumi(inputFile);
            summedWeights = DYJetsLumi.Loop();

            ZTauMuTauHadAnalyzer ZMuMuTauHist(inputFile, outputDir, lumi*2075.14*3*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "DYB", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
            ZMuMuTauHist.Loop();
        } // end if inputFile.EndsWith(".root")

        else{
            ifstream finLumi;
            finLumi.open(inputFile);
            string fileName;
            while (getline(finLumi, fileName))
            {
                lumiana DYJetsLumi(fileName);
                summedWeights += DYJetsLumi.Loop();
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                ZTauMuTauHadAnalyzer ZMuMuTauHist(fileName, outputDir, lumi*2075.14*3*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "DYB", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
                ZMuMuTauHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if DYB

    // --- always need to reinitialize the weight parameter for new sample -----
    summedWeights = 0;

    if (doWhat == "WJETS" || doWhat == "ALL")
    {
        if (inputFile.EndsWith(".root"))
        {
            lumiana WJetsLumi(inputFile);
            summedWeights = WJetsLumi.Loop();
            ZTauMuTauHadAnalyzer WJetsHist(inputFile, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "WJETS", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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
            } // end while loop on weight sum

            ifstream finTree;
            finTree.open(inputFile);
            while (getline(finTree, fileName))
            {
                ZTauMuTauHadAnalyzer WJetsHist(fileName, outputDir, lumi*61526.7*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "WJETS", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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
            ZTauMuTauHadAnalyzer TTJetsHist(inputFile, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "TTJETS", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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
                ZTauMuTauHadAnalyzer TTJetsHist(fileName, outputDir, lumi*831.76*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "TTJETS", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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
            ZTauMuTauHadAnalyzer WWIncHist(inputFile, outputDir, lumi*118.7*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "WW", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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
                ZTauMuTauHadAnalyzer WWIncHist(fileName, outputDir, lumi*118.7*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "WW", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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
            ZTauMuTauHadAnalyzer WZIncHist(inputFile, outputDir, lumi*47.13*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "WZ", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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
                ZTauMuTauHadAnalyzer WZIncHist(fileName, outputDir, lumi*47.13*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "WZ", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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
            ZTauMuTauHadAnalyzer ZZIncHist(inputFile, outputDir, lumi*16.523*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "ZZ", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
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
                ZTauMuTauHadAnalyzer ZZIncHist(fileName, outputDir, lumi*16.523*1000, summedWeights, maxEvents, true, invertedMu1Iso, Mu1IsoThreshold, tauMVAIsoRawORWP, tauMVAIsoRawThreshold, tauMVAIsoWP, signSameOROpposite, mTMuMetLowThreshold, mTMuMetHighThreshold, invertedPzetaCut, pzetaThreshold, tauPtLowThreshold, tauPtHighThreshold, tauAntiMuDisc, tauAntiEleDisc, "ZZ", deepTauID, deepTauVSele, deepTauVSmu, deepTauVSjet);
                ZZIncHist.Loop();
            } // end while loop on input file list
        } // end else
    } // end if ZZInc

    return 0;
}
