QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/sblockdata.cpp \
    core/sgeneraldata.cpp \
    core/smainclass.cpp \
    gui/enteringblocks.cpp \
    gui/form2.cpp \
    gui/generaldata.cpp \
    gui/mainwindow.cpp \
    gui/renamedform.cpp \
    main.cpp \

HEADERS += \
    core/sblockdata.h \
    core/sgeneraldata.h \
    core/smainclass.h \
    gui/enteringblocks.h \
    gui/form2.h \
    gui/generaldata.h \
    gui/mainwindow.h \
    gui/renamedform.h

FORMS += \
    gui/enteringblocks.ui \
    gui/form2.ui \
    gui/generaldata.ui \
    gui/mainwindow.ui \
    gui/renamedform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
