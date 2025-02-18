#
#   Copyright (c) 2025 - Matt C
#    All rights reserved.
#

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
SRC = main.cpp deck.cpp hand.cpp

# Header files
HEADERS = header.h hand.h deck.h

# Output file
TARGET = blackjack

# Build
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)

# Clean
clean:
	rm -rf $(TARGET)