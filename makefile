CXX=g++
CXXFLAGS=-Wall
LDFLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -latomic
MAIN=$(wildcard $(CURDIR)/src/main.cpp)
BIN=$(CURDIR)/game.bin

all: build

build:
	$(CXX) -o $(BIN) $(CXXFLAGS) $(MAIN) $(LDFLAGS) 
run: $(BIN)
	$(BIN)

exec: all run
