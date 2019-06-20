#include "MuTauAnalyzer.h"

int main()
{

    //------------------------- data histograms production -------------------

    MuTauAnalyzer DataHist("MuMuTauTauTreelization", 1, 1);
    DataHist.Loop();

    return 0;
}
