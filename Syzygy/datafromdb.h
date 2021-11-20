#ifndef DATAFROMDB_H
#define DATAFROMDB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QByteArray>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>

#include "syzygyexception.h"

#define TABLE_KEY_IMG    "Img"
#define TABLE_IMG_FORMAT "PNG"

class DataFromDB
{
public:
    DataFromDB();
    ~DataFromDB();

    QByteArray GetImageOf(QString namePlanet, QString type);
    //QByteArray GetSysImage(QString name);

    static QString CartoonTable;
    static QString GitHubTable;
private:
    QSqlDatabase db;

    QString fileName = "images.db";
};

#endif // DATAFROMDB_H
