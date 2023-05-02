QT       += core gui sql axcontainer printsupport network serialport multimedia multimediawidgets charts

QT       += core gui sql
QT       += core gui charts
QT       += core gui multimedia
QT       += widgets charts
QT += axcontainer
QT += printsupport
QT       += core gui sql network multimedia multimediawidgets charts printsupport widgets axcontainer

QT       += core gui
QT       += sql
QT       += multimedia

QT       += multimediawidgets charts printsupport widgets axcontainer network
QT       +=network
QT       += core gui  serialport
QT += widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = DOCTOR_WHEEL

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
    DuMessengerServer.cpp \
    DuMessengerSocket.cpp \
    ardBarriere.cpp \
    ardPorte.cpp \
    calendrier.cpp \
    captchabox.cpp \
    chatboxconnectiondialog.cpp \
    connection.cpp \
    employee.cpp \
    employees_statistiques.cpp \
    equipement.cpp \
    exportexcelobject.cpp \
    main.cpp \
    mainwindow.cpp \
    notifications.cpp \
    piste.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    reservation.cpp \
    smtp.cpp \
    vehicule.cpp \
    visite.cpp \
    widget.cpp

HEADERS += \
    DuMessengerServer.h \
    DuMessengerSocket.h \
    ardBarriere.h \
    ardPorte.h \
    calendrier.h \
    captchabox.h \
    chatboxconnectiondialog.h \
    connection.h \
    employee.h \
    employees_statistiques.h \
    equipement.h \
    exportexcelobject.h \
    mainwindow.h \
    notifications.h \
    piste.h \
    qcustomplot.h \
    qrcode.h \
    reservation.h \
    smtp.h \
    vehicule.h \
    visite.h \
    webaxwidget.h \
    widget.h

FORMS += \
    chatboxconnectiondialog.ui \
    employees_statistiques.ui \
    mainwindow.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    buttons/pause.png \
    buttons/play.png \
    buttons/plus.png \
    buttons/skip-next.png \
    buttons/skip-previous.png \
    buttons/stop.png \
    captchabox.png \
    car.png \
    chart.png

RESOURCES += \
    images.qrc
