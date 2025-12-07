# PARAMETERS
NCITIES = 8




# MAKEFILE CODE
CXXFLAGS := -Wall -pedantic

CXX := g++
SRC := main.cpp
BIN := bin/$(SRC:.cpp=.x)

all: ${BIN}


${BIN}: ${SRC} Bruteforce.cpp MST.cpp | bin
	$(CXX) $(CXXFLAGS) $< -o $@

run: ${BIN}
	./$< ${NCITIES} 1
	python3 graph.py

bin:
	mkdir -p bin