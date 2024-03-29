QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common.cpp \
    lab2.cpp \
    lab3.cpp \
    qcustomplot/qcustomplot.cpp \
    lab1.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    common.h \
    lab2.h \
    lab3.h \
    lab3diophantus.h \
    lab3fermat.h \
    lab3perceptron.h \
    qcustomplot/qcustomplot.h \
    lab1.h \
    mainwindow.h

FORMS += \
    lab1.ui \
    lab2.ui \
    lab3.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
