#ifndef SAVEONEXIT_H
#define SAVEONEXIT_H

#include <QObject>
#include <QCoreApplication>
#include "overall.h"

class SaveOnExit : public QObject {
    Q_OBJECT

public:
    SaveOnExit() {
        // 连接程序退出信号与保存函数
        connect(qApp, &QCoreApplication::aboutToQuit, this, &SaveOnExit::onAboutToQuit);
    }

private slots:
    void onAboutToQuit() {
        // 程序退出时保存活动信息
        overall::saveActivitiesToFile();
    }
};

#endif // SAVEONEXIT_H
