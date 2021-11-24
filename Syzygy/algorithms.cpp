#include "algorithms.h"

Algorithms::Algorithms(QVector<Planet*> &planets, QObject *parent) : QObject(parent), planetsAlg(planets)
{
    systemCenterX = 360; //window test center
    systemCenterY = 360;
    manager = new QNetworkAccessManager();
    //movePlanetsGroup = new QParallelAnimationGroup();
    movePlanetGroup = new QSequentialAnimationGroup();
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(GetResponse(QNetworkReply*)));
}

Algorithms::~Algorithms()
{
    //movePlanetsGroup->deleteLater();
    movePlanetGroup->deleteLater();
    manager->deleteLater();
}

void Algorithms::PlanetMovement(int planetId, double angle)
{
    double radius = sqrt(pow((planetsAlg[planetId]->GetX() - systemCenterX), 2) + pow((planetsAlg[planetId]->GetY() - systemCenterY), 2));
    double currentAngle = acos((planetsAlg[planetId]->GetX() - systemCenterX) / radius);
    //double currentAngle = 360 - CurrentAngularPos(planet, radius) * (180 / PI);
    //double moveAngle = 6.28318531 - angle;
    double moveAngle = (360.0 - angle) * (PI / 180.0);

    int newX = planetsAlg[planetId]->GetX();
    int newY = planetsAlg[planetId]->GetY();
    int step = (currentAngle - moveAngle) / 0.01745329;
    if(step < 0){
        step += 360;
    }

    //QSequentialAnimationGroup* movePlanetGroup = new QSequentialAnimationGroup();
    for(int i = 0; i < step; i++){
        currentAngle -= 0.01745329;
        if(currentAngle < 0) currentAngle += 6.28318531;

        QPropertyAnimation* movePlanet = new QPropertyAnimation(planetsAlg[planetId]->planet, "pos");
        movePlanet->setDuration(25);
        movePlanet->setStartValue(QPoint(newX, newY));
        newX = systemCenterX + cos(currentAngle) * radius;
        newY = systemCenterY + sin(currentAngle) * radius;
        movePlanet->setEndValue(QPoint(newX, newY));
        movePlanetGroup->addAnimation(movePlanet);
    }
    movePlanetGroup->start();
    //movePlanetsGroup->addAnimation(movePlanetGroup);
}

void Algorithms::AllPlanetsMovement(QDate date)
{
    for(int i = 1; i < 9; i++){
        QString path = "https://ssp.imcce.fr/webservices/miriade/api/ephemcc.php?-name=p:" + QString::number(i) + "&-observer=@sun&-ep=" + date.toString("yyyy-MM-dd") + "T00:00:00.000&-rplane=2&-mime=json&-from=Syzygy";
        manager->get(QNetworkRequest(QUrl(path)));
    }

    //movePlanetsGroup->start();
}

void Algorithms::GetResponse(QNetworkReply *reply)
{
    // TODO: Situation -> get_reply_error
    if (reply->error()) {
        qDebug() << QString("Error %1").arg(reply->errorString());
        return;
    }

    QJsonDocument parseReply;
    QJsonParseError parseErr;
    QJsonArray arrayReply;
    QString replyRes;
    int planetNum = 0;

    QByteArray responseData = reply->readAll();
    parseReply = QJsonDocument::fromJson(responseData, &parseErr);

    // TODO: Situation -> get_jsonParse_error
    if(parseErr.errorString().toInt() == QJsonParseError::NoError){
        arrayReply = QJsonValue(parseReply.object().value("data")).toArray();
        planetNum = parseReply.object().value("sso").toObject().value("num").toString().toInt();
    }
    for(int i = 0; i < arrayReply.count(); i++){
        if(arrayReply.at(i).toObject().contains("Longitude")){
            replyRes = arrayReply.at(i).toObject().value("Longitude").toString();
        }
    }

    // TODO: Situation -> get_captured_error (hasMatch())
    QRegularExpression pattern("\\d+");
    QRegularExpressionMatchIterator matchParts = pattern.globalMatch(replyRes);
    double result = (matchParts.next().captured().toDouble() + matchParts.next().captured().toDouble() / 60.0) - 90.0;
    qDebug() << qSetRealNumberPrecision( 10 ) << ((result < 0) ? (360 + result) : result);
    PlanetMovement(planetNum, (result < 0) ? (360 + result) : result);

    reply->deleteLater();
}
