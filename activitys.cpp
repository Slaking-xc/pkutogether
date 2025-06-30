#include "activitys.h"
#include <QDebug>
#include<QMetaType>
#include<overall.h>
// 初始化静态变量
int activitysData::s_nextId = 0;

activitys::activitys(QObject *parent) : QObject(parent), data(new activitysData)
{
    qRegisterMetaType<activitys>("activitys");
}

activitys::activitys(const activitys &other) : QObject(other.parent()), data(other.data)
{
}

activitys::~activitys()
{
}

activitys &activitys::operator=(const activitys &rhs)
{
    if (this != &rhs) {
        data.operator=(rhs.data);
    }
    return *this;
}

//访问属性的函数
int activitys::id() const { return data->id; }

QString activitys::name() const { return data->activityName; }

QString activitys::details() const { return data->activityDetails; }

QString activitys::posterName()const{return data->posterName;}

//设置属性的函数
void activitys::setName(const QString &name)
{
    if (data->activityName != name) {
        data->activityName = name;
        emit nameChanged();
    }
}

void activitys::setDetails(const QString &details)
{
    if (data->activityDetails != details) {
        data->activityDetails = details;
        emit detailsChanged();
    }
}

bool activitys::getTag(int index) const
{
    if (index >= 0 && index < 5) {
        return data->activityTag[index];
    }
    qWarning() << "Invalid tag index:" << index;
    return false;
}

void activitys::setPosterName(QString postrName){
    data->posterName=postrName;
}

void activitys::setTag(int index, bool value)
{
    if (index >= 0 && index < 5) {
        if (data->activityTag[index] != value) {
            data->activityTag[index] = value;
            emit tagsChanged();
        }
    } else {
        qWarning() << "Invalid tag index:" << index;
    }
}

QString activitys::getTagName(int index) const
{
    static const QString tagNames[] = {
        tr("运动"), tr("桌游"), tr("聚餐"), tr("旅行"), tr("其他")
    };

    if (index >= 0 && index < 5) {
        return tagNames[index];
    }
    return tr("未知");
}

//添加游戏人
void activitys:: addPlayer(QString playerName){
    data->players.push_back(playerName);
}

//参与游戏的人数
int activitys::playerNum(){
    return data->players.size();
};

//第i个人的名字
QString  activitys::playerIName(int i){
    return data-> players[i];
}


