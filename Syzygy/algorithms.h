#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define PI 3.14159265

//#include <QVector>
#include <cmath>
#include "planet.h"

class Algorithms
{
public:
    Algorithms();
    Algorithms(Planet);
    void PlanetMovement(Planet, float);
    float CurrentAngularPos(Planet, int);
private:
    int systemCenterX;
    int systemCenterY;
};

#endif // ALGORITHMS_H
