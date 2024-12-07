
INCLUDES := -Iinclude
SRCDIR := src
OBJDIR := .obj
BINDIR := bin


CXX := g++
CXXFLAGS := -Wall -O2 -std=c++17 -shared -fPIC -DDIVISION_EXPORT -DWIN32 -D_WIN32 -g 
LDFLAGS := -shared -Wl,--out-implib,$(BINDIR)/libdivision.a
LIBS := -lgdi32 -luser32


# Recursively find all cpp files in source directory
SOURCES := $(shell find $(SRCDIR) -name "*.cpp")
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

$(info SOURCES: $(SOURCES))
$(info OBJECTS: $(OBJECTS))

# Main target
all: setup $(BINDIR)/libdivision.dll

# Create necessary directories
setup:
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BINDIR)

# Build the DLL
$(BINDIR)/libdivision.dll: $(OBJECTS)
	@echo "Building Division Engine DLL..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

# Compile object files (with subdirectory support)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all setup clean
