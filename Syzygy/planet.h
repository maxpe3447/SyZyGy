#ifndef PLANET_H
#define PLANET_H

#include <QLabel>
#include <QString>
#include <QByteArray>
#include <setplanetimage.h>

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
    int GetX() const;
    int GetY() const;

    int GetWidth() const;
    int GetHeight() const;

    QString GetName() const;
private:
    friend class ManageSession;
    friend class Algorithms;

    void SetImg(QPixmap& pxm);
    QLabel *planet;
};

#endif // PLANET_H
