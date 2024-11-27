CC := gcc
CXX := g++
CXXFLAGS := -Wall -O2 -std=c++17 -shared -fPIC
INCLUDES := -Iinclude
SRCDIR := src
OBJDIR := .obj
BINDIR := bin

# Find all cpp files in source directory
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Main target
all: setup $(BINDIR)/Division.dll

# Create necessary directories
setup:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

# Build the DLL
$(BINDIR)/Division.dll: $(OBJECTS)
	@echo "Building Division Engine DLL..."
	$(CXX) $(CXXFLAGS) -o $@ $^ -Wl,--out-implib,$(BINDIR)/libDivision.a

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)/*

.PHONY: all setup clean