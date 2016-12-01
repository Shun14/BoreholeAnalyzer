#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T14:38:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BoreholeAnalyzer
TEMPLATE = app

CONFIG += precompile_header debug_and_release

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER = stable.h

SOURCES +=  main.cpp\
            mainwindow.cpp \
            imagewidget.cpp \
            defectwidget.cpp \
            GraphicsView.cpp \
            MyCommand.cpp \
            OpenGLWidget.cpp \
            GraphicsTextItem.cpp \
            DbHandler.cpp \
            GraphicsScene.cpp \
    TextDialog.cpp \
    GraphicsLineItem.cpp \
    GraphicsSettings.cpp \
    GraphicsAngleItem.cpp \
    GraphicsRectItem.cpp \
    GraphicsAnyshape.cpp


HEADERS  += mainwindow.h \
            imagewidget.h \
            defectwidget.h \
            GraphicsView.h \
            MyCommand.h \
            OpenGLWidget.h \
            GraphicsTextItem.h \
            DbHandler.h \
            GraphicsScene.h \
    TextDialog.h \
    GraphicsLineItem.h \
    GraphicsSettings.h \
    GraphicsAngleItem.h \
    GraphicsRectItem.h \
    GraphicsAnyshape.h


FORMS    += mainwindow.ui \
            imagewidget.ui \
            defectwidget.ui

RESOURCES += \
    res.qrc

win32 {
#    QT += axcontainer

#    HEADERS += qword.h  qexcel.h
#    SOURCES += qword.cpp qexcel.cpp
}

DISTFILES += \
    doc/README.MD
