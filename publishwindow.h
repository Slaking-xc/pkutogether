#ifndef PUBLISHWINDOW_H
#define PUBLISHWINDOW_H

#include <QDialog>
#include<QLabel>
#include<QTextEdit>
#include<QCheckBox>
#include<ui_publishwindow.h>

namespace Ui {
class publishWindow;
}

class publishWindow : public QDialog
{
    Q_OBJECT

public:
    explicit publishWindow(QWidget *parent = nullptr);
    ~publishWindow();



private slots:
    void on_publishButton_accepted();

private:
    Ui::publishWindow *ui;

};

#endif // PUBLISHWINDOW_H
