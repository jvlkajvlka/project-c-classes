#-------------------------------------------------
#
# Project created by QtCreator 2019-05-28T09:21:08
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Paint
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        paintingplace.cpp \
        painttests.cpp

HEADERS += \
        mainwindow.h \
        paintingplace.h

FORMS += \
        mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_FILE = PaintIcon.rc

############ external libraries:
#win32:INCLUDEPATH += libs/boost_1_70_0
#win32:INCLUDEPATH += libs/gtest


#win32:LIBS += -L"$$PWD/libs/boost_1_70_0/stage/lib"
#win32:LIBS += -lboost_filesystem-mgw73-mt-x64-1_70 -lboost_system-mgw73-mt-d-x64-1_70 -lboost_program_options-mgw73-mt-d-x64-1_70
#unix:LIBS += -lboost_filesystem -lboost_system -lboost_program_options


############ libraries for tests:
#win32:LIBS += -L"$$PWD/libs/gtest/lib"
#LIBS += -lgtest
