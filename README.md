# MuMuTauTauAnalyzer

This framework is used to analyze the output of "MuMuTauTauTreelizer". It is written in standard C++/ROOT format, as is independent from CMSSW. 
It reads the vector trees of different objects (eg. muons, electrons, taus, and jets), through making customized selection scripts, and outputs 
of variable histograms and/or flat trees.

# Introduction for running the analyzer

First you must make sure you have the ROOT library included in your local environment. 

$ git clone https://github.com/Fengwangdong/MuMuTauTauAnalyzer.git

$ cd MuMuTauTauAnalyzer

$ make clean

$ make # compile the C++ functions

$ cp example.cfg mumutautau.cfg

One needs the "mumutautau.cfg" file to customize the default input parameters before running the analyzer. In addition, these parameters can be 
also customized in the command line for instance when executing the analyzer, for instance:

# Run the diMuon Analyzer:

$ ./runMuMuAnalyzer doWhat=DYJets maxEvents=1000 ###### for producing histograms of the dimuon channel (control region)

# Run the diMuon + ditau (tau_mu + tau_mu) Analyzer:

$ ./runMuMuTauMuTauMuAnalyzer doWhat=H125AA5 maxEvents=2000 ###### for producing histograms of the tau_mu + tau_mu channel

$ ./runFakeMuMuTauMuTauMuAnalyzer doWhat=Data maxEvents=3000 ##### for producing the histograms of dimuon + tau_mu + tau_mu channel (control region for jet faking muon study) 

# Run the diMuon + ditau (tau_mu + tau_e) Analyzer:

$ ./runMuMuTauMuTauEAnalyzer doWhat=H125AA5 maxEvents=2000 ###### for producing histograms of the tau_mu + tau_e channel

$ ./runFakeMuMuTauMuTauEAnalyzer doWhat=Data maxEvents=3000 ##### for producing the histograms of dimuon + tau_mu + tau_e channel (control region for jet faking muon study) 

# Run the diMuon + ditau (tau_e + tau_e) Analyzer:

$ ./runMuMuTauETauEAnalyzer doWhat=H125AA5 maxEvents=2000 ###### for producing histograms of the tau_e + tau_e channel

$ ./runFakeMuMuTauETauEAnalyzer doWhat=Data maxEvents=3000 ##### for producing the histograms of dimuon + tau_e + tau_e channel (control region for jet faking muon study) 

# Run the diMuon + ditau (tau_mu + tau_h) Analyzer:

$ ./runMuMuTauMuTauHadAnalyzer doWhat=H125AA5 maxEvents=2000 ###### for producing histograms of the tau_mu + tau_h channel

$ ./runFakeMuMuTauMuTauHadAnalyzer doWhat=Data maxEvents=3000 ##### for producing the histograms of dimuon + tau_mu + tau_h channel (control region for jet faking tau study) 

$ ./runMuTauFlatTreelizer doWhat=Data maxEvents=3000 ###### for producing the flat trees of the tau_mu + tau_h channel

# Run the diMuon + ditau (tau_e + tau_h) Analyzer:

$ ./runMuMuTauETauHadAnalyzer doWhat=H125AA5 maxEvents=2000 ###### for producing histograms of the tau_e + tau_h channel

$ ./runFakeMuMuTauETauHadAnalyzer doWhat=Data maxEvents=3000 ##### for producing the histograms of dimuon + tau_e + tau_h channel (control region for jet faking muon study) 

# Run the diMuon + ditau (tau_h + tau_h) Analyzer:

$ ./runMuMuTauHadTauHadAnalyzer doWhat=H125AA5 maxEvents=2000 ###### for producing histograms of the tau_h + tau_h channel

$ ./runFakeMuMuTauHadTauHadAnalyzer doWhat=Data maxEvents=3000 ##### for producing the histograms of dimuon + tau_h + tau_h channel (control region for jet faking muon study) 

###############################################################

NOTE: If the parameters are customized in the command line, their default values in "mumutautau.cfg" will be ignored.

The ''FlatTreelizer'' produces a flat tree containing the variables that will be used for subsequent RooFit/combine steps.
