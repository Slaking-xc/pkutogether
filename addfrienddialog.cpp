#include "addfrienddialog.h"
#include "ui_addfrienddialog.h"
#include <overall.h>
addFriendDialog::addFriendDialog(const QString &currentUsername,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFriendDialog),
    m_currentUsername(currentUsername)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);

}

addFriendDialog::~addFriendDialog()
{
    delete ui;
}
QString addFriendDialog::getAddedFriend() const {
    return m_addedFriend;
}
void addFriendDialog::on_okButton_clicked() {
    QString targetUsername = ui->usernameEdit->text().trimmed();

    // 1. 检查输入是否为空
    if (targetUsername.isEmpty()) {
        ui->errorLabel->setText("用户名不能为空");
        ui->errorLabel->setVisible(true);
        return;
    }

    // 2. 检查是否是自己
    if (targetUsername == m_currentUsername) {
        ui->errorLabel->setText("不能添加自己为好友");
        ui->errorLabel->setVisible(true);
        return;
    }

    // 3. 检查用户名是否存在
    if (!overall::settings->childGroups().contains(targetUsername)) {
        ui->errorLabel->setText("用户名不存在");
        ui->errorLabel->setVisible(true);
        return;
    }

    // 4. 检查是否已经是好友
    overall::settings->beginGroup(m_currentUsername);
    QStringList friends = overall::settings->value("friends").toStringList();
    overall::settings->endGroup();

    if (friends.contains(targetUsername)) {
        ui->errorLabel->setText("该用户已经是你的好友");
        ui->errorLabel->setVisible(true);
        return;
    }

    // 5. 所有检查通过，记录成功添加的好友
    m_addedFriend = targetUsername;
    accept();  // 关闭对话框并返回 QDialog::Accepted
}
