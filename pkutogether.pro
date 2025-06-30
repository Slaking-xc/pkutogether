QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actdetailwindow.cpp \
    activitys.cpp \
    addfrienddialog.cpp \
    choosehobby.cpp \
    frienddetaildialog.cpp \
    login.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    overall.cpp \
    person.cpp \
    publishwindow.cpp \
    saveonexit.cpp \
    social.cpp \
    user.cpp

HEADERS += \
    ../build-frontendTrial2-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/ui_publishwindow.h\
    actdetailwindow.h \
    activitys.h \
    addfrienddialog.h \
    choosehobby.h \
    frienddetaildialog.h \
    login.h \
    mainmenu.h \
    mainwindow.h \
    overall.h \
    person.h \
    publishwindow.h \
    saveonexit.h \
    social.h \
    user.h

FORMS += \
    actdetailwindow.ui \
    addfrienddialog.ui \
    choosehobby.ui \
    frienddetaildialog.ui \
    login.ui \
    mainmenu.ui \
    mainwindow.ui \
    publishwindow.ui \
    social.ui \
    subwindow1.ui \
    user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc \
    qss.qrc
