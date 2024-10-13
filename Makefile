# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Target executable
TARGET = program

# Object files
OBJECTS = Exercise.o

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile Exercise.cpp
Exercise.o: Exercise.cpp
	$(CXX) $(CXXFLAGS) -c Exercise.cpp

# Clean up object files and executable
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean
