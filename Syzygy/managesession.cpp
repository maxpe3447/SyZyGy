#include "managesession.h"

ManageSession::ManageSession()
{

}

void ManageSession::GetLastSession(QVector<Planet*> & planets)
{
    if(!QFile::exists(fileName)){
        Default(planets);
        return;
    }
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QFile::Text)){
       doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docErr);
       file.close();

       if(docErr.errorString().toInt() == QJsonParseError::NoError){
           docArr = QJsonValue(doc.object().value(arrKey)).toArray();
           for(int i = 0; i< docArr.count(); i++){

               int x = docArr.at(i).toObject().value(xKey).toInt();
               int y = docArr.at(i).toObject().value(yKey).toInt();

               planets[i]->SetPos(x, y);
           }
       }
    }
}

void ManageSession::SetCurrentSession(QVector<Planet *> & planets)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);


    QJsonArray  docToWrite;// = doc.object().value(arrKey).toArray();

    for(int i = 0; i < planets.size(); i++){
        QVariantMap map;
        map.insert(planetNameKey, planets[i]->planet->objectName());
        map.insert(xKey, planets[i]->GetX());
        map.insert(yKey, planets[i]->GetY());

        QJsonObject jsonObj = QJsonObject::fromVariantMap(map);

        docToWrite.append(jsonObj);
    }
    doc.setArray(docToWrite);

    QString title("{\n\t\"" + arrKey +  "\":" + doc.toJson() + "}");
    file.write(title.toUtf8());
    file.close();
}

void ManageSession::Default(QVector<Planet*>& planets){

    for(int i = 0, x = 50, y = 50; i < planets.size(); i++){
        if(i%2==0){
            planets[i]->SetPos(x, y);
            y+=90;
        }
        else{
            planets[i]->SetPos(x, y);
            x+=100;
        }

    }

}
