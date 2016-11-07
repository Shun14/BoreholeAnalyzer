#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T14:38:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BoreholeAnalyzer
TEMPLATE = app

CONFIG += precompile_header debug_and_release

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER = stable.h

SOURCES += main.cpp\
        mainwindow.cpp \
    imagewidget.cpp \
    defectwidget.cpp

HEADERS  += mainwindow.h \
    imagewidget.h \
    defectwidget.h

FORMS    += mainwindow.ui \
    imagewidget.ui \
    defectwidget.ui

RESOURCES += \
    res.qrc

CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}

BUILDDIR = build

win32 {
    OBJECTS_DIR = $$BUILDDIR/obj
    MOC_DIR = $$BUILDDIR/moc
    RCC_DIR = $$BUILDDIR/qrc
    UI_DIR = $$BUILDDIR/ui
} else {
    OBJECTS_DIR = $$BUILDDIR/.obj
    MOC_DIR = $$BUILDDIR/.moc
    RCC_DIR = $$BUILDDIR/.qrc
    UI_DIR = $$BUILDDIR/.ui
}

DISTFILES += \
    doc/README.MD
