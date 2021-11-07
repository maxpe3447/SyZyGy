#include "algorithms.h"

Algorithms::Algorithms()
{
    systemCenterX = 472; //window test center
    systemCenterY = 384;
    manager = new QNetworkAccessManager();
    movePlanetGroup = new QSequentialAnimationGroup();
}

Algorithms::~Algorithms()
{
    movePlanetGroup->deleteLater();
    manager->deleteLater();
}

Algorithms::Algorithms(Planet* star)
{
    systemCenterX = star->GetX(); //Coordinates of The Sun(system center)
    systemCenterY = star->GetY();
    manager = new QNetworkAccessManager();
    movePlanetGroup = new QSequentialAnimationGroup();
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
    int step = (currentAngle - moveAngle) / 0.01745329; // 6=0.10472
    if(step < 0) step += 360;
    for(int i = 0; i < step; ++i){
        currentAngle -= 0.01745329;
        QPropertyAnimation* movePlanet = new QPropertyAnimation(planet->planet, "pos");
        movePlanet->setDuration(25);
        movePlanet->setStartValue(QPoint(newX, newY));
        newX = systemCenterX + cos(currentAngle) * radius;
        newY = systemCenterY + sin(currentAngle) * radius;
        movePlanet->setEndValue(QPoint(newX, newY));
        movePlanetGroup->addAnimation(movePlanet);
    }
    movePlanetGroup->start();
}

void Algorithms::HeliocentricLon(Planet* planet, QDate date)
{
    QString path = "https://ssd.jpl.nasa.gov/api/horizons.api?COMMAND='399'&CENTER='500@10'&START_TIME='" + date.toString("yyyy-MM-dd") + "'&STOP_TIME='" + date.addDays(1).toString("yyyy-MM-dd") + "'&STEP_SIZE='1%20d'&QUANTITIES='18'";
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
