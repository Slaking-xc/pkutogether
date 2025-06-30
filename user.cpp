#include "user.h"
#include "ui_user.h"
#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include "mainwindow.h"
#include <QDateTime>
#include <QColor>
#include <QInputDialog>
#include <QDebug>
#include<QMessageBox>
#include<QFileDialog>
#include <overall.h>
#include <choosehobby.h>
user::user(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    loadUserData();
    updateHobbyDisplay(); // 初始化爱好显示
    QFile file(":/file/qss/style-user.qss");/*QSS文件所在的路径*/
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();
}

user::~user()
{
    delete ui;
}

void user::on_pushButtonName_clicked()
{
    bool ok;
    QString newNickname = QInputDialog::getText(this,
                                              tr("修改昵称"),
                                              tr("请输入新昵称:"),
                                              QLineEdit::Normal,
                                              this->ui->pushButtonName->text(), // 默认显示当前昵称
                                              &ok);

    if(ok && !newNickname.isEmpty()) {
        overall::me->nickname=newNickname;
        // 1. 更新按钮显示
        this->ui->pushButtonName->setText(newNickname);

        // 2. 打印调试信息
        qDebug() << "新昵称设置为:" << newNickname;
        overall::me->nickname=newNickname;

        // 3. 更新到全局设置（如果需要持久化）
        overall::settings->beginGroup(overall::me->userName);
        overall::settings->setValue("nickname", newNickname);
        overall::settings->endGroup();

        // 4. 可选：发送信号通知其他组件更新
        //emit nicknameChanged(newNickname);
    }
}

void user::on_pushButtonSignature_clicked()
{
    bool ok;
    QString newSignature = QInputDialog::getText(this,
                                              tr("修改个性签名"),
                                              tr("请输入个性签名:"),
                                              QLineEdit::Normal,
                                              this->ui->pushButtonName->text(), // 默认显示当前昵称
                                              &ok);

    if(ok && !newSignature.isEmpty()) {
        // 1. 更新按钮显示
        this->ui->pushButtonSignature->setText(newSignature);

        // 2. 打印调试信息
        qDebug() << "新个性签名设置为:" << newSignature;


        // 3. 更新到全局设置（如果需要持久化）
        overall::settings->beginGroup(overall::me->userName);
        overall::settings->setValue("signature", newSignature);
        overall::settings->endGroup();

        // 4. 可选：发送信号通知其他组件更新
        //emit nicknameChanged(newNickname);
    }
}

void user::on_pushButtonAvatar_clicked()
{
    // 1. 确认对话框
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        tr("更改头像"),
        tr("您要更改头像吗？"),
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply != QMessageBox::Yes) {
        qDebug() << "用户取消更改头像";
        return;
    }

    // 2. 获取图片路径（默认从上次目录打开）
    QString lastDir = overall::settings->value("LastAvatarDir", QDir::homePath()).toString();
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("选择头像图片"),
        lastDir,
        tr("图片文件 (*.png *.jpg *.jpeg *.bmp *.gif)")
    );

    if (fileName.isEmpty()) {
        qDebug() << "未选择文件";
        return;
    }

    // 3. 处理图片文件
    try {
        // 加载图片
        QPixmap pixmap(fileName);
        if (pixmap.isNull()) throw std::runtime_error("图片加载失败");

        // 缩放并显示（建议尺寸）
        QSize avatarSize(128, 128);

        ui->avatarLabel->setPixmap(pixmap.scaled(
            avatarSize,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        ));
        ui->avatarLabel->setAlignment(Qt::AlignCenter);

        // 4. 持久化存储（两种方案任选）
        // 方案A：存储图片路径
        overall::settings->beginGroup(overall::me->userName);
        overall::settings->setValue("avatarPath", fileName);
        overall::settings->setValue("LastAvatarDir", QFileInfo(fileName).path());
        overall::settings->endGroup();

        // 方案B：存储图片数据（Base64编码）
        /*
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");
        overall::settings->setValue("avatarData", imageData.toBase64());
        */

        qDebug() << "头像更新成功:" << fileName;
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, tr("错误"), tr("头像加载失败: %1").arg(e.what()));
        qWarning() << "头像处理错误:" << e.what();
    }
}
void user::loadUserData()
{

        // 确保有当前用户
        if (!overall::me) return;

        // 从设置加载用户数据
        overall::settings->beginGroup(overall::me->userName);
        ui->pushButtonID->setText(overall::me->userName);
        // 1. 加载昵称
        QString nickname = overall::settings->value("nickname","未设置昵称").toString();
        ui->pushButtonName->setText(nickname);

        // 2. 加载个性签名
        QString signature = overall::settings->value("signature", "未设置签名").toString();
        ui->pushButtonSignature->setText(signature);

        // 3. 加载头像
        QString avatarPath = overall::settings->value("avatarPath").toString();
        if (!avatarPath.isEmpty()) {
            QPixmap pixmap(avatarPath);
            if (!pixmap.isNull()) {
                ui->avatarLabel->setPixmap(pixmap.scaled(
                    ui->avatarLabel->size(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation
                ));
            }
        }

        overall::settings->endGroup();

}

void user::on_pushButtonActivity_clicked()
{
    chooseHobby dialog(this);
    if(dialog.exec() == QDialog::Accepted) {
        QStringList hobbies = dialog.getSelectedHobbies();

        // 保存到设置
        overall::settings->beginGroup(overall::me->userName);
        overall::settings->setValue("hobbies", hobbies.join(","));
        overall::settings->endGroup();

        // 更新显示
        updateHobbyDisplay();
    }
}
void user::updateHobbyDisplay()
{
    // 从设置加载爱好
    overall::settings->beginGroup(overall::me->userName);
    QString hobbiesStr = overall::settings->value("hobbies").toString();
    overall::settings->endGroup();

    QStringList hobbies = hobbiesStr.split(",");

    // 更新显示 - 两个标签分别显示
    if(hobbies.isEmpty()) {
        ui->hobbyLabel1->setText("未选择爱好");
        ui->hobbyLabel2->setText("");
    }
    else {
        // 第一个爱好显示在第一个标签
        ui->hobbyLabel1->setText(hobbies.size() > 0 ? hobbies[0] : "");

        // 第二个爱好显示在第二个标签
        ui->hobbyLabel2->setText(hobbies.size() > 1 ? hobbies[1] : "");
    }
}
