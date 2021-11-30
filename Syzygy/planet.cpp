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
    SetImg(obj);
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

void Planet::SetRadius(int radius)
{
    this->radius = radius;
}

int Planet::GetRadius() const
{
    return radius;
}

int Planet::GetX() const
{
    return planet->geometry().x();
}

int Planet::GetY() const
{
    return planet->geometry().y();
}

int Planet::GetWidth() const
{
    return planet->width();
}

int Planet::GetHeight() const
{
    return planet->height();
}

QLabel *Planet::GetBase() const
{
    return  this->planet;
}

QString Planet::GetName() const
{
    return planet->objectName();
}

void Planet::SetImg(QPixmap &pxm)
{

    this->planet->setPixmap(pxm.scaled(planet->width(), planet->height()));
    planet->setStyleSheet("background: transparent;");

    auto position = planet->pos();
    auto size = planet->size();
    planet->setGeometry(position.x(), position.y(), size.width(), size.height());
}

void Planet::SetParams(QLabel* pLabel, QString img){
    planet = pLabel;
    QPixmap obj(img);

    SetImg(obj);
}

void Planet::SetParams(const QByteArray &img)
{

    QPixmap obj;
    obj.loadFromData(img, TABLE_IMG_FORMAT);

    SetImg(obj);

}

void Planet::SetParams(const QString &img)
{
    QPixmap obj(img);

    SetImg(obj);
}
