    #ifndef PLANETINFODATA_H
#define PLANETINFODATA_H

#include <QString>
#include <QByteArray>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>

#include "setplanetimage.h"

class PlanetInfoData
{
public:
    PlanetInfoData(SetPlanetImage* planetImageSetter);

    void SetName(QString name);
    void SetInfo(QString info);
    void SetImg(QByteArray img);
    void SetWidthForm(int newWidth);
    void SetHeighForm(int newHeight);

    QString GetName() const;
    QString GetInfo() const;
    QByteArray GetImg() const;

    int GetWidthForm() const;
    int GetHeighForm() const;

    bool isEmpty();

    PlanetInfoData* Parse(QString);
private:
    QString name;
    QString info;
    QByteArray img;

    int widthForm;
    int heightForm;

    bool empty;

    QString fileXML = "planets.xml";

    SetPlanetImage* planetImageSetter;
};

#endif // PLANETINFODATA_H
