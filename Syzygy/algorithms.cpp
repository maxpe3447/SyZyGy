#include "algorithms.h"

Algorithms::Algorithms()
{
    systemCenterX = 405; //window test center
    systemCenterY = 300;
}

Algorithms::~Algorithms()
{
    delete movePlanet;
}

Algorithms::Algorithms(Planet* star)
{
    systemCenterX = star->GetX(); //Coordinates of The Sun(system center)
    systemCenterY = star->GetY();
}

double Algorithms::CurrentAngularPos(Planet* planet, int radius)
{
    return acos((planet->GetX()-systemCenterX)/radius);
}

void Algorithms::PlanetMovement(Planet *planet, double angle)
{
    int radius = sqrt(pow((planet->GetX()-systemCenterX), 2)+pow((planet->GetY()-systemCenterY), 2));
    //double currentAngle = 6.28318531 - CurrentAngularPos(planet, radius);
    //float currentAngle = 360 - CurrentAngularPos(planet, radius) * (180 / PI);
    double moveAngle = 6.28318531 - angle;
    //float moveAngle = (360 - angle) * (PI / 180);
    int newX = systemCenterX + cos(moveAngle)*radius;
    int newY = systemCenterY + sin(moveAngle)*radius;
    movePlanet = new QPropertyAnimation(planet->planet, "pos");
    movePlanet->setDuration(3000);
    movePlanet->setStartValue(planet->planet->pos());
    movePlanet->setEndValue(QPoint(newX, newY));
    movePlanet->start();


}
