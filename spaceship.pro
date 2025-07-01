QT -= core
QT -= gui

CONFIG += c++2b

TARGET = my_tetris

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$_PRO_FILE_PWD_"/thirdparty/PDCurses"
win32:LIBS += -L$$_PRO_FILE_PWD_"/thirdparty/PDCurses/win32" -lpdcurses
unix:LIBS += -L$$_PRO_FILE_PWD_"/thirdparty/PDCurses/x11" -lpdcurses

SOURCES += main.cpp
