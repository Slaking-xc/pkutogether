#include "login.h"
#include "ui_login.h"
#include "user.h"
#include <QFile>
#include <QTextStream>
#include<overall.h>
#include <QDebug>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("用户登录");

    // 初始化设置存储
    //settings = new QSettings("MyCompany", "MyApp", this);

    // 密码输入框设置为密码模式
    ui->passwordEdit->setEchoMode(QLineEdit::Password);

    // 隐藏错误提示
    ui->errorLabel->setVisible(false);

    QFile file(":/file/qss/style-login.qss");/*QSS文件所在的路径*/
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();


}
bool login::loggedin = 0;
login::~login()
{
    delete ui;
}

bool login::authenticate(const QString &username, const QString &password)
{
    if (!overall::settings->childGroups().contains(username)) {
        qDebug() << "用户名不存在！";
        return false;
    }
    // 进入该用户的分组
    overall::settings->beginGroup(username);

    // 获取存储的密码（实际应用应对比哈希值）
    QString storedPassword = overall::settings->value("password").toString();

    bool isCorrect = (password == storedPassword);

    overall::settings->endGroup();

    return isCorrect;
    /*
    // 从设置中获取存储的密码
    QString storedPassword = settings->value(username).toString();

    // 验证密码
    return !storedPassword.isEmpty() && storedPassword == password;*/
}

bool login::registerUser(const QString &username, const QString &password)
{
    // 检查用户名是否已存在
    if (overall::settings->childGroups().contains(username)) {
        return false;
    }

    // 存储用户名和密码
   /* overall::allPersonNum++;
    overall::allPerson.append(new person);
    overall::allPerson[overall::allPersonNum]->userName = username;
    overall::allPerson[overall::allPersonNum]->addFriend(overall::NPC);*/

    overall::settings->beginGroup(username);
    overall::settings->setValue("password", password);
    //overall::settings->setValue("ptrIndex", overall::allPersonNum);
    overall::settings->endGroup();
    return true;
}

void login::on_loginButton_clicked()
{
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        ui->errorLabel->setText("用户名和密码不能为空");
        ui->errorLabel->setVisible(true);
        return;
    }

    if (authenticate(username, password)) {
        // 登录成功，打开副菜单
        loggedin = 1;
        overall::settings->beginGroup(username);
        //int index = overall::settings->value("ptrIndex").toInt();
        overall::me = new person(username);
        overall::settings->endGroup();

        this->close();
    } else {
        ui->errorLabel->setText("用户名或密码错误");
        ui->errorLabel->setVisible(true);
    }
}

void login::on_registerButton_clicked()
{
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        ui->errorLabel->setText("用户名和密码不能为空");
        ui->errorLabel->setVisible(true);
        return;
    }

    if (registerUser(username, password)) {
        QMessageBox::information(this, "注册成功", "用户注册成功，请登录");
        ui->passwordEdit->clear();
        ui->usernameEdit->clear();

    } else {
        ui->errorLabel->setText("用户名已存在");
        ui->errorLabel->setVisible(true);
    }
}
