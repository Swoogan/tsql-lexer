#-------------------------------------------------
#
# Project created by QtCreator 2014-11-12T20:36:35
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = Lexer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    state.cpp \
    lexer.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    state.h \
    lexer.h \
    itemtype.h \
    item.h

OTHER_FILES += \
    todo.md
