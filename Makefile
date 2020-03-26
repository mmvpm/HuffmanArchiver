CXX = g++
CXXFLAGS = -O2 -Wall -Werror -Wextra -Wpedantic -std=c++11 -Iinclude
LDFLAGS =

EXE = hw_03
SRCDIR = src
TESTDIR = tests
BINDIR = obj
MAINS = obj/main.o
TESTEXE = hw_03_test

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
TESTOBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(TESTDIR)/*.cpp))

all: $(EXE)

$(TESTEXE): $(BINDIR) $(OBJECTS) $(TESTOBJECTS)
	$(CXX) $(TESTOBJECTS) $(filter-out $(MAINS), $(OBJECTS)) -o $(TESTEXE) $(LDFLAGS)

$(EXE): $(BINDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(BINDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(EXE) $(TESTEXE)

.PHONY: clean $(TESTEXE) all
