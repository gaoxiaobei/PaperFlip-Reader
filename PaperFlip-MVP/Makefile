# Simple Makefile for Qt project

# Qt installation path - adjust as needed
QT_DIR = C:/Qt
QT_VERSION = 5.15.2
QT_COMPILER = mingw81_64

# Compiler and flags
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -fPIC
INCLUDES = -I$(QT_DIR)/$(QT_VERSION)/$(QT_COMPILER)/include
INCLUDES += -I$(QT_DIR)/$(QT_VERSION)/$(QT_COMPILER)/include/QtCore
INCLUDES += -I$(QT_DIR)/$(QT_VERSION)/$(QT_COMPILER)/include/QtWidgets
INCLUDES += -I$(QT_DIR)/$(QT_VERSION)/$(QT_COMPILER)/include/QtGui

# Qt libraries
LIBS = -L$(QT_DIR)/$(QT_VERSION)/$(QT_COMPILER)/lib
LIBS += -lQt5Core -lQt5Widgets -lQt5Gui -lmingw32

# MOC and other Qt tools
MOC = $(QT_DIR)/$(QT_VERSION)/$(QT_COMPILER)/bin/moc
RCC = $(QT_DIR)/$(QT_VERSION)/$(QT_COMPILER)/bin/rcc

# Source files
SOURCES = main.cpp MainWindow.cpp ReaderWidget.cpp EPUBManager.cpp Views/PreviewBar.cpp
HEADERS = MainWindow.h ReaderWidget.h EPUBManager.h Views/PreviewBar.h
MOC_SOURCES = moc_MainWindow.cpp moc_ReaderWidget.cpp moc_PreviewBar.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o) $(MOC_SOURCES:.cpp=.o)

# Default target
all: PaperFlip.exe

# Main executable
PaperFlip.exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

# Compile source files
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Generate MOC files
moc_%.cpp: %.h
	$(MOC) $< -o $@

# Clean build files
clean:
	del *.o moc_*.cpp PaperFlip.exe 2>nul

# Run the application
run: PaperFlip.exe
	./PaperFlip.exe

.PHONY: all clean run