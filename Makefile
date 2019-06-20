# =============================== 
# Makefile for MuTau Analysis 
# =============================== 

ROOTGLIBS     = $(shell $(HOME)/Desktop/ROOT/bin/root-config --glibs)
ROOTCFLAGS    = $(shell $(HOME)/Desktop/ROOT/bin/root-config --cflags) 

SRCDIR = Sources/
INCDIR = -IIncludes/

CXX           = g++ -std=c++11
CXXFLAGS      = -g -Wall -fPIC   	
CXXFLAGS      += $(ROOTCFLAGS) 

SOURCES = Histomutau.cc MuTauAnalyzer.cc

SRCLIST = $(addprefix $(SRCDIR), $(SOURCES))
OBJLIST = $(SRCLIST:.cc=.o)

.PHONY: all clean

all: runMuTauAnalyzer

# ===========================================================================
.cc.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCDIR)

runMuTauAnalyzer: $(OBJLIST) runMuTauAnalyzer.o 
	$(CXX) -o runMuTauAnalyzer $^ $(ROOTGLIBS)

runMuTauAnalyzer.o: runMuTauAnalyzer.cc
	$(CXX) -o $@ -c -IIncludes $< $(CXXFLAGS) $(INCDIR)

# =========================================================================== 
clean: 
	rm -f *.o Sources/*.o 
