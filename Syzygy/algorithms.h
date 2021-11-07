#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define PI 3.1415926535897932

#include <QPropertyAnimation>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDate>
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
    void HeliocentricLon(Planet*, QDate);
private:
    int systemCenterX;
    int systemCenterY;

    //QPropertyAnimation* movePlanet;
    QNetworkAccessManager* manager;

    QJsonDocument parseReply;
    QJsonParseError parseErr;
    QString replyRes;
};

#endif // ALGORITHMS_H
