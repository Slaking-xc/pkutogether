#include "person.h"
#include <QVector>
#include <overall.h>
person::person(const QString &username) : userName(username) {
    // 从 QSettings 加载好友列表
    overall::settings->beginGroup(userName);
    friends = overall::settings->value("friends").toStringList();
    friendNum = friends.size();
    overall::settings->endGroup();
}

bool person::isFriend(const QString &username) const {
    return friends.contains(username);
}

void person::addFriend(const QString &username) {
    if (username.isEmpty() || username == userName || isFriend(username)) {
        return;  // 无效或重复添加
    }

    friends.append(username);
    friendNum++;

    // 更新 QSettings
    overall::settings->beginGroup(userName);
    overall::settings->setValue("friends", friends);
    overall::settings->endGroup();

    // 双向关系：同时更新对方的好友列表
    overall::settings->beginGroup(username);
    QStringList theirFriends = overall::settings->value("friends").toStringList();
    theirFriends.append(userName);
    overall::settings->setValue("friends", theirFriends);
    overall::settings->endGroup();
}

void person::removeFriend(const QString &username) {
    if (friends.removeOne(username)) {
        friendNum--;

        // 更新 QSettings
        overall::settings->beginGroup(userName);
        overall::settings->setValue("friends", friends);
        overall::settings->endGroup();

        // 双向关系：从对方列表中移除自己
        overall::settings->beginGroup(username);
        QStringList theirFriends = overall::settings->value("friends").toStringList();
        theirFriends.removeOne(userName);
        overall::settings->setValue("friends", theirFriends);
        overall::settings->endGroup();
    }
}
