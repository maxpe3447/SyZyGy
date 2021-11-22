#ifndef PLANETINFOFORM_H
#define PLANETINFOFORM_H

#include <QMainWindow>
#include <QIcon>
#include "planetinfodata.h"

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
    void GetOptionsAndInfo(PlanetInfoData* data);
};

#endif // PLANETINFOFORM_H
