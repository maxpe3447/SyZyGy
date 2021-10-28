#ifndef SETPLANETIMAGE_H
#define SETPLANETIMAGE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QByteArray>
#include <QSqlQuery>
#include <QSqlRecord>

#define TABLE_KEY_IMG    "Img"
#define TABLE_IMG_FORMAT "PNG"

class SetPlanetImage
{
public:
    SetPlanetImage();
    ~SetPlanetImage();

    QByteArray GetImageOf(QString namePlanet);
private:
    QSqlDatabase db;
};

#endif // SETPLANETIMAGE_H
