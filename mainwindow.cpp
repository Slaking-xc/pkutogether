#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include "mainwindow.h"
#include <QDateTime>
#include <QColor>
#include <QString>
#include<publishwindow.h>
#include<activitys.h>
#include<overall.h>
#include<QDebug>
#include<QMessageBox>
#include<actdetailwindow.h>
#include<QMenu>
#include<QInputDialog>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("PKU To-gather");
    setFixedSize(1200, 800);
    // 主布局
    QWidget *centralWidget = new QWidget(this);

    setStyleSheet(
            "MainWindow {"
            "   background-image: url(:/file/background-5.png);"
            "   background-position: center;"
            "   background-repeat: no-repeat;"
            "   background-attachment: fixed;"
            "}"
        );
    centralWidget->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(40);          // 控件间距
    mainLayout->setContentsMargins(80, 20, 80, 20);  // 边距（左、上、右、下）

    titleLabel = new QLabel("总览", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: rgb(181, 136, 99); margin: 15px;background: transparent;"
                              "   font-family: '楷体', 'KaiTi', 'STKaiti';"  // 设置楷体
                              );
    mainLayout->addWidget(titleLabel);

    // 活动列表
    activityList = new QListWidget(this);
    for(int i=0;i<overall::allActs.size();i++){
        if (overall::allActs[i] == nullptr) continue;



        QString tempName=overall::allActs[i]->name();
        /*
        for(int j=0;j<5;j++){
            if(overall::allActs[i]->getTag(j)){
                tempName+="【"+overall::allActs[i]->getTagName(j)+"】";
            }
        }*/
        QListWidgetItem*tempItem= new QListWidgetItem(tempName);
        activitys* actPtr=overall::allActs[i];
        tempItem->setData(Qt::UserRole, QVariant::fromValue(actPtr));
        activityList->addItem(tempItem);

    }
    activityList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    activityList->setStyleSheet(
        // 设置 QListWidget 主控件的样式
        "QListWidget {"
        "   font-size: 21px;"                  // 设置列表整体字体大小
                "   font-family: '楷体', 'KaiTi', 'STKaiti';"  // 设置楷体
        "   color: #333;"                      // 设置默认文本颜色(深灰色)
        // 使用渐变背景(从上到下渐变色)
                "background: transparent;"
        "   background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f9f9f9, stop:1 #e8e8e8);"
        "   border: 2px solid #dcdcdc;"        // 设置2像素宽的浅灰色边框
        "   border-radius: 10px;"              // 设置10像素圆角
        "   padding: 5px;"                     // 设置内边距为5像素
                "   outline: 0;"
        "}"

        // 设置列表项的默认样式
        "QListWidget::item {"
        "   color: #333;"                      // 设置项文本颜色(深灰色)
        "   background-color: rgb(222, 196, 160);"     // 设置项背景
        "   padding: 12px 15px;"               // 设置项内边距(上下12px，左右15px)
        "   border-bottom: 1px solid #e0e0e0;" // 设置项底部1像素浅灰色边框(分隔线)
        "   border-radius: 5px;"               // 设置项圆角5像素
                "   outline: 0;"

        "}"

        // 设置鼠标悬停在项上时的样式
        "QListWidget::item:hover {"
        // 设置半透明红色背景(rgba最后0.1表示10%透明度)
        "   background-color: rgb(210, 180, 140);"
                "   outline: 0;"
        "}"

        // 设置选中项的样式
        "QListWidget::item:selected {"
        "   background-color: rgb(181, 136, 99);"        // 设置选中项背景
        "   color: white;"                     // 设置选中项文本为白色
        "   border: none;"                     // 移除选中项的边框
        "   outline: 0;"
                "}"



            // 或者更彻底地移除所有焦点状态下的虚线框
            "QListWidget::item:focus {"
            "   outline: 0;"
            "}"

        "QScrollBar:vertical {"
            "   border: none;"
            "   background: #f1f1f1;"
            "   width: 12px;"                      // 增加宽度确保可见
            "   margin: 2px;"                      // 添加外边距
            "   border-radius: 6px;"
            "}"
            "QScrollBar::handle:vertical {"
            "   background: #c1c1c1;"
            "   min-height: 30px;"                 // 增加最小高度
            "   border-radius: 6px;"
            "}"
            // 恢复箭头按钮（可选）
            "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
            "   height: 15px;"                     // 恢复箭头高度
            "   background: #f1f1f1;"
            "}"
            // 确保滚动条在需要时显示
            "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
            "   background: none;"
            "}"
    );

    mainLayout->addWidget(activityList);

    // 按钮布局
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        publishButton = new QPushButton("发布活动", this);

        // 设置按钮样式
        publishButton->setStyleSheet(
            "QPushButton {"
            "   background-color: rgb(210, 180, 140);"
            "   color: white;"
            "   border: none;"
            "   padding: 20px 40px;"
            "   border-radius: 4px;"
            "   font-size: 25px;"
                    "   font-family: '楷体', 'KaiTi', 'STKaiti';"  // 设置楷体
            "}"
            "QPushButton:hover {"
            "   background-color: rgb(181, 136, 99);"
            "}"
        );



        // 创建容器widget和布局
        QWidget *buttonContainer = new QWidget(this);
        buttonContainer->setStyleSheet(
            "QWidget {"
            "   background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f9f9f9, stop:1 #e8e8e8);"
            "   border: 2px solid #dcdcdc;"  // 浅灰色边框
            "   border-radius: 10px;"       // 圆角
            "   padding: 30px 25px;"             // 内边距
            "}"
        );

        QHBoxLayout *containerLayout = new QHBoxLayout(buttonContainer);
        containerLayout->setContentsMargins(30, 20, 30, 20);  // 左, 上, 右, 下
        containerLayout->addSpacing(25);
        containerLayout->addWidget(publishButton);
        containerLayout->addSpacing(20);
        containerLayout->addSpacing(25);

        buttonLayout->addWidget(buttonContainer);
        mainLayout->addSpacing(20);
        mainLayout->addLayout(buttonLayout);
        mainLayout->addSpacing(70);

    // 状态栏（显示时间）
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(1000); // 每秒更新一次时间
    updateTime(); // 初始化时间

    // 按钮点击事件
    connect(publishButton, &QPushButton::clicked, this, &MainWindow::on_Publish_Clicked);
    //connect(registerButton, &QPushButton::clicked, this, &MainWindow::on_Register_Clicked);
    connect(activityList, &QListWidget::itemDoubleClicked, this, &MainWindow::on_ActivityItem_DoubleClicked);

    activityList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(activityList, &QListWidget::customContextMenuRequested, this, &MainWindow::onActivityItemContextMenu);

    // 设置主窗口的中心部件
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {
    delete timer;
}
//点击发布活动按钮
void MainWindow::on_Publish_Clicked() {
    overall::settings->beginGroup(overall::me->userName);
    QString nickname = overall::settings->value("nickname", overall::me->userName).toString();
    overall::settings->endGroup();
    overall::me->nickname=nickname;

    publishWindow* pubact = new publishWindow(this);
    pubact->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除???
    pubact->show();
}

