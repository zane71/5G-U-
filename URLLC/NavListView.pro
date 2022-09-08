#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T23:00:13
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NavListView
TEMPLATE = app


SOURCES += main.cpp\
    frmnavlistview.cpp \
    frmnavlistviewform.cpp \
    logindialog.cpp \
    navlistview.cpp

HEADERS  += \
    logindialog.h \
    navlistview.h \
    frmnavlistview.h \
    frmnavlistviewform.h

FORMS    += \
    frmnavlistviewform.ui \
    frmnavlistview.ui \
    logindialog.ui \

RESOURCES += \
    rc.qrc
