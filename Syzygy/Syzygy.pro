QT       += core gui sql
QT       +=xml
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutprogramform.cpp \
    algorithms.cpp \
    clock.cpp \
    developersform.cpp \
    main.cpp \
    mainwindow.cpp \
    managesession.cpp \
    planet.cpp \
    planetinfodata.cpp \
    planetinfoform.cpp \
    setplanetimage.cpp \
    syzygyexception.cpp

HEADERS += \
    aboutprogramform.h \
    algorithms.h \
    clock.h \
    developersform.h \
    mainwindow.h \
    managesession.h \
    planet.h \
    planetinfodata.h \
    planetinfoform.h \
    setplanetimage.h \
    syzygyexception.h

FORMS += \
    aboutprogramform.ui \
    developersform.ui \
    mainwindow.ui \
    planetinfoform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
