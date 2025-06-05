CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Iinclude/external -O2

OBJDIR = build
SRCDIR = src
EXTERNALDIR = include/external

TARGET = knotc

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
EXTERNAL_SOURCES := $(EXTERNALDIR)/pbPlots.cpp $(EXTERNALDIR)/supportLib.cpp

OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
EXTERNAL_OBJECTS := $(patsubst $(EXTERNALDIR)/%.cpp, $(OBJDIR)/%.o, $(EXTERNAL_SOURCES))

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(OBJDIR) mkdir $(OBJDIR)
    RMDIR = rmdir /s /q
    RMFILE = del /q
else
    MKDIR = mkdir -p $(OBJDIR)
    RMDIR = rm -rf
    RMFILE = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJECTS) $(EXTERNAL_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(EXTERNALDIR)/%.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RMDIR) $(OBJDIR)
	-$(RMFILE) $(TARGET)

.PHONY: all clean
