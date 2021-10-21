#ifndef PLANETINFOFORM_H
#define PLANETINFOFORM_H

#include <QMainWindow>

namespace Ui {
class PlanetInfoForm;
}

class PlanetInfoForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlanetInfoForm(QWidget *parent = nullptr);
    ~PlanetInfoForm();

private:
    Ui::PlanetInfoForm *ui;
public slots:
    void GetOptionsAndInfo(QString);
};

#endif // PLANETINFOFORM_H
