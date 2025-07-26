# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

# Target executable
TARGET = rbtree

# Source files
SRC = main.cpp

# Header file
DEPS = RedBlackTree.h

# Build rule
$(TARGET): $(SRC) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean rule
clean:
	rm -f $(TARGET)

