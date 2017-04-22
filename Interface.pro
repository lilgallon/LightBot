TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Appli.cpp \
    Button.cpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
LIBS           += -lsfml-graphics -lsfml-window -lsfml-system

HEADERS += \
    Appli.h \
    Button.h
