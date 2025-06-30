#include "frienddetaildialog.h"
#include "ui_frienddetaildialog.h"
#include "overall.h"
#include <QMessageBox>
#include <QSettings>
#include <QFile>
#include <QTextStream>

friendDetailDialog::friendDetailDialog(const QString &username, QWidget *parent) :
    QDialog(parent),
    m_username(username),  // 存储用户名
    ui(new Ui::friendDetailDialog)
{
    ui->setupUi(this);


    QFile file(":/file/qss/style-frienddetail.qss");/*QSS文件所在的路径*/
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();
    setWindowTitle("好友详情");

    // 从全局settings读取好友信息
    overall::settings->beginGroup(m_username);
    QString nickname = overall::settings->value("nickname", m_username).toString();
    overall::settings->endGroup();
    // 从设置加载爱好
    overall::settings->beginGroup(m_username);
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
    // 设置UI显示
    ui->nicknameLabel->setText(nickname);
    // 设置UI显示【ID】
    ui->IDLabel->setText(m_username);
    // 设置【头像】
    overall::settings->beginGroup(m_username);
    QString avatarPath = overall::settings->value("avatarPath").toString();
    if(!avatarPath.isEmpty()) {
        QPixmap avatar(avatarPath);
        if(!avatar.isNull()) {
            ui->avatarLabel->setPixmap(
                avatar.scaled(ui->avatarLabel->size(),
                            Qt::KeepAspectRatio,
                            Qt::SmoothTransformation)
            );
        }
    }
    // 设置【签名】
    QString signature = overall::settings->value("signature", "没写签名捏").toString();
    ui->signatureLabel->setText(signature);
    overall::settings->endGroup();

}

friendDetailDialog::~friendDetailDialog()
{
    delete ui;
}

void friendDetailDialog::on_deleteButton_clicked()
{
    // 再次从settings获取当前昵称（确保显示最新）
    overall::settings->beginGroup(m_username);
    QString currentNickname = overall::settings->value("nickname", m_username).toString();
    overall::settings->endGroup();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
                                QString("确定要删除好友 %1 吗?").arg(currentNickname),
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 从当前用户的好友列表中删除（通过username操作）
        overall::settings->beginGroup(overall::me->userName);
        QStringList friends = overall::settings->value("friends").toStringList();
        friends.removeAll(m_username);  // 移除目标用户
        overall::settings->setValue("friends", friends);
        overall::settings->endGroup();

        // 可选：双向删除（从对方好友列表也移除自己）
        overall::settings->beginGroup(m_username);
        QStringList theirFriends = overall::settings->value("friends").toStringList();
        theirFriends.removeAll(overall::me->userName);
        overall::settings->setValue("friends", theirFriends);
        overall::settings->endGroup();

        QMessageBox::information(this, "成功", "好友已删除");
        emit accepted();  // 发送信号通知外部刷新
        close();
    }
}