//双击活动的槽函数+查看详情
void MainWindow::on_ActivityItem_DoubleClicked(QListWidgetItem* item){

    activitys* act = item->data(Qt::UserRole).value<activitys*>();
    if (!act) return;
    // 显示活动详情
    actDetailWindow* actDetail=new actDetailWindow(this);
    actDetail->setActdetails(act);
    actDetail->setWindowModality(Qt::ApplicationModal);
    actDetail->show();
}

//右键点击的槽函数
void MainWindow::onActivityItemContextMenu(const QPoint &pos)
{
    QModelIndex index = activityList->indexAt(pos);
    if (index.isValid()) {
        // 保存当前上下文菜单项的索引
        currentContextIndex = index;
        // 创建右键菜单
        QMenu menu(this);
        // 添加菜单项
        QAction *deleteAction = menu.addAction("删除活动");
        // 连接菜单项到对应的槽函数
        connect(deleteAction, &QAction::triggered, this, &MainWindow::onDeleteActivity);
        // 在鼠标位置显示菜单
        menu.exec(activityList->mapToGlobal(pos));
    }

}

// 删除活动槽函数实现
void MainWindow::onDeleteActivity()
{
    if (currentContextIndex.isValid()) {
        // 确认对话框

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除", "确定要删除这个活动吗?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // 获取 QListWidgetItem 对象
            QListWidgetItem* item = activityList->item(currentContextIndex.row());
            if (!item) return;

            // 获取对应的 activitys 指针
            activitys* act = item->data(Qt::UserRole).value<activitys*>();
            if(overall::me->userName!=act->posterName()){
                QMessageBox::information(this, "警告","无权限删除");
                qDebug()<<"overall::me->userName:"<<overall::me->userName;
                qDebug()<<"act->posterName():"<<act->posterName();
                return;
            }
            else{
                qDebug()<<"overall::me->userName:"<<overall::me->userName;
                qDebug()<<"act->posterName():"<<act->posterName();
            }


            if (act) {
                // 从 overall::allActs 中删除该指针（注意：这里我们假设使用裸指针，需判断或处理内存）
                for (int i = 0; i < overall::allActs.size(); ++i) {
                    if (overall::allActs[i] == act) {
                        delete overall::allActs[i]; // 删除对象本身，防止内存泄漏
                        overall::allActs[i] = nullptr; // 标记为空
                        overall::allActs.remove(i);    // 只置空不移除
                        break;
                    }
                }
            }

            // 从 activityList 中删除该行
            delete activityList->takeItem(currentContextIndex.row());

            //保存所有活动
            overall::saveActivitiesToFile();
        }
    }
}


void MainWindow::updateTime() {
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    statusBar->showMessage("当前时间：" + currentTime);
}
