QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/sblockdata.cpp \
    core/varclasses/sconstantvar.cpp \
    core/varclasses/scontinuousvar.cpp \
    core/varclasses/sdiscretevar.cpp \
    core/sgeneraldata.cpp \
    core/smainclass.cpp \
    core/svarparent.cpp \
    gui/enteringblocks.cpp \
    gui/generaldata.cpp \
    gui/generaldatapainter.cpp \
    gui/mainwindow.cpp \
    gui/projectmanager.cpp \
    gui/renamedform.cpp \
    main.cpp \

HEADERS += \
    core/sblockdata.h \
    core/varclasses/sconstantvar.h \
    core/varclasses/scontinuousvar.h \
    core/varclasses/sdiscretevar.h \
    core/sgeneraldata.h \
    core/smainclass.h \
    core/svarparent.h \
    gui/enteringblocks.h \
    gui/generaldata.h \
    gui/generaldatapainter.h \
    gui/mainwindow.h \
    gui/projectmanager.h \
    gui/renamedform.h

FORMS += \
    gui/enteringblocks.ui \
    gui/generaldata.ui \
    gui/generaldatapainter.ui \
    gui/mainwindow.ui \
    gui/projectmanager.ui \
    gui/renamedform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
