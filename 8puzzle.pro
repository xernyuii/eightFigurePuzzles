QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 8puzzle
TEMPLATE = app


SOURCES += main.cpp\
        eightpuzzle.cpp \
    mode.cpp \
    deal.cpp \
    show.cpp

HEADERS  += eightpuzzle.h \
    head.h \
    show.h

FORMS    += eightpuzzle.ui \
    show.ui
