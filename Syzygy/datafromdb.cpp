#include "datafromdb.h"

DataFromDB::DataFromDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    if(!QFile::exists(fileName)){
        throw SyzygyException("На пристрої немає зображень!\nПеревстановіть додаток", true, false);
    }

    db.setDatabaseName(fileName);

    OpenConnect();
}
    DataFromDB::~DataFromDB()
    {
        CloseConnect();
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

    QString DataFromDB::GetTextOf(QString name, QString table, QString type){
        QSqlQuery query(db);
        if (!query.exec("SELECT " +type +" FROM " + table + " WHERE Name = \"" + name + "\"")) {
            qDebug() << "Даже селект не получается, я пас.";
        }

        query.last();

        QSqlRecord rec = query.record();

        QString res = query.value(rec.indexOf("Url")).toString();
        //qDebug() << "Label: " << res;
        return res;
    }

    void DataFromDB::CloseConnect(){
        if(db.isOpen()){
            db.close();
        }
    }
    void DataFromDB::OpenConnect(){
        if(!db.open()){
            qDebug() << "error! no open"<< db.lastError().text();
            throw SyzygyException("Помилка відкриття файлу який містить зображення", false, true);
        }
    }
    QString DataFromDB::CartoonTable = "cartoon";
    QString DataFromDB::GitHubTable = "GitHab";



