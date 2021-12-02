#ifndef DATAFROMDB_H
#define DATAFROMDB_H

#include <QSqlDatabase>
#include <QSqlError>
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

    QByteArray GetImageOf(QString nameImg, QString type);
    //QByteArray GetSysImage(QString name);

    int GetRadiusOf(QString nameImg);

    void CloseConnect();
    void OpenConnect();

    QString GetTextOf(QString name, QString table, QString type = "*");

    static QString CartoonTable;
    static QString GitHubTable;
    static QString PlanetData;
private:
    QSqlDatabase db;

    QString fileName = "images.db";
};

#endif // DATAFROMDB_H
