#-------------------------------------------------
#
# Project created by QtCreator 2017-08-31T12:20:53
#
#-------------------------------------------------

QT       += core gui sql
QT += testlib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerDataBase
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dbmanager.cpp \
    loginmanager.cpp \
    logregdialog.cpp \
    clickablelabel.cpp

HEADERS += \
        mainwindow.h \
    dbmanager.h \
    loginmanager.h \
    logregdialog.h \
    clickablelabel.h

FORMS += \
        mainwindow.ui \
    logregdialog.ui

#INCLUDEPATH += $$PWD/boost_1_64_0/include
#DEPENDPATH += $$PWD/boost_1_64_0/include

#unix:!macx: LIBS += -L$$PWD/boost_1_64_0/lib/ -lboost_system -lboost_thread -lboost_serialization -lboost_filesystem



#LIBS += -lcrypto -lssl

RESOURCES += \
    resources.qrc


