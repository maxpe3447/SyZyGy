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
    int x = 50, y = 90;

    planets[0]->SetPos(x, y);
    planets[1]->SetPos(x, y+90);

    for(int i = 2, x = 100; i < planets.size(); i++){
        if(i%2==0){
            planets[i]->SetPos(planets[i-2]->GetX()+x,planets[i-2]->GetY());
            //y+=90;
        }
        else{
            planets[i]->SetPos( planets[i-2]->GetX()+x,planets[i-2]->GetY());
        }

    }

}
