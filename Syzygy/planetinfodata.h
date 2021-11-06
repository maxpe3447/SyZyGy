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
    QString GetUkrName() const;

    QByteArray GetImg() const;

    int GetWidthForm() const;
    int GetHeighForm() const;

    int GetImgWidth() const;
    int GetImgHeight() const;

    bool isEmpty() const;

    PlanetInfoData* Parse(QString);
private:
    QString name;
    QString info;
    QString ukrName;

    QByteArray img;

    int widthForm;
    int heightForm;

    int imgWidth;
    int imgHeight;

    bool empty;

    QString fileXML = "planets.xml";

    SetPlanetImage* planetImageSetter;
};

#endif // PLANETINFODATA_H
