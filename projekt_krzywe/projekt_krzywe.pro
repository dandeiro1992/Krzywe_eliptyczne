TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgmp
SOURCES += main.cpp \
    funkcje.cpp \
    alice.cpp \
    bob.cpp

HEADERS += \
    funkcje.h
