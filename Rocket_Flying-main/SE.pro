QT       += core gui printsupport
QT       += sql
QT       += core gui widgets
CONFIG += c++20
CONFIG += staticlib c++11
#QMAKE_CXXFLAGS += -Wunused -Werror

#QMAKE_CXXFLAGS += -Wa,-mbig-obj
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataVector.cpp \
    FlightInit.cpp \
    FlightSolver.cpp \
    aerodynamics/airforce.cpp \
    aerodynamics/focus.cpp \
    alpha.cpp \
    atmosphere/atmosphere.cpp \
    dycoef.cpp \
    eastwind.cpp \
    equations.cpp \
    main.cpp \
    mainwindow.cpp \
    mass.cpp \
    libs/qcustomplot.cpp \
    rockets/RocketConfigurator.cpp \
    rockets/element.cpp

HEADERS += \
    Constants.h \
    DataVector.h \
    FlightInit.h \
    FlightSolver.h \
    FlightType.h \
    aerodynamics/airforce.h \
    aerodynamics/focus.h \
    atmosphere/atmosphere.h \
    rocket/Rocket.h \
    alpha.h \
    atmosphere.h \
    dycoef.h \
    eastwind.h \
    equations.h \
    focus.h \
    mainwindow.h \
    mass.h \
    libs/qcustomplot.h \
    rockets/Rocket.h \
    rockets/RocketConfigurator.h \
    rockets/Rockets.h \
    rockets/element.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Exp.qrc
