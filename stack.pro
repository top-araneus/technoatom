QT += core
QT -= gui

CONFIG += c++11

TARGET = stack
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    stack.h \
    array.h \
    exception.h \
    arraytest.h \
    array_iter.h \
    stacktest.h \
    print.h \
    bit_iter.h \
    smart_ptr.h \
    smart_ptr_test.h \
    alu.h
