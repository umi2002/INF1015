# Compiler options
CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++20
INCLUDES = -I/usr/include/qt -I./cppitertools
OBJECTS=$(SOURCES:.cpp=.o) $(MOC_SOURCES:.cpp=.o)

# Linker options
LDLIBS = -lQt5Core -lQt5Gui -lQt5Widgets

# Source files
SRCS = $(wildcard *.cpp) $(wildcard pieces/*.cpp)
MOC_HEADERS = maingui.hpp
MOC_SOURCES=$(MOC_HEADERS:.hpp=.moc.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o) $(MOC_SOURCES:.cpp=.o)

# Target executable
TARGET = main

# Build rule
all: $(TARGET)
	@echo "Build complete."
	rm -f $(OBJS) ./pieces/*.o

$(TARGET): $(OBJS)
	$(CXX) $^ $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.moc.cpp: %.hpp
	moc $(MOC) $(INCLUDES) $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET) ./pieces/*.o
