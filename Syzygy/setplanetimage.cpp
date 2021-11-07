#include "setplanetimage.h"

SetPlanetImage::SetPlanetImage()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    if(!QFile::exists("images.db")){
        throw SyzygyException("На пристрої немає зображень!\nПеревстановіть додаток", true, false);
    }

    db.setDatabaseName("images.db");

    if(!db.open()){
        qDebug() << "error! no open"<< db.lastError().text();
        throw SyzygyException("Помилка відкриття файлу який містить зображення", false, true);
    }
}
    SetPlanetImage::~SetPlanetImage()
    {
        db.close();
    }

    QByteArray SetPlanetImage::GetImageOf(QString namePlanet, QString type)
    {
        QSqlQuery query(db);
        if (!query.exec("SELECT * FROM " + type + " WHERE Name = \"" + namePlanet + "\"")) {
            qDebug() << "Даже селект не получается, я пас.";
        }

        query.last();

        QSqlRecord rec = query.record();
        return query.value(rec.indexOf("Img")).toByteArray();

    }

    QByteArray SetPlanetImage::GetSysImage(QString name)
    {
        QSqlQuery query(db);
        if (!query.exec("SELECT * FROM systemImage WHERE Name = \"" + name + "\"")) {
            qDebug() << "Даже селект не получается, я пас.";
        }

        query.last();

        QSqlRecord rec = query.record();
        return query.value(rec.indexOf("Img")).toByteArray();
    }
