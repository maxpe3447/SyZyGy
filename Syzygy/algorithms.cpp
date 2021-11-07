#include "algorithms.h"

Algorithms::Algorithms()
{
    systemCenterX = 360; //window test center
    systemCenterY = 360;
    manager = new QNetworkAccessManager();
    movePlanetsGroup = new QParallelAnimationGroup();
}

Algorithms::~Algorithms()
{
    movePlanetsGroup->deleteLater();
    manager->deleteLater();
}

Algorithms::Algorithms(Planet* star)
{
    systemCenterX = star->GetX(); //Coordinates of The Sun(system center)
    systemCenterY = star->GetY();
    manager = new QNetworkAccessManager();
    movePlanetsGroup = new QParallelAnimationGroup();
}

void Algorithms::PlanetMovement(Planet* planet, double angle)
{
    double radius = sqrt(pow((planet->GetX()-systemCenterX), 2)+pow((planet->GetY()-systemCenterY), 2));
    double currentAngle = 6.28318531 - acos((planet->GetX() - systemCenterX) / radius);
    //double currentAngle = 360 - CurrentAngularPos(planet, radius) * (180 / PI);
    //double moveAngle = 6.28318531 - angle;
    double moveAngle = (360. - angle) * (PI / 180.);
    int newX = planet->GetX();
    int newY = planet->GetY();
    int step = (currentAngle - moveAngle) / 0.01745329;
    if(step < 0) step += 360;
    QSequentialAnimationGroup* movePlanetGroup = new QSequentialAnimationGroup();
    for(int i = 0; i < step; ++i){
        currentAngle -= 0.01745329;
        if(currentAngle < 0) currentAngle += 6.28318531;
        QPropertyAnimation* movePlanet = new QPropertyAnimation(planet->planet, "pos");
        movePlanet->setDuration(25);
        movePlanet->setStartValue(QPoint(newX, newY));
        newX = systemCenterX + cos(currentAngle) * radius;
        newY = systemCenterY + sin(currentAngle) * radius;
        movePlanet->setEndValue(QPoint(newX, newY));
        movePlanetGroup->addAnimation(movePlanet);
    }
    movePlanetsGroup->addAnimation(movePlanetGroup);
}

void Algorithms::HeliocentricLon(Planet* planet, QString planetId, QDate date)
{
    //manager = new QNetworkAccessManager();
    QString path = "https://ssd.jpl.nasa.gov/api/horizons.api?COMMAND='" + planetId + "'&CENTER='500@10'&START_TIME='" + date.toString("yyyy-MM-dd") + "'&STOP_TIME='" + date.addDays(1).toString("yyyy-MM-dd") + "'&STEP_SIZE='1%20d'&QUANTITIES='18'";
    QObject::connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply)
    {
        // TODO: Situation -> get_reply_error
        if (reply->error()) {
            qDebug() << QString("Error %1").arg(reply->errorString());
            return ;
        }

        QByteArray responseData = reply->readAll();
        parseReply = QJsonDocument::fromJson(responseData, &parseErr);

        // TODO: Situation -> get_jsonParse_error
        if(parseErr.errorString().toInt() == QJsonParseError::NoError){
            replyRes = QJsonValue(parseReply.object().value("result")).toString();
        }

        int start = replyRes.indexOf("$$SOE");
        int end = replyRes.indexOf("$$EOE");
        QRegularExpressionMatch match;
        replyRes.mid(start, end - start).contains(QRegularExpression("\\d+[.]\\d+"), &match);
        double result = match.captured().toDouble() - 90;
        qDebug() << qSetRealNumberPrecision( 10 ) << ((result < 0) ? (360 + result) : result);
        PlanetMovement(planet, (result < 0) ? (360 + result) : result);

        reply->deleteLater();
    });
    manager->get(QNetworkRequest(QUrl(path)));
}

void Algorithms::AllPlanetsMovement(QVector<Planet *> &planets, QDate date)
{
    /*HeliocentricLon(planets[0], "399", date);
    HeliocentricLon(planets[1], "599", date);
    HeliocentricLon(planets[2], "499", date);
    HeliocentricLon(planets[3], "199", date);
    HeliocentricLon(planets[4], "899", date);
    HeliocentricLon(planets[5], "699", date);
    HeliocentricLon(planets[7], "799", date);
    HeliocentricLon(planets[8], "299", date);*/
    PlanetMovement(planets[0], 290);
    PlanetMovement(planets[1], 310);
    PlanetMovement(planets[2], 300);
    PlanetMovement(planets[3], 270);
    PlanetMovement(planets[4], 340);
    PlanetMovement(planets[5], 320);
    PlanetMovement(planets[7], 330);
    PlanetMovement(planets[8], 280);

    movePlanetsGroup->start();
}
