#-------------------------------------------------
#
# Project created by QtCreator 2022-08-03T15:27:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

TARGET = test_pop_keyboard
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    FullKeyboard.cpp \
    NumberKeyboard.cpp \
    HanCharacter.cpp

HEADERS  += MainWindow.h \
    FullKeyboard.h \
    NumberKeyboard.h \
    HanCharacter.h

FORMS    += MainWindow.ui
