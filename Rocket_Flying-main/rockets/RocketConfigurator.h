#ifndef ROCKETS_H
#define ROCKETS_H

#include <QDebug>
#include <math.h>
#include "Rocket.h"

enum class RocketType {
    master,
    cz_2c
};

Rocket RocketConfigurator(RocketType type);

#endif // ROCKETS_H
