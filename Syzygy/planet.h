#ifndef PLANET_H
#define PLANET_H

#include <QLabel>
#include <QString>
#include <QByteArray>
#include <datafromdb.h>

class Planet
{
public:
    Planet();
    Planet(QLabel* pLabel);
    Planet(QLabel* pLabel, QString img);
    Planet(QLabel* pLabel, QString img, int width, int height);

    void SetParams(QLabel* pLabel, QString img);
    void SetParams(QLabel* pLabel, const QByteArray& img);
    void SetParams(const QByteArray& img);
    void SetParams(const QString& img);

    void SetPos(int x, int y);

    void SetRadius(int radius);

    int GetRadius() const;

    int GetX() const;
    int GetY() const;

    int GetWidth() const;
    int GetHeight() const;

    QLabel* GetBase() const;
    QString GetName() const;
private:
    friend class ManageSession;

    void SetImg(QPixmap& pxm);
    QLabel *planet;
    int radius;
};

#endif // PLANET_H
