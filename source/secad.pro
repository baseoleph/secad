# Ship Exterior CAD
# Copyright (C) 2020 baseoleph@gmail.com,
#					  github.com/RoninHikami

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    core/salgorithm.cpp \
    core/sblockdata.cpp \
    core/sgeneraldata.cpp \
    core/sm_algorithms.cpp \
    core/smainclass.cpp \
    core/typesofoptimizevar.cpp \
    gui/enteringblocks.cpp \
    gui/generaldata.cpp \
    gui/jsonparserclass.cpp \
    gui/mainwindow.cpp \
    gui/optimizewidget.cpp \
    gui/projectmanager.cpp \
    gui/resultswidget.cpp \
    main.cpp

HEADERS += \
    core/salgorithm.h \
    core/sblockdata.h \
    core/sconstants.h \
    core/sgeneraldata.h \
    core/sm_algorithms.h \
    core/smainclass.h \
    core/typesofoptimizevar.h \
    gui/enteringblocks.h \
    gui/generaldata.h \
    gui/jsonparserclass.h \
    gui/mainwindow.h \
    gui/optimizewidget.h \
    gui/projectmanager.h \
    gui/resultswidget.h

FORMS += \
    gui/enteringblocks.ui \
    gui/generaldata.ui \
    gui/mainwindow.ui \
    gui/optimizewidget.ui \
    gui/projectmanager.ui \
    gui/resultswidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
