#include "overall.h"
#include "person.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QDebug>
#include<QCoreApplication>

overall::overall()
{

}


MainWindow* overall::activityList=nullptr;
QVector<activitys*> overall::allActs={nullptr};
person* overall::me = nullptr;
person* overall::NPC = nullptr;
int overall::allPersonNum = 0;
QVector<person*> overall::allPerson={nullptr};
QSettings* overall::settings = new QSettings("MyCompany","MyApp");
void overall::saveActivitiesToFile() {
    // 获取程序当前目录（.pro文件所在的目录）
    QString currentDir = QCoreApplication::applicationDirPath();  // 使用应用程序的目录路径
    qDebug() << "Current directory: " << currentDir;

    // 拼接文件夹路径（saveActivitys 文件夹）
    QString folderPath = currentDir + "/saveActivitys";

    // 检查文件夹是否存在，不存在则创建
    QDir dir(folderPath);
    if (!dir.exists()) {
        if (!dir.mkpath(folderPath)) {
            qDebug() << "Failed to create directory: " << folderPath;
            return;
        }
    }

    // 拼接文件完整路径（保存的 JSON 文件）
    QString filePath = folderPath + "/activities.json";
    qDebug() << "Saving to file: " << filePath;

    // 检查 overall::allActs 是否为空
    if (overall::allActs.isEmpty()) {
        qDebug() << "No activities to save.";
        return;
    }

    // 创建 JSON 数据
    QJsonArray activitiesArray;

    // 确保 overall::allActs 中的每个元素都是有效指针
    for (auto* act : overall::allActs) {
        if (act == nullptr) {
            qDebug() << "Skipping invalid activity pointer.";
            continue;  // 跳过无效的活动
        }

        QJsonObject activityObj;
        activityObj["name"] = act->name();
        activityObj["details"] = act->details();
        activityObj["posterName"] = act->posterName();  // 添加 posterName 到 JSON 中

        // 保存 players 列表
        QJsonArray playersArray;
        for (int i=0;i<act->playerNum();i++) {
            playersArray.append(act->playerIName(i));
        }
        activityObj["players"] = playersArray;  // 保存 players 到 JSON

        // 假设活动有标签等信息
        QJsonArray tagsArray;
        for (int i = 0; i < 5; ++i) {
            tagsArray.append(act->getTag(i));
        }
        activityObj["tags"] = tagsArray;

        activitiesArray.append(activityObj);
    }

    // 使用 QJsonDocument 将活动列表转换为 JSON 格式
    QJsonDocument doc(activitiesArray);

    // 将 JSON 数据写入文件
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing: " << filePath;
        qDebug() << "Error: " << file.errorString();  // 输出具体的错误信息
        return;
    }

    file.write(doc.toJson());
    file.close();
    qDebug() << "Activities saved to: " << filePath;
}

void overall::loadActivitiesFromFile() {
    // 获取程序实际的执行目录路径（.pro 文件所在的目录）
    QString currentDir = QCoreApplication::applicationDirPath();
    qDebug() << "Application directory: " << currentDir;

    // 拼接文件夹路径（saveActivitys 文件夹）
    QString folderPath = currentDir + "/saveActivitys";

    // 拼接文件完整路径（活动 JSON 文件）
    QString filePath = folderPath + "/activities.json";
    qDebug() << "Loading file from: " << filePath;

    // 检查文件是否存在
    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << "File not found: " << filePath;
        return;
    }

    // 打开文件读取内容
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            QJsonArray activitiesArray = doc.array();
            for (const QJsonValue& value : activitiesArray) {
                if (value.isObject()) {
                    QJsonObject activityObj = value.toObject();
                    activitys* newAct = new activitys;
                    newAct->setName(activityObj["name"].toString());
                    newAct->setDetails(activityObj["details"].toString());

                    // 确保 posterName 被正确恢复
                    if (activityObj.contains("posterName")) {
                        newAct->setPosterName(activityObj["posterName"].toString());  // 设置 posterName，假设你已经在 setPosterName 中处理好了
                    } else {
                        qDebug() << "PosterName not found in JSON for activity: " << newAct->name();
                    }

                    // 恢复 players 列表
                    if (activityObj.contains("players")) {
                        QJsonArray playersArray = activityObj["players"].toArray();
                        QVector<QString> playersList;
                        for (const QJsonValue& playerValue : playersArray) {
                            playersList.append(playerValue.toString());
                        }

                        for(int i=0;i<playersList.size();i++){
                            newAct->addPlayer(playersList[i]);
                        }

                    }

                    //恢复tag列表
                    QJsonArray tagsArray = activityObj["tags"].toArray();
                    for (int i = 0; i < tagsArray.size(); ++i) {
                        newAct->setTag(i, tagsArray[i].toBool());
                    }
                    overall::allActs.push_back(newAct);
                }
            }
        }
        file.close();
        qDebug() << "Activities loaded from: " << filePath;
    } else {
        qDebug() << "Failed to open file for reading: " << filePath;
    }
}
