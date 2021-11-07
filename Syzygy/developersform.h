#ifndef DEVELOPERSFORM_H
#define DEVELOPERSFORM_H

#include <QWidget>

namespace Ui {
class DevelopersForm;
}

class DevelopersForm : public QWidget
{
    Q_OBJECT

public:
    explicit DevelopersForm(QWidget *parent = nullptr);
    ~DevelopersForm();

private:
    Ui::DevelopersForm *ui;
};

#endif // DEVELOPERSFORM_H
