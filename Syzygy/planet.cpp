#include "planet.h"

Planet::Planet():planet{nullptr}
{

}
Planet::Planet(QLabel *pLabel):planet{pLabel}
{

}
Planet::Planet(QLabel* pLabel, QString img):planet{pLabel}
{
    QPixmap obj(img);
    planet->setPixmap(obj.scaled(planet->width(), planet->height()));
    planet->setStyleSheet("background: transparent;");
}
Planet::Planet(QLabel* pLabel, QString img, int width, int height):Planet(pLabel, img)
{   
    auto position = planet->pos();
    planet->setGeometry(position.x(), position.y(), width, height);

}
void Planet::SetPos(int x, int y)
{
    planet->setGeometry(x, y, planet->width(),planet->height());

}
void Planet::SetParams(QLabel* pLabel, QString img){
    planet = pLabel;
    QPixmap obj(img);
    planet->setPixmap(obj.scaled(planet->width(), planet->height()));
    planet->setStyleSheet("background: transparent;");

    auto position = planet->pos();
    auto size = planet->size();
    planet->setGeometry(position.x(), position.y(), size.width(), size.height());
}
