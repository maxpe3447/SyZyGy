#ifndef CLOCK_H
#define CLOCK_H
#include <QTimer>
#include <QLCDNumber>
#include <QDateTime>
#include <QObject>
#include <QDebug>
#include <QMainWindow>

class Clock : public QObject
{
public:
    Clock(QLCDNumber *dm,QLCDNumber *y, QLCDNumber *hm, QLCDNumber *s, QMainWindow* mainWindow);
    ~Clock();

    void Start();
    void Stop();

    bool GetisEnable() const;
    bool GetIsShowCurDate() const;
    QDate GetDate() const;

    void SetIsShowCurDate(bool flag);
    void SetDate(QDate);
private:
    QTimer* timer;
    QLCDNumber *dayAndMonth, *year, *hourAndMin, *second;
    QMainWindow *mw;
    QDate date;
    bool isEnable;
    bool isShowCurDate;
    void initSetCurrentTime();

public slots:
    void Tick();
    void DateSet(QDate* date);
};

#endif // CLOCK_H
