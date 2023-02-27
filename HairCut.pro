#-------------------------------------------------
#
# Project created by QtCreator 2023-02-11T16:03:06
#
#-------------------------------------------------

QT       += core gui
CONFIG += resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HairCut
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    createuser.cpp \
    loginin.cpp \
    mybtn.cpp \
    temp_customer_consume.cpp \
    vip.cpp \
    startpage.cpp \
    show_temp_customer_consume_sum.cpp \
    add_vip.cpp \
    modify_vip.cpp \
    consume_vip.cpp \
    charged_vip_record.cpp \
    consume_vip_record.cpp

HEADERS += \
        mainwindow.h \
    createuser.h \
    loginin.h \
    mybtn.h \
    temp_customer_consume.h \
    ui_createuser.h \
    ui_loginin.h \
    vip.h \
    startpage.h \
    show_temp_customer_consume_sum.h \
    add_vip.h \
    modify_vip.h \
    consume_vip.h \
    charged_vip_record.h \
    consume_vip_record.h

FORMS += \
        mainwindow.ui \
    createuser.ui \
    loginin.ui \
    temp_customer_consume.ui \
    startpage.ui \
    show_temp_customer_consume_sum.ui \
    add_vip.ui \
    modify_vip.ui \
    consume_vip.ui \
    charged_vip_record.ui \
    consume_vip_record.ui

RESOURCES += \
    res.qrc \
    image.qrc
