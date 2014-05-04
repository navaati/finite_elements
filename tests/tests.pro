QT       += testlib
QT       -= gui

TARGET = testfinitediff
CONFIG   += console testcase c++11
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

SOURCES += testfinitediff.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
