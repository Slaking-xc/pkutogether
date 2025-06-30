#ifndef OVERALL_H
#define OVERALL_H

#include<mainwindow.h>
#include<QListWidget>
#include<activitys.h>
#include<QVector>
#include "person.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QSettings>
class overall
{
public:
    overall();
    static MainWindow* activityList;//按钮必须依赖于父目录activityList，在MainWindow里创建
    static QVector<activitys*> allActs;
    static person* me;
    static person* NPC;

    static void loadActivitiesFromFile() ;
    static void saveActivitiesToFile();

    static QSettings* settings;
    static int allPersonNum;
    static QVector<person*> allPerson;
};

#endif // OVERALL_H
