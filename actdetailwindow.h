#ifndef ACTDETAILWINDOW_H
#define ACTDETAILWINDOW_H

#include <QDialog>
#include<activitys.h>
namespace Ui {
class actDetailWindow;
}

class actDetailWindow : public QDialog
{
    Q_OBJECT

public:
    explicit actDetailWindow(QWidget *parent = nullptr);
    ~actDetailWindow();
    void setActdetails(activitys* act);

private slots:
    void on_signBntm_clicked();

private:
    Ui::actDetailWindow *ui;
};

#endif // ACTDETAILWINDOW_H
