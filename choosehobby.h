#ifndef CHOOSEHOBBY_H
#define CHOOSEHOBBY_H

#include <QDialog>

namespace Ui {
class chooseHobby;
}

class chooseHobby : public QDialog
{
    Q_OBJECT

public:
    explicit chooseHobby(QWidget *parent = nullptr);
    ~chooseHobby();
    QStringList getSelectedHobbies() const;
private slots:
    //void on_buttonBox_accepted();

    void on_confirmButton_clicked();

    //void on_pushButton_clicked();

private:
    Ui::chooseHobby *ui;
    QStringList selectedHobbies;
};

#endif // CHOOSEHOBBY_H
