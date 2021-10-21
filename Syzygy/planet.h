#ifndef PLANET_H
#define PLANET_H

#include <QLabel>
#include <QString>


class Planet
{
public:
    Planet();
    Planet(QLabel* pLabel);
    Planet(QLabel* pLabel, QString img);
    Planet(QLabel* pLabel, QString img, int width, int height);

    void SetParams(QLabel* pLabel, QString img);
    void SetPos(int x, int y);
    int GetX();
    int GetY();
    int GetWidth();
    int GetHeight();
    QString GetName() const;
private:
    friend class ManageSession;
    QLabel *planet;
};

#endif // PLANET_H
