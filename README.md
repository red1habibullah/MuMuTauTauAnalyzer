# MuMuTauTauAnalyzer

This framework is used to analyze the output of "MuMuTauTauTreelizer". It is written in standard C++/ROOT format, so is independent from CMSSW. 
It reads the vector trees of different objects (eg. muons, electrons, taus, and jets), through making customized selection scripts, and outputs 
of variable histograms and/or flat trees (latter TBD).

# Introduction for running the analyzer

First you must make sure you have the ROOT library included in your local environment. 

$ git clone https://github.com/Fengwangdong/MuMuTauTauTreeMaker.git

$ cd MuMuTauTauAnalyzer

$ make clean

$ make # compile the C++ functions

$ ./runMuTauAnalyzer 
