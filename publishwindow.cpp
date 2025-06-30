#include "publishwindow.h"
#include "ui_publishwindow.h"
#include<QString>
#include<activitys.h>
#include<overall.h>
#include <QFile>
#include <QTextStream>
#include<QDebug>

publishWindow::publishWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::publishWindow)
{
    setFixedSize(1200, 800);
    ui->setupUi(this);
    QFile file(":/file/qss/style-publish.qss");/*QSS文件所在的路径*/
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();

}

publishWindow::~publishWindow()
{
    delete ui;


}

void publishWindow::on_publishButton_accepted()
{
    // 创建新的 activitys 对象
    activitys* tempAct = new activitys;
    tempAct->setName(ui->actName->toPlainText());
    tempAct->setDetails(ui->actDetail->toPlainText());

    bool tempTag[5] = {
        ui->checkBox_sports->isChecked(),
        ui->checkBox_boardgame->isChecked(),
        ui->checkBox_eatout->isChecked(),
        ui->checkBox_trip->isChecked(),
        ui->checkBox_others->isChecked()
    };
    for (int i = 0; i < 5; i++) {
        tempAct->setTag(i, tempTag[i]);
    }
    tempAct->setPosterName(overall::me->userName);
    tempAct->addPlayer(overall::me->nickname);
    qDebug()<<"overall::me->nickname"<<overall::me->nickname;
    // 将活动添加到后端
    overall::allActs.push_back(tempAct);

    // 创建 QListWidgetItem，并设置指针为 data
    QListWidgetItem* item = new QListWidgetItem(tempAct->name());
    item->setData(Qt::UserRole, QVariant::fromValue(tempAct));
    overall::activityList->activityList->addItem(item);
    //保存所有活动
    overall::saveActivitiesToFile();
    this->close();
}

