#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define PI 3.1415926535897932

#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
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
    void HeliocentricLon(Planet*, QString, QDate);
    void AllPlanetsMovement(QVector<Planet*>&, QDate);
private:
    int systemCenterX;
    int systemCenterY;

    QParallelAnimationGroup* movePlanetsGroup;
    QNetworkAccessManager* manager;

    QJsonDocument parseReply;
    QJsonParseError parseErr;
    QString replyRes;
};

#endif // ALGORITHMS_H
