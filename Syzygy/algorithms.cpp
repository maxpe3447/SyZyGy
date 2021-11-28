#include "algorithms.h"

Algorithms::Algorithms(QVector<Planet*> &planets, QObject *parent) : QObject(parent), planetsAlg(planets)
{
    systemCenterX = planetsAlg[0]->GetX() + planetsAlg[0]->GetWidth() / 2.0;
    systemCenterY = planetsAlg[0]->GetY() + planetsAlg[0]->GetHeight() / 2.0;
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(GetResponse(QNetworkReply*)));
}

Algorithms::~Algorithms()
{
    manager->deleteLater();
}

void Algorithms::PlanetMovement(int planetId, double angle)
{
    double newX = planetsAlg[planetId]->GetX() + planetsAlg[planetId]->GetWidth() / 2.0;
    double newY = planetsAlg[planetId]->GetY() + planetsAlg[planetId]->GetHeight() / 2.0;
    double radius = sqrt(pow((newX - systemCenterX), 2) + pow((newY - systemCenterY), 2));
    double currentAngle = 0;
    if(newX < systemCenterX){
        currentAngle = 3.14159265 - asin((newY - systemCenterY) / radius);
    }
    else{
        currentAngle = asin((newY - systemCenterY) / radius);
    }
    double moveAngle = 6.28318531 - (angle * (PI / 180.0));

    int step = (currentAngle - moveAngle) / 0.01745329;
    if(step < 0){
        step += 360;
    }

    newX = planetsAlg[planetId]->GetX();
    newY = planetsAlg[planetId]->GetY();
    QSequentialAnimationGroup* movePlanetGroup = new QSequentialAnimationGroup();
    for(int i = 0; i < step; i++){
        currentAngle -= 0.01745329;
        if(currentAngle < 0) currentAngle += 6.28318531;

        QPropertyAnimation* movePlanet = new QPropertyAnimation(planetsAlg[planetId]->planet, "pos");
        movePlanet->setDuration(25);
        movePlanet->setStartValue(QPoint(newX, newY));
        newX = systemCenterX + cos(currentAngle) * radius - planetsAlg[planetId]->GetWidth() / 2.0;
        newY = systemCenterY + sin(currentAngle) * radius - planetsAlg[planetId]->GetHeight() / 2.0;
        movePlanet->setEndValue(QPoint(newX, newY));
        movePlanetGroup->addAnimation(movePlanet);
    }
    movePlanetGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void Algorithms::AllPlanetsMovement(QDate* date)
{
    for(int i = 1; i < 9; i++){
        QString path = "https://ssp.imcce.fr/webservices/miriade/api/ephemcc.php?-name=p:" + QString::number(i) + "&-observer=@sun&-ep=" + date->toString("yyyy-MM-dd") + "T00:00:00.000&-rplane=2&-mime=json&-from=Syzygy";
        manager->get(QNetworkRequest(QUrl(path)));
    }
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
    //qDebug() << qSetRealNumberPrecision( 10 ) << ((result < 0) ? (360 + result) : result);

    reply->deleteLater();

    PlanetMovement(planetNum, (result < 0) ? (360 + result) : result);
}
