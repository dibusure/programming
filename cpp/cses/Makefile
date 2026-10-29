# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2

# Output directory
BIN_DIR = ./bin

# Default target to handle arbitrary 'make <num>' calls
.PHONY: default
default:
	@echo "Please specify a target number, e.g., 'make 1'"

# Pattern rule to match natural number targets
%:
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $@.cpp -o $(BIN_DIR)/$@