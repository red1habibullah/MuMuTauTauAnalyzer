# MuMuTauTauAnalyzer

This framework is used to analyze the output of "MuMuTauTauTreelizer". It is written in standard C++/ROOT format, as is independent from CMSSW. 
It reads the vector trees of different objects (eg. muons, electrons, taus, and jets), through making customized selection scripts, and outputs 
of variable histograms and/or flat trees (latter TBD).

# Introduction for running the analyzer

First you must make sure you have the ROOT library included in your local environment. 

$ git clone https://github.com/Fengwangdong/MuMuTauTauAnalyzer.git

$ cd MuMuTauTauAnalyzer

$ make clean

$ make # compile the C++ functions

$ cp example.cfg mumutautau.cfg

One needs the "mumutautau.cfg" file to customize the default input parameters before running the analyzer. In addition, these parameters can be 
also customized in the command line for instance when executing the analyzer:

$ ./runMuMuAnalyzer doWhat=DYJets maxEvents=1000 ###### for analyzing the dimuon channel (control region)

$ ./runMuTauAnalyzer doWhat=H125AA5 maxEvents=2000 ###### for analyzing the tau_mu + tau_had channel

NOTE: If the parameters are customized in the command line, their default values in "mumutautau.cfg" will be ignored.
