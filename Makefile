# PARAMETERS
NCITIES = 8




# MAKEFILE CODE
CXXFLAGS := -Wall -pedantic

CXX  := g++
SRC  := main.cpp
BIN  := bin/$(SRC:.cpp=.x)
LIBS := Bruteforce.cpp MST.cpp

all: ${BIN}


${BIN}: $(:SRC=src/) $(:LIBS=src) | bin
	$(CXX) $(CXXFLAGS) $< -o $@

run: ${BIN}
	./$< ${NCITIES} 1
	python3 graph.py

bin:
	mkdir -p bin