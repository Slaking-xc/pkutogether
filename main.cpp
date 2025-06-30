#include "mainwindow.h"
#include "mainmenu.h"
#include <QApplication>
#include <overall.h>
#include <QListWidget>
#include "person.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "saveonexit.h"  // 包含 SaveOnExit 头文件

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qRegisterMetaType<person*>("person*");

    // 创建人物和朋友
    //overall::me = new person;
      //overall::me->nickname = "myself";
      overall::NPC = new person("pkuTogather");
      overall::NPC->nickname="nickTogather";
      overall::settings->beginGroup("pkuTogather");
      overall::settings->setValue("nickname","nickTogather");
      overall::settings->endGroup();
      //overall::me->addFriend(overall::NPC);

    // 注册 activitys 类型
    qRegisterMetaType<activitys*>("activitys*");
    overall::activityList = new MainWindow;

    // 加载之前保存的活动信息
    overall::loadActivitiesFromFile();

    // 创建 SaveOnExit 对象，程序退出时自动保存
    //SaveOnExit saveOnExit;

    mainMenu home;
    home.show();

    return app.exec();
}
