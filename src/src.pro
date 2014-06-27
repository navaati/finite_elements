QT       -= gui

TARGET = finite_elem
TEMPLATE = lib
CONFIG += staticlib c++11

HEADERS += finitediff.h \
    thomas_algo.h \
    const_iterator.h \
    sampler_iterator.h \
    integrator.h
