#ifndef DEVELOPERSFORM_H
#define DEVELOPERSFORM_H

#include <QMainWindow>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class DevelopersForm;
}

class DevelopersForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit DevelopersForm(QWidget *parent = nullptr);
    ~DevelopersForm();

private slots:
    void on_pbAsyaLink_clicked();
    void on_pbMaxLink_clicked();
    void on_pbKateLink_clicked();

private:
    Ui::DevelopersForm *ui;
};

#endif // DEVELOPERSFORM_H
