#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define PI 3,1415926535897932

#include <QPropertyAnimation>
#include <cmath>
#include "planet.h"

class Algorithms
{
public:
    Algorithms();
    ~Algorithms();
    Algorithms(Planet*);
    void PlanetMovement(Planet*, double);
    double CurrentAngularPos(Planet*, int);
private:
    int systemCenterX;
    int systemCenterY;

    QPropertyAnimation* movePlanet;
};

#endif // ALGORITHMS_H
