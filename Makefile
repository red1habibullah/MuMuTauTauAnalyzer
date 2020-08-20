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

SOURCES = HistoZmumu.cc MuMuAnalyzer.cc Histomutau.cc HistoZmutau.cc MuMuTauMuTauHadAnalyzer.cc MuMuTauMuTauMuAnalyzer.cc MuMuTauMuTauEAnalyzer.cc MuMuTauETauEAnalyzer.cc MuMuTauETauHadAnalyzer.cc MuMuTauHadTauHadAnalyzer.cc lumiana.cc ArgParser.cc ConfigArg.cc FakeMuMuTauMuTauHadAnalyzer.cc FakeMuMuTauMuTauMuAnalyzer.cc FakeMuMuTauETauEAnalyzer.cc FakeMuMuTauETauHadAnalyzer.cc FakeMuMuTauHadTauHadAnalyzer.cc ZTauMuTauHadAnalyzer.cc ZMuMuAnalyzer.cc

SRCLIST = $(addprefix $(SRCDIR), $(SOURCES))
OBJLIST = $(SRCLIST:.cc=.o)

.PHONY: all clean

all: runMuMuAnalyzer runMuMuTauMuTauHadAnalyzer runMuMuTauMuTauMuAnalyzer runMuMuTauMuTauEAnalyzer runMuMuTauETauEAnalyzer runMuMuTauETauHadAnalyzer runMuMuTauHadTauHadAnalyzer runFakeMuMuTauMuTauHadAnalyzer runFakeMuMuTauMuTauMuAnalyzer runFakeMuMuTauETauEAnalyzer runFakeMuMuTauETauHadAnalyzer runFakeMuMuTauHadTauHadAnalyzer runZTauMuTauHadAnalyzer runZMuMuAnalyzer

# ===========================================================================
.cc.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCDIR)

runMuMuAnalyzer: $(OBJLIST) runMuMuAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runMuMuAnalyzer.o: runMuMuAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runMuMuTauMuTauHadAnalyzer: $(OBJLIST) runMuMuTauMuTauHadAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runMuMuTauMuTauHadAnalyzer.o: runMuMuTauMuTauHadAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runMuMuTauMuTauMuAnalyzer: $(OBJLIST) runMuMuTauMuTauMuAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runMuMuTauMuTauMuAnalyzer.o: runMuMuTauMuTauMuAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runMuMuTauMuTauEAnalyzer: $(OBJLIST) runMuMuTauMuTauEAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runMuMuTauMuTauEAnalyzer.o: runMuMuTauMuTauEAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runMuMuTauETauEAnalyzer: $(OBJLIST) runMuMuTauETauEAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runMuMuTauETauEAnalyzer.o: runMuMuTauETauEAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runMuMuTauETauHadAnalyzer: $(OBJLIST) runMuMuTauETauHadAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runMuMuTauETauHadAnalyzer.o: runMuMuTauETauHadAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runMuMuTauHadTauHadAnalyzer: $(OBJLIST) runMuMuTauHadTauHadAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runMuMuTauHadTauHadAnalyzer.o: runMuMuTauHadTauHadAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runFakeMuMuTauMuTauHadAnalyzer: $(OBJLIST) runFakeMuMuTauMuTauHadAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runFakeMuMuTauMuTauHadAnalyzer.o: runFakeMuMuTauMuTauHadAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runFakeMuMuTauMuTauMuAnalyzer: $(OBJLIST) runFakeMuMuTauMuTauMuAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runFakeMuMuTauMuTauMuAnalyzer.o: runFakeMuMuTauMuTauMuAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runFakeMuMuTauETauEAnalyzer: $(OBJLIST) runFakeMuMuTauETauEAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runFakeMuMuTauETauEAnalyzer.o: runFakeMuMuTauETauEAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runFakeMuMuTauETauHadAnalyzer: $(OBJLIST) runFakeMuMuTauETauHadAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runFakeMuMuTauETauHadAnalyzer.o: runFakeMuMuTauETauHadAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runFakeMuMuTauHadTauHadAnalyzer: $(OBJLIST) runFakeMuMuTauHadTauHadAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runFakeMuMuTauHadTauHadAnalyzer.o: runFakeMuMuTauHadTauHadAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runZTauMuTauHadAnalyzer: $(OBJLIST) runZTauMuTauHadAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runZTauMuTauHadAnalyzer.o: runZTauMuTauHadAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)

runZMuMuAnalyzer: $(OBJLIST) runZMuMuAnalyzer.o 
	$(CXX) -o $@ $^ $(ROOTGLIBS)

runZMuMuAnalyzer.o: runZMuMuAnalyzer.cc
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCDIR)
# =========================================================================== 
clean: 
	rm -f *.o Sources/*.o 
