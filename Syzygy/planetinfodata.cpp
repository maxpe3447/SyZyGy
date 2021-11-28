#include "planetinfodata.h"

PlanetInfoData::PlanetInfoData(DataFromDB* planetImageSetter): empty{true}
{
    this->planetImageSetter = planetImageSetter;
}

void PlanetInfoData::SetName(QString name)
{
    this->name = name;
}

void PlanetInfoData::SetInfo(QString info)
{
    this->info = info;
}

void PlanetInfoData::SetImg(QByteArray img)
{
    this->img = img;
}

void PlanetInfoData::SetWidthForm(int newWidth)
{
    widthForm = newWidth;
}

void PlanetInfoData::SetHeighForm(int newHeight)
{
    heightForm = newHeight;
}

QString PlanetInfoData::GetName() const
{
    return name;
}

QString PlanetInfoData::GetInfo() const
{
    return info;
}

QString PlanetInfoData::GetUkrName() const
{
    return ukrName;
}

QByteArray PlanetInfoData::GetImg() const
{
    return img;
}

QString PlanetInfoData::GetImgStyle() const
{
    return stylePlanet;
}

int PlanetInfoData::GetWidthForm() const
{
    return widthForm;
}

int PlanetInfoData::GetHeighForm() const
{
    return heightForm;
}

int PlanetInfoData::GetImgWidth() const
{
    return imgWidth;
}

int PlanetInfoData::GetImgHeight() const
{
    return imgHeight;
}

bool PlanetInfoData::isEmpty() const
{
    return empty;
}

PlanetInfoData* PlanetInfoData::Parse(QString planetName)
{
    QFile file(fileXML);

    if(!file.open(QFile::ReadOnly| QFile::Text)){

        throw SyzygyException("Нажаль немає XML файлу");
        return this;
    }

    planetImageSetter->OpenConnect();

    QXmlStreamReader xmlReader;

    xmlReader.setDevice(&file);
    xmlReader.readNext();

    while(!xmlReader.atEnd()){
        if(xmlReader.isStartElement()){
            if(xmlReader.name() == planetName){
                foreach(const QXmlStreamAttribute &atr, xmlReader.attributes()){
                    if(atr.name().toString() == "name")
                        name = atr.value().toString();
                    else if (atr.name().toString() == "formWidth")
                        widthForm = atr.value().toInt();
                    else if(atr.name().toString() == "formHeight")
                        heightForm = atr.value().toInt();
                    else if(atr.name().toString() == "ukrName")
                        ukrName = atr.value().toString();
                }

                xmlReader.readNext();
                xmlReader.readNext();
                xmlReader.readNextStartElement();

                while(xmlReader.isStartElement() && xmlReader.name().toString() == "text"){

                    info += xmlReader.readElementText() + "\n";
                    xmlReader.readNextStartElement();
                }
                xmlReader.readNext();
                xmlReader.readNextStartElement();

                if(xmlReader.isStartElement()&& xmlReader.name().toString() == "img"){
                    foreach(const QXmlStreamAttribute &atr, xmlReader.attributes()){
                        if(atr.name().toString() == "imgWidth")
                            imgWidth = atr.value().toInt();
                        else if (atr.name().toString() == "imgHeight")
                            imgHeight = atr.value().toInt();
                        else if (atr.name().toString() == "type")
                            stylePlanet = atr.value().toString();
                    }
                    img = planetImageSetter->GetImageOf(xmlReader.readElementText(), stylePlanet);
                }
            }
        }
        xmlReader.readNext();
        if (xmlReader.hasError()) {
                qDebug() << "   Error Type:" << xmlReader.error();
                qDebug() << " Error String:" << xmlReader.errorString();
                qDebug() << "  Line Number:" << xmlReader.lineNumber();
                qDebug() << "Column Number:" << xmlReader.columnNumber();
                qDebug() << " Char. Offset:" << xmlReader.characterOffset();
                throw SyzygyException("Зчитування відбулось з помилкою", false, true);
            }
    }

    empty = false;
    planetImageSetter->CloseConnect();
    return this;
}
