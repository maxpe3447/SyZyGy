#include "managesession.h"

ManageSession::ManageSession()
{

}

void ManageSession::GetLastSession(QVector<Planet*> & planets, QDate& date)
{
    if(!QFile::exists(fileName)){
        throw SyzygyException("Файлу минулої сесії не уснує!", false, true);

    }
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QFile::Text)){
       doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docErr);
       file.close();

       if(docErr.errorString().toInt() == QJsonParseError::NoError){


            QString sDate = QJsonValue(doc.object().value(dateKey)).toString();//doc[dateKey].toString();
            qDebug() << "Start: " <<sDate;
            date = QDate::fromString(sDate, "dd.MM.yyyy");
           qDebug() << "Start: " << date.toString("dd.MM.yyyy");
           docArr = QJsonValue(doc.object().value(arrKey)).toArray();
           for(int i = 0; i< docArr.count(); i++){

               int x = docArr.at(i).toObject().value(xKey).toInt();
               int y = docArr.at(i).toObject().value(yKey).toInt();

               planets[i]->SetPos(x, y);
           }
           //throw SyzygyException("Помилка обробки json файлу: " + docErr.error,true, false);
       }
    }
    file.close();
}

void ManageSession::SetCurrentSession(QVector<Planet *> & planets, QDate date)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QJsonArray  docToWrite;

    for(int i = 0; i < planets.size(); i++){
        QVariantMap map;
        map.insert(planetNameKey, planets[i]->GetName());
        map.insert(xKey, planets[i]->GetX());
        map.insert(yKey, planets[i]->GetY());

        QJsonObject jsonObj = QJsonObject::fromVariantMap(map);

        docToWrite.append(jsonObj);
    }
    doc.setArray(docToWrite);

    QString title(
                "{\n"
                "\t\"" + dateKey + "\" : \"" + date.toString("dd.MM.yyyy")+ "\",\n"
                "\t\"" + arrKey +  "\":" + doc.toJson() + "}");
    file.write(title.toUtf8());
    file.close();
}

QString ManageSession::GetFileName() const
{
    return fileName;
}

