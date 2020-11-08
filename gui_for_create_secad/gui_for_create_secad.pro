QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enteringblocks.cpp \
    form2.cpp \
    generaldata.cpp \
    main.cpp \
    mainwindow.cpp \
    renamedform.cpp

HEADERS += \
    enteringblocks.h \
    form2.h \
    generaldata.h \
    mainwindow.h \
    renamedform.h

FORMS += \
    enteringblocks.ui \
    form2.ui \
    generaldata.ui \
    mainwindow.ui \
    renamedform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
