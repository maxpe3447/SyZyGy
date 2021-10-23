#include "algorithms.h"

Algorithms::Algorithms()
{
    systemCenterX = 405; //window test center
    systemCenterY = 300;
}

Algorithms::Algorithms(Planet star)
{
    systemCenterX = star.GetX(); //Coordinates of The Sun(system center)
    systemCenterY = star.GetY();
}

float Algorithms::CurrentAngularPos(Planet planet, int radius)
{
    return acos((planet.GetX()-systemCenterX)/radius);
}

void Algorithms::PlanetMovement(Planet planet, float angle)
{
    int radius = sqrt(pow((planet.GetX()-systemCenterX), 2)+pow((planet.GetY()-systemCenterY), 2));
    //float currentAngle = 6.28319 - CurrentAngularPos(planet, radius);
    float moveAngle = 6.28319 - angle;
    //float moveAngle = (360 - angle) * (PI / 180);
    int newX = systemCenterX + cos(moveAngle)*radius;
    int newY = systemCenterY + sin(moveAngle)*radius;
    planet.SetPos(newX, newY);
}
