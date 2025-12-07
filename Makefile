# PARAMETERS
NCITIES = 8




# MAKEFILE CODE
CXXFLAGS := -Wall -pedantic

CXX  := g++
SRC  := main.cpp
BIN  := $(SRC:%.cpp=bin/%.x)
LIBS := Bruteforce.cpp MST.cpp

all: ${BIN}


${BIN}: $(SRC:%=src/%) $(LIBS:%=src/%) | bin
	$(CXX) $(CXXFLAGS) $< -o $@

run: ${BIN}
	./$< ${NCITIES} 1
#	python3 graph.py

bin:
	mkdir -p bin