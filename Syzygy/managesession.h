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
//#include "mainwindow.h"
#include "planet.h"
class ManageSession
{
public:
    ManageSession();
    void GetLastSession(QVector<Planet*>&);
    void SetCurrentSession(QVector<Planet*>&);
private:
    QString fileName = "last_session.json";
    QString arrKey = "planets";
    QString planetNameKey = "name";
    QString xKey = "x";
    QString yKey = "y";
    void Default(QVector<Planet*>&);
    QJsonDocument doc;
    QJsonArray docArr;
    QJsonParseError docErr;
};

#endif // MANAGESESSION_H
