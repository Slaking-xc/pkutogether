#ifndef ACTIVITYS_H
#define ACTIVITYS_H

#include <QObject>
#include <QString>
#include <QSharedData>
#include <QDateTime>
#include<QMetaType>


class activitysData : public QSharedData
{
public:
    int id;
    QString activityName;
    QString activityDetails;
    bool activityTag[5]; // 0运动，1桌游，2聚餐，3旅行，4其他
    static int s_nextId;
    QVector<QString> players={};//活动参与者
    QString posterName;


    activitysData() : id(++s_nextId) {
        for(int i=0; i<5; ++i) activityTag[i] = false;
    }

};

class activitys : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString details READ details WRITE setDetails NOTIFY detailsChanged)

public:
    explicit activitys(QObject *parent = nullptr);
    activitys(const activitys &other);
    ~activitys();


    activitys &operator=(const activitys &rhs);

    // 属性访问方法
    int id() const;
    QString name() const;
    QString details() const;
    QString posterName()const;
    QString playerIName(int i);
    int playerNum();



    // 设置方法
    void setName(const QString &name);
    void setDetails(const QString &details);
    void setId();
    void setNPC();
    void setPosterName(QString postrName);
    void addPlayer(QString playerName);

    // 标签操作方法
    Q_INVOKABLE bool getTag(int index) const;
    Q_INVOKABLE void setTag(int index, bool value);
    Q_INVOKABLE QString getTagName(int index) const;

signals:
    void nameChanged();
    void detailsChanged();
    void tagsChanged();

private:
    QSharedDataPointer<activitysData> data;
};

Q_DECLARE_METATYPE(activitys*)

#endif // ACTIVITYS_H

