#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T11:17:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = caseManagement
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    legaldoc.cpp \
    baseinfo.cpp \
    anqinginfodialog.cpp

HEADERS  += mainwindow.h \
    lawitem.h \
    legaldoc.h \
    baseinfo.h \
    anqinginfodialog.h

FORMS    += mainwindow.ui \
    baseinfo.ui \
    anqinginfodialog.ui
CONFIG   += qaxcontainer

RESOURCES += \
    resoures.qrc
RC_FILE = myapp.rc
QT      += axcontainer
