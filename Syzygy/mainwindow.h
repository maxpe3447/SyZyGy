#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDateTime>
#include <QIcon>
#include "planet.h"
#include "clock.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbMenu_clicked();
    void Tick_of_clock();

private:
    Ui::MainWindow *ui;
    void initPlanetsImage();
    void initTime();
    void initMenuButton();

    Clock* clock;
    Planet earth, jupiter, mars, mercury, neptune, saturn, sun, uranus, venus;
};
#endif // MAINWINDOW_H
