#include "MuTauAnalyzer.h"
#include "lumiana.h"

int main()
{

    // ----- This two variables to be used for MC reweighting -----
    //double lumi = 41.9; // fb-1
    float summedWeights = 0;

    //------------------------- data histograms production -------------------

    // ------------------------ MC histogram production ------------------
    lumiana HAA5Lumi("MuMuTauTauTreelization");
    summedWeights = HAA5Lumi.Loop();
    MuTauAnalyzer HAA5Hist("MuMuTauTauTreelization", 1, 1);
    HAA5Hist.Loop();

    return 0;
}
