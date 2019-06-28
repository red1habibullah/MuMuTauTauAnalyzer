#ifndef lumiana_h
#define lumiana_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
// Header file for the classes stored in the TTree if any.

class lumiana {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           lumi;
   Int_t           nevents;
   Float_t         summedWeights;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_nevents;   //!
   TBranch        *b_summedWeights;   //!

   TString fileName;
   lumiana(TString fileName_);
   virtual ~lumiana();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init();
   virtual float    Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   bool isData;
};

#endif

#ifdef lumiana_cxx
lumiana::lumiana(TString fileName_) : fileName(fileName_) 
{
   TChain *chain = new TChain("","");
   TString treePath = fileName + ".root/lumiTree/LumiTree";
   chain->Add(treePath);
   fChain = chain;
   Init();
   isData = ((fileName.Index("Data") >= 0) || (fileName.Index("data") >= 0));
}

lumiana::~lumiana()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t lumiana::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t lumiana::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void lumiana::Init()
{
   run = -999.;
   lumi = -999.;
   nevents = 0;
   summedWeights = 0;
   // Set branch addresses and branch pointers
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("nevents", &nevents, &b_nevents);
   fChain->SetBranchAddress("summedWeights", &summedWeights, &b_summedWeights);
   Notify();
}

Bool_t lumiana::Notify()
{
   return kTRUE;
}

void lumiana::Show(Long64_t entry)
{
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t lumiana::Cut(Long64_t entry)
{
   return 1;
}
#endif // #ifdef lumiana_cxx
