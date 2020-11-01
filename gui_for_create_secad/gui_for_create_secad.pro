QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form1.cpp \
    form2.cpp \
    form3.cpp \
<<<<<<< Updated upstream
    form4.cpp \
=======
    gofuckyourself.cpp \
>>>>>>> Stashed changes
    main.cpp \
    mainwindow.cpp

HEADERS += \
    form1.h \
    form2.h \
    form3.h \
<<<<<<< Updated upstream
    form4.h \
=======
    gofuckyourself.h \
>>>>>>> Stashed changes
    mainwindow.h

FORMS += \
    form1.ui \
    form2.ui \
    form3.ui \
<<<<<<< Updated upstream
    form4.ui \
=======
    gofuckyourself.ui \
>>>>>>> Stashed changes
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
