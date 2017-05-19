QT += core
QT -= gui

CONFIG += c++11

TARGET = ALU
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    alu.h \
    alucommands.h
