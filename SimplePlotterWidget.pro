#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T16:54:44
#
#-------------------------------------------------

QT       += core gui
QT += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimplePlotterWidget
TEMPLATE = app
CONFIG += c++11
#QMAKE_CXXFLAGS += -O3


SOURCES += main.cpp \
    simpleplotterview.cpp \
    simple2dplot.cpp \
    simpleplotterexception.cpp \
    lepton/src/CompiledExpression.cpp \
    lepton/src/ExpressionProgram.cpp \
    lepton/src/ExpressionTreeNode.cpp \
    lepton/src/Operation.cpp \
    lepton/src/ParsedExpression.cpp \
    lepton/src/Parser.cpp

HEADERS  += \
    simpleplotterview.h \
    simple2dplot.h \
    simpleplotterexception.h \
    lepton/include/lepton/CompiledExpression.h \
    lepton/include/lepton/CustomFunction.h \
    lepton/include/lepton/Exception.h \
    lepton/include/lepton/ExpressionProgram.h \
    lepton/include/lepton/ExpressionTreeNode.h \
    lepton/include/lepton/Operation.h \
    lepton/include/lepton/ParsedExpression.h \
    lepton/include/lepton/Parser.h \
    lepton/include/lepton/windowsIncludes.h \
    lepton/include/Lepton.h \
    lepton/src/MSVC_erfc.h
