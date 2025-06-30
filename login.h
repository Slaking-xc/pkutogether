#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <QSettings>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    static bool loggedin;
private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();
private:
    Ui::login *ui;
    //QSettings *settings;
    bool authenticate(const QString &username, const QString &password);
    bool registerUser(const QString &username, const QString &password);

};
#endif // LOGIN_H
