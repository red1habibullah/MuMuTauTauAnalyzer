# =============================== 
# Makefile for MuTau Analysis 
# =============================== 

ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)
ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)

SRCDIR = Sources/
INCDIR = -IIncludes/

CXX           = g++ -std=c++11
CXXFLAGS      = -g -Wall -fPIC   	
CXXFLAGS      += $(ROOTCFLAGS) 

SOURCES = HistoZmumu.cc MuMuAnalyzer.cc Histomutau.cc MuTauAnalyzer.cc lumiana.cc ArgParser.cc ConfigArg.cc TreeMuTau.cc MuTauFlatTreelizer.cc

SRCLIST = $(addprefix $(SRCDIR), $(SOURCES))
OBJLIST = $(SRCLIST:.cc=.o)

.PHONY: all clean

all: runMuMuAnalyzer runMuTauAnalyzer runMuTauFlatTreelizer

# ===========================================================================
.cc.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCDIR)

runMuMuAnalyzer: $(OBJLIST) runMuMuAnalyzer.o 
	$(CXX) -o runMuMuAnalyzer $^ $(ROOTGLIBS)

runMuMuAnalyzer.o: runMuMuAnalyzer.cc
	$(CXX) -o $@ -c -IIncludes $< $(CXXFLAGS) $(INCDIR)

runMuTauAnalyzer: $(OBJLIST) runMuTauAnalyzer.o 
	$(CXX) -o runMuTauAnalyzer $^ $(ROOTGLIBS)

runMuTauAnalyzer.o: runMuTauAnalyzer.cc
	$(CXX) -o $@ -c -IIncludes $< $(CXXFLAGS) $(INCDIR)

runMuTauFlatTreelizer: $(OBJLIST) runMuTauFlatTreelizer.o 
	$(CXX) -o runMuTauFlatTreelizer $^ $(ROOTGLIBS)

runMuTauFlatTreelizer.o: runMuTauFlatTreelizer.cc
	$(CXX) -o $@ -c -IIncludes $< $(CXXFLAGS) $(INCDIR)

# =========================================================================== 
clean: 
	rm -f *.o Sources/*.o 
