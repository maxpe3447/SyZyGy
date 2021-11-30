#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define PI 3.1415926535897932

#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDate>
#include <cmath>
#include "planet.h"
#include "syzygyexception.h"

class Algorithms : public QObject
{
    Q_OBJECT
public:
    Algorithms(QMainWindow*, QVector<Planet*>&, QObject *parent = 0);
    ~Algorithms();
public slots:
    void AllPlanetsMovement(QDate*);
private slots:
    void GetResponse(QNetworkReply*);
    void PlanetsCheck();
private:
    void PlanetMovement(int, double);

    double systemCenterX;
    double systemCenterY;
    int animationCounter;

    QNetworkAccessManager* manager;
    QMainWindow* mainWindow;

    QVector<Planet*>& planetsAlg;
};

#endif // ALGORITHMS_H
