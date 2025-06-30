#ifndef USER_H
#define USER_H

#include <QMainWindow>

namespace Ui {
class user;
}

class user : public QMainWindow
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    ~user();
    void loadUserData();
private slots:
    void on_pushButtonName_clicked();

    void on_pushButtonSignature_clicked();

    void on_pushButtonAvatar_clicked();

    void on_pushButtonActivity_clicked();

private:
    Ui::user *ui;
    void updateHobbyDisplay();
};

#endif // USER_H
