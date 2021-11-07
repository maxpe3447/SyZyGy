#ifndef DEVELOPERSFORM_H
#define DEVELOPERSFORM_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class DevelopersForm;
}

class DevelopersForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit DevelopersForm(QWidget *parent = nullptr);
    ~DevelopersForm();

private:
    Ui::DevelopersForm *ui;
};

#endif // DEVELOPERSFORM_H
