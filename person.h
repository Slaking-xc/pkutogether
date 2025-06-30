#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <QStringList>
#include <QLineEdit>
#include <QVector>
#include <QObject>
#include <QMetaType>
class person
{

public:
    person(const QString &username);
    int age=0;
    int gender=0;       //0女1男
    QString userName = "NULL";
    QString password = "NULL";
    QString signature = "NULL";
    QString nickname = "NULL";

    int friendNum = 0;
    void init();

    //QVector<person*> friends;
    bool isFriend(const QString &username) const;
    void addFriend(const QString &username);
    void removeFriend(const QString &username);
//private:
    QStringList friends;


};
Q_DECLARE_METATYPE(person*)  // 注册指针类型
#endif // PERSON_H
