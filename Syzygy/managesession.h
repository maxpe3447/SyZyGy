#ifndef MANAGESESSION_H
#define MANAGESESSION_H

#include <QString>
#include <string>
#include <QVector>
#include <QFile>
#include <QJsonArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include "QLabel"

#include <syzygyexception.h>
#include "planet.h"
class ManageSession
{
public:
    ManageSession();
    void GetLastSession(QVector<Planet*>&, QDate& date);
    void SetCurrentSession(QVector<Planet*>&, QDate);

    QString GetFileName() const;
    //void ReadRadiusFromFile(QVector<Planet*>&);
private:
    QString fileName = "last_session.json";
    QString arrKey = "planets";
    QString planetNameKey = "name";
    QString xKey = "x";
    QString yKey = "y";
    QString radiusKey = "radius";
    QString dateKey = "date";

    QJsonDocument doc;
    QJsonArray docArr;
    QJsonParseError docErr;
};

#endif // MANAGESESSION_H
