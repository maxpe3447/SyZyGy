#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define PI 3.1415926535897932

#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDate>
#include <cmath>
#include "planet.h"

class Algorithms : public QObject
{
    Q_OBJECT
public:
    Algorithms(QVector<Planet*>&, QObject *parent = 0);
    ~Algorithms();
    void PlanetMovement(int, double);
    void AllPlanetsMovement(QDate);
public slots:
    void GetResponse(QNetworkReply*);
private:
    int systemCenterX;
    int systemCenterY;

    //QParallelAnimationGroup* movePlanetsGroup;
    QSequentialAnimationGroup* movePlanetGroup;
    QNetworkAccessManager* manager;

    QVector<Planet*>& planetsAlg;
};

#endif // ALGORITHMS_H
