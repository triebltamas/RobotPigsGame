QT       += testlib

QT       -= gui

TARGET = robotpigsmodeltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
        player.cpp \
        robotpigsmodel.cpp \
        robotpigsmodeltest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    player.h \
    robotpigsdataaccess.h \
    robotpigsdataaccessmock.h \
    robotpigsmodel.h
