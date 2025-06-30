#ifndef ADDFRIENDDIALOG_H
#define ADDFRIENDDIALOG_H

#include <QDialog>

namespace Ui {
class addFriendDialog;
}

class addFriendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addFriendDialog(const QString &currentUsername,
                             QWidget *parent = nullptr);
    ~addFriendDialog();

    // 获取成功添加的好友用户名（仅在验证通过后有效）
    QString getAddedFriend() const;
    QString m_currentUsername;  // 当前用户
    QString m_addedFriend;      // 成功添加的好友
private slots:
    void on_okButton_clicked();
private:
    Ui::addFriendDialog *ui;
};

#endif // ADDFRIENDDIALOG_H
