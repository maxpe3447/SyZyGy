#include "datafromdb.h"

DataFromDB::DataFromDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    if(!QFile::exists(fileName)){
        throw SyzygyException("На пристрої немає зображень!\nПеревстановіть додаток", true, false);
    }

    db.setDatabaseName(fileName);

    if(!db.open()){
        qDebug() << "error! no open"<< db.lastError().text();
        throw SyzygyException("Помилка відкриття файлу який містить зображення", false, true);
    }
}
    DataFromDB::~DataFromDB()
    {
        db.close();
    }

    QByteArray DataFromDB::GetImageOf(QString imageName, QString table)
    {
        QSqlQuery query(db);
        if (!query.exec("SELECT * FROM " + table + " WHERE Name = \"" + imageName + "\"")) {
            qDebug() << "Даже селект не получается, я пас.";
        }

        query.last();

        QSqlRecord rec = query.record();
        return query.value(rec.indexOf("Img")).toByteArray();

    }

    QString DataFromDB::CartoonTable = "cartoon";
    QString DataFromDB::GitHubTable = "GitHub";
//    QByteArray DataFromDB::GetSysImage(QString name)
//    {
//        QSqlQuery query(db);
//        if (!query.exec("SELECT * FROM systemImage WHERE Name = \"" + name + "\"")) {
//            qDebug() << "Даже селект не получается, я пас.";
//        }

//        query.last();

//        QSqlRecord rec = query.record();
//        return query.value(rec.indexOf("Img")).toByteArray();
//    }
