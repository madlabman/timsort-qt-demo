#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T14:14:55
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kursovaya
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    theory.cpp \
    test.cpp \
    demo.cpp

HEADERS  += mainwindow.h \
    theory.h \
    test.h \
    demo.h \
    sorts.h

FORMS    += mainwindow.ui \
    theory.ui \
    test.ui \
    demo.ui

DISTFILES +=

QMAKE_CXXFLAGS += -std=c++0x

