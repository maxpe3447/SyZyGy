#include "planetinfodata.h"

PlanetInfoData::PlanetInfoData(SetPlanetImage* planetImageSetter): empty{true}
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

QByteArray PlanetInfoData::GetImg() const
{
    return img;
}

int PlanetInfoData::GetWidthForm() const
{
    return widthForm;
}

int PlanetInfoData::GetHeighForm() const
{
    return heightForm;
}

bool PlanetInfoData::isEmpty()
{
    return empty;
}

PlanetInfoData* PlanetInfoData::Parse(QString planetName)
{
    //QString data;
    QFile file(fileXML);

    if(!file.open(QFile::ReadOnly| QFile::Text)){
       //TODO
        return this;
    }

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
                    QString imgName= xmlReader.readElementText();
                    qDebug() << "!!!!!!!!" << imgName;
                    img = planetImageSetter->GetImageOf(imgName);
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

            }
    }

    empty = false;
    return this;
}
