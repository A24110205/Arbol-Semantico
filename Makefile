CXX := /c/msys64/mingw64/bin/g++.exe

CXXFLAGS := -std=c++17 -Wall -Iinclude -IC:/msys64/mingw64/include

LDFLAGS := -LC:/msys64/mingw64/lib -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR := src
BINDIR := bin
SOURCES := $(SRCDIR)/main.cpp
TARGET := $(BINDIR)/programa.exe

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BINDIR)