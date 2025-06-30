#include "actdetailwindow.h"
#include "ui_actdetailwindow.h"
#include<activitys.h>
#include <QFile>
#include <QTextStream>
#include<QDebug>
#include<QMessageBox>
#include<overall.h>

actDetailWindow::actDetailWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::actDetailWindow)
{
    ui->setupUi(this);

    QFile file(":/file/qss/style-activitydetail.qss");/*QSS文件所在的路径*/
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();





}

actDetailWindow::~actDetailWindow()
{
    delete ui;
}

void actDetailWindow::setActdetails(activitys* act){
    ui->detailText->setText(act->details());
    QString tempTitle;
    ui->uniTitle->setText(act->name());

    QString tempTag;
    for(int i=0;i<5;i++){
        if(act->getTag(i)){
            tempTag+="【"+act->getTagName(i)+"】";
        }
    }
    ui->tagIndetail->setText(tempTag);
    for(int i=0;i<act->playerNum();i++){
        if(!act->playerIName(i).isNull()){
            ui->listWidget->addItem(act->playerIName(i));
            qDebug()<<"act->playerIName(i)"<<act->playerIName(i);
        }
    }

}



//点击报名活动
void actDetailWindow::on_signBntm_clicked() {
    // 安全检查
    if (!ui->uniTitle || !ui->detailText || !overall::me) {
        QMessageBox::critical(this, "错误", "初始化异常");
        return;
    }

    QString title = ui->uniTitle->text();
    QString details = ui->detailText->toPlainText();
    QString nickname = overall::me->nickname;

    // 查找活动
    activitys* tempact = nullptr;
    for (int i = 0; i < overall::allActs.size(); ++i) {
        if (overall::allActs[i] &&
            overall::allActs[i]->name() == title &&
            overall::allActs[i]->details() == details) {
            tempact = overall::allActs[i];
            break;
        }
    }

    if (!tempact) {
        QMessageBox::critical(this, "错误", "未找到活动");
        return;
    }

    // 检查是否已报名
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        if (ui->listWidget->item(i)->text() == nickname) {
            QMessageBox::information(this, "提示", "您已报名");
            return;
        }
    }

    // 确认报名
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "报名活动", "确定要报名这个活动吗?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        tempact->addPlayer(nickname);

        try {
            overall::saveActivitiesToFile();
            QMessageBox::information(this, "祝贺你", "报名成功");
            overall::saveActivitiesToFile();
            QListWidgetItem* newItem = new QListWidgetItem(nickname);
            ui->listWidget->addItem(newItem);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "错误", QString("保存失败: %1").arg(e.what()));
        }
    }
}
