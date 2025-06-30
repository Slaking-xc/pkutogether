#include "social.h"
#include "ui_social.h"
#include "overall.h"
#include <QListWidgetItem>
#include <QListWidget>
#include "frienddetaildialog.h"
#include <QDialog>
#include <QDebug>
#include <QWidget>
#include "addfrienddialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
Social::Social(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Social)
{
    setFixedSize(1200, 800);
    ui->setupUi(this);
    QFile file(":/file/qss/style-social.qss");/*QSS文件所在的路径*/
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();


    refreshFriendList();
    connect(ui->becomeFriend, &QPushButton::clicked,
                this, &Social::on_becomeFriend_clicked);
    connect(ui->friendListWidget, &QListWidget::itemDoubleClicked,
            this, &Social::onFriendDoubleClicked);





}

Social::~Social()
{
    delete ui;
}
/*void Social::refreshFriendList()
{
    // 清空现有列表
    ui->friendListWidget->clear();

    // 检查当前用户是否有效
   //if (!m_currentUser) {
     //   qWarning() << "Current user is null!";
       // return;
    //}

    // 根据好友数量添加列表项
    for (int i = 0; i < overall::me->friendNum; ++i) {
        person* friendPtr = overall::me->friends[i];
        if (friendPtr) {

            QListWidgetItem* item = new QListWidgetItem;

            QString friendInfo = QString("%1 (ID: %2)")
                                .arg(friendPtr->nickname)
                                .arg(friendPtr->userName);
            item->setText(friendInfo);
            item->setData(Qt::UserRole, QVariant::fromValue(friendPtr));
            // 可以设置更多属性，如图标等!!!
            // item->setIcon(...);

            // 将用户指针存储在项中!!!
            //item->setData(Qt::UserRole, QVariant::fromValue(friendPtr));

            // 添加到列表
            ui->friendListWidget->addItem(item);
        }
        else
            break;
    }

    // 可选：如果没有好友，显示提示信息
   if (m_currentUser->getFriendsNum() == 0) {
        QListWidgetItem* item = new QListWidgetItem("暂无好友");
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled); // 禁用该项
        ui->friendListWidget->addItem(item);
    }*/
void Social::refreshFriendList()
{
    // 清空现有列表
    ui->friendListWidget->clear();

    // 从全局settings获取当前用户的好友列表
    overall::settings->beginGroup(overall::me->userName);
    QStringList friends = overall::settings->value("friends").toStringList();
    overall::settings->endGroup();

    // 如果没有好友，显示提示信息
    if (friends.isEmpty()) {
        QListWidgetItem* item = new QListWidgetItem("暂无好友");
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled); // 禁用该项
        ui->friendListWidget->addItem(item);
        return;
    }

    // 遍历好友列表并添加到UI
    for (const QString& friendName : friends) {
        // 从settings获取好友详细信息
        overall::settings->beginGroup(friendName);
        QString nickname = overall::settings->value("nickname").toString(); // 默认使用用户名
        // 可以获取更多好友信息，如头像等
        // QByteArray avatarData = settings.value("avatar").toByteArray();
        overall::settings->endGroup();

        QListWidgetItem* item = new QListWidgetItem;
        QString friendInfo = QString("%1(nickname:%2)").arg(friendName).arg(nickname);
        item->setText(friendInfo);

        // 存储用户名而不是指针
        item->setData(Qt::UserRole, friendName);

        ui->friendListWidget->addItem(item);
    }
}
void Social::onFriendDoubleClicked(QListWidgetItem* item)
{
    // 1. 检查是否是可选项
    if (!(item->flags() & Qt::ItemIsSelectable)) {
        return;
    }

    // 2. 直接传递用户名（UserRole存储的是QString）
    QString username = item->data(Qt::UserRole).toString();
    if (username.isEmpty()) {
        qDebug() << "Invalid username in list item";
        return;
    }

    // 3. 创建对话框（仅传username）
    friendDetailDialog* dialog = new friendDetailDialog(username, this);
    dialog->exec();

    // 4. 可选：关闭后刷新
    refreshFriendList();
}





   /* // 从列表项中获取存储的好友指针
    person* friendPtr = item->data(Qt::UserRole).value<person*>();
    if (!friendPtr) {
        qDebug() << "Invalid friend pointer in list item";
        return;
    }

    // 创建并显示好友详情对话框
    friendDetailDialog* dialog = new friendDetailDialog(friendPtr, this);
    dialog->exec();

    // 对话框关闭后可以添加刷新逻辑
    refreshFriendList();*/


void Social::on_becomeFriend_clicked()
{
    // 1. 弹出对话框（传入当前用户名）
    qDebug()<<"here";
    addFriendDialog dialog(overall::me->userName, this);
    if (dialog.exec() != QDialog::Accepted) {
        return;  // 用户取消操作
    }

    // 2. 获取成功添加的好友用户名
    QString newFriend = dialog.getAddedFriend();
    if (!overall::settings->childGroups().contains(newFriend)) {
        QMessageBox::warning(this, "错误", QString("用户 %1 不存在！").arg(newFriend));
        return;
    }
    // 3. 更新好友列表
    overall::settings->beginGroup(overall::me->userName);
    QStringList friends = overall::settings->value("friends").toStringList();
    friends.append(newFriend);
    overall::settings->setValue("friends", friends);
    overall::settings->endGroup();

    // 4. 提示添加成功
    QMessageBox::information(this, "成功", QString("已添加 %1 为好友！").arg(newFriend));

    refreshFriendList();
}
