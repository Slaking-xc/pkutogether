#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QListWidget *activityList; // 活动列表
    QVector<QListWidgetItem*> actlstItem;//活动对应按钮
    QPushButton *publishButton;
    QLabel *titleLabel;
    QStatusBar *statusBar;
    QTimer *timer;
    QModelIndex currentContextIndex;

    void refreshActivityList();

private slots:
    void on_Publish_Clicked();    // 点击 "发布活动"
    void updateTime();         // 更新时间显示
    void on_ActivityItem_DoubleClicked(QListWidgetItem* item);

    void onActivityItemContextMenu(const QPoint &pos);

    void onDeleteActivity();




};

#endif // MAINWINDOW_H
