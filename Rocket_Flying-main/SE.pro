QT       += core gui printsupport
QT       += sql
QT       += core gui widgets
CONFIG += c++17
CONFIG += staticlib c++11
QMAKE_CXXFLAGS += -Wa,-mbig-obj
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DyEq.cpp \
    airforce.cpp \
    alpha.cpp \
    atmosphere.cpp \
    dycoef.cpp \
    dynamic_mass.cpp \
    eastwind.cpp \
    equations.cpp \
    focus.cpp \
    main.cpp \
    mainwindow.cpp \
    mass.cpp \
    pitch.cpp \
    qcustomplot.cpp

HEADERS += \
    airforce.h \
    alpha.h \
    atmosphere.h \
    dycoef.h \
    dynamic_mass.h \
    eastwind.h \
    equations.h \
    focus.h \
    mainwindow.h \
    mass.h \
    pid_file.h \
    pitch.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Exp.qrc
