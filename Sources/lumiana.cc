#define lumiana_cxx
#include "lumiana.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;
float lumiana::Loop()
{
   if (fChain == 0) return 1;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;

   Float_t WeightSum = 0;

   for (Long64_t jentry=0; jentry<nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   
      nbytes += nb;
      WeightSum += summedWeights;
      // if (Cut(ientry) < 0) continue;
   }

   cout << "Summation of weights: " << WeightSum << endl;
   return WeightSum;
}
