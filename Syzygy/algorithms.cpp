#include "algorithms.h"

Algorithms::Algorithms(QMainWindow* mw, QVector<Planet*> &planets, QObject *parent)
    : QObject(parent), isAnimErrShown(false), isReplyErrShown(false), mainWindow(mw), planetsAlg(planets)
{
    systemCenterX = planetsAlg[0]->GetX() + planetsAlg[0]->GetWidth() / 2.0;
    systemCenterY = planetsAlg[0]->GetY() + planetsAlg[0]->GetHeight() / 2.0;
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &Algorithms::GetResponse);
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
    connect(movePlanetGroup, &QSequentialAnimationGroup::currentAnimationChanged, this, &Algorithms::PlanetsCheck);
    for(int i = 0; i < step; i++){
        currentAngle -= 0.01745329;
        if(currentAngle < 0) currentAngle += 6.28318531;

        QPropertyAnimation* movePlanet = new QPropertyAnimation(planetsAlg[planetId]->GetBase(), "pos");
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
    isAnimErrShown = false;
    isReplyErrShown = false;
    for(int i = 1; i < planetsAlg.size(); i++){
        QString path = "https://ssp.imcce.fr/webservices/miriade/api/ephemcc.php?-name=p:" + QString::number(i) + "&-observer=@sun&-ep=" + date->toString("yyyy-MM-dd") + "T00:00:00.000&-rplane=2&-mime=json&-from=Syzygy";
        manager->get(QNetworkRequest(QUrl(path)));
    }
}

void Algorithms::GetResponse(QNetworkReply *reply)
{
    try {
        if (reply->error() != QNetworkReply::NoError) {
            switch (reply->error()) {
                case QNetworkReply::ConnectionRefusedError:
                    throw SyzygyException("Сервер відмовив у з'єднані! Зверніться до розробників!", true, false);
                    break;
                case QNetworkReply::HostNotFoundError:
                    throw SyzygyException("Недійсне ім'я серверу! Зверніться до розробників!", true, false);
                    break;
                case QNetworkReply::TimeoutError:
                    throw SyzygyException("Минув час очікування підключення до серверу!", false, true);
                    break;
                case QNetworkReply::TemporaryNetworkFailureError:
                case QNetworkReply::NetworkSessionFailedError:
                    throw SyzygyException("З'єднання було розірвано через відключення від мережі! Перевірте Інтернет-з'єднання!", false, true);
                    break;
                case QNetworkReply::ContentAccessDenied:
                    throw SyzygyException("Було відмовлено в доступі до вмісту серверу! Зверніться до розробників!", true, false);
                    break;
                case QNetworkReply::ContentNotFoundError:
                    throw SyzygyException("Віддалений вміст не знайдено на сервері! Зверніться до розробників!", true, false);
                    break;
                case QNetworkReply::ContentConflictError:
                    throw SyzygyException("Не вдалося виконати запит до серверу через конфлікт із поточним станом ресурсу! Зверніться до розробників!", true, false);
                    break;
                case QNetworkReply::ContentGoneError:
                    throw SyzygyException("Запитаний ресурс більше не доступний на сервері! Зверніться до розробників!", true, false);
                    break;
                case QNetworkReply::InternalServerError:
                    throw SyzygyException("Сервер зіткнувся з несподіваною умовою, яка завадила йому виконати запит! Зверніться до розробників!", true, false);
                    break;
                case QNetworkReply::OperationNotImplementedError:
                    throw SyzygyException("Сервер не підтримує функціональні можливості, необхідні для виконання запиту! Зверніться до розробників!", true, false);
                    break;
                case QNetworkReply::ServiceUnavailableError:
                    throw SyzygyException("Сервер не може обробити запит на даний момент! Спробуйте пізніше!", false, true);
                    break;
                default:
                    throw SyzygyException("Сталася помилка під час взаємодії з сервером! Зверніться до розробників!", true, false);
                    break;
            }
        }

        QJsonDocument parseReply;
        QJsonParseError parseErr;
        QJsonArray arrayReply;
        QString replyRes;
        int planetNum = 0;

        QByteArray responseData = reply->readAll();
        parseReply = QJsonDocument::fromJson(responseData, &parseErr);

        if(parseErr.errorString().toInt() == QJsonParseError::NoError){
            arrayReply = QJsonValue(parseReply.object().value("data")).toArray();
            planetNum = parseReply.object().value("sso").toObject().value("num").toString().toInt();
        }
        else{
            throw SyzygyException("Під час обробки відповіді від серверу сталася помилка!", false, true);
        }
        for(int i = 0; i < arrayReply.count(); i++){
            if(arrayReply.at(i).toObject().contains("Longitude")){
                replyRes = arrayReply.at(i).toObject().value("Longitude").toString();
            }
        }

        double result = 0;
        QRegularExpression pattern("\\d+");
        QRegularExpressionMatchIterator matchParts = pattern.globalMatch(replyRes);
        if(matchParts.hasNext()){
            result = (matchParts.next().captured().toDouble() + matchParts.next().captured().toDouble() / 60.0) - 90.0;
        }
        else{
            throw SyzygyException("Потрібних даних у відповіді від серверу не знайдено!", false, true);
        }

        reply->deleteLater();

        PlanetMovement(planetNum, (result < 0) ? (360 + result) : result);
    }
    catch (const SyzygyException& ex) {
        mutex.lock();
        if(!isReplyErrShown){
            isReplyErrShown = true;
            mutex.unlock();
            SyzygyException::WhatShow(ex);
        }
        else mutex.unlock();
    }
}

void Algorithms::PlanetsCheck()
{
    try {
        mutex.lock();
        for(int i = 0; i < planetsAlg.size(); i++){
            int iposX = planetsAlg[i]->GetX();
            int iposY = planetsAlg[i]->GetY();
            int iposR = iposX + planetsAlg[i]->GetWidth();
            int iposB = iposY + planetsAlg[i]->GetHeight();
            if(iposX < 0 || iposY < 0 || iposR > mainWindow->geometry().width() || iposB > mainWindow->geometry().height() - 36){
                mutex.unlock();
                throw SyzygyException("Небесне тіло вийшло за межі вікна!", false, true);
            }
            for (int j = i + 1; j < planetsAlg.size(); j++) {
                int icenterX = iposX + planetsAlg[i]->GetWidth() / 2;
                int icenterY = iposY + planetsAlg[i]->GetHeight() / 2;
                int jcenterX = planetsAlg[j]->GetX() + planetsAlg[j]->GetWidth() / 2;
                int jcenterY = planetsAlg[j]->GetY() + planetsAlg[j]->GetHeight() / 2;
                double distance = sqrt(pow((icenterX - jcenterX), 2) + pow((icenterY - jcenterY), 2));
                double ideal = planetsAlg[i]->GetWidth() / 2 + planetsAlg[j]->GetWidth() / 2;
                if(distance <= ideal){
                    mutex.unlock();
                    throw SyzygyException("Зіткнення двох небесних тіл!", false, true);
                }
            }
        }
        mutex.unlock();
    }
    catch(const SyzygyException& ex){
        mutex.lock();
        if(!isAnimErrShown){
            isAnimErrShown = true;
            mutex.unlock();
            SyzygyException::WhatShow(ex);
        }
        else mutex.unlock();
    }
}
