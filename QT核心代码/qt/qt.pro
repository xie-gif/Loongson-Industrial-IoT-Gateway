QT       += core gui
QT       += serialport
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chke.cpp \
    main.cpp \
    mainwindow.cpp \
    widg.cpp

HEADERS += \
    chke.h \
    mainwindow.h \
    widg.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../Desktop/png/Qtbarc.qrc

DISTFILES += \
    ../../Desktop/aec/R-C.png \
    ../../Desktop/aec/g.png \
    ../../Desktop/aec/x.png
