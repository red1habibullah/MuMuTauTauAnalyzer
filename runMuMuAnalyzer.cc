#include "MuMuAnalyzer.h"
#include "lumiana.h"

int main()
{

    // ----- This two variables to be used for MC reweighting -----
    //double lumi = 41.9; // fb-1
    float summedWeights = 0;

    //------------------------- data histograms production -------------------

    // ------------------------ MC histogram production ------------------
    lumiana DYJetsLumi("MuMuTreelization");
    summedWeights = DYJetsLumi.Loop();
    MuMuAnalyzer DYJetsHist("MuMuTreelization", 1, 1);
    DYJetsHist.Loop();

    return 0;
}
