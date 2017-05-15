TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Button.cpp \
    Utils.cpp \
    Theme.cpp \
    Grid.cpp \
    Cell.cpp \
    Interface.cpp \
    Application.cpp \
    ProgramBox.cpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
LIBS           += -lsfml-graphics -lsfml-window -lsfml-system

HEADERS += \
    Button.h \
    Utils.h \
    Theme.h \
    Grid.h \
    Cell.h \
    Interface.h \
    Application.h \
    ProgramBox.h
