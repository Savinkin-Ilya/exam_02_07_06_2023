QT += network testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_test.cpp \
    ../server/mytcpserver-ex.cpp

HEADERS += \
    ../server/mytcpserver-ex.h
