#include "setplanetimage.h"

SetPlanetImage::SetPlanetImage()
{


    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("images.db");


    if(!db.open()){
        qDebug() << "error! no open"<< db.lastError().text();
    }
     qDebug() << "1";
}
    SetPlanetImage::~SetPlanetImage()
    {
        db.close();
    }

    QByteArray SetPlanetImage::GetImageOf(QString namePlanet)
    {
        QSqlQuery query(db);
        if (!query.exec("SELECT * FROM cartoon WHERE Name = \"" + namePlanet + "\"")) {
            qDebug() << "Даже селект не получается, я пас.";
        }

        query.last();

        QSqlRecord rec = query.record();
        return query.value(rec.indexOf("Img")).toByteArray();

    }
