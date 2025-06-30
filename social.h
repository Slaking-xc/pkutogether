#ifndef SOCIAL_H
#define SOCIAL_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDialog>
namespace Ui {
class Social;
}

class Social : public QMainWindow
{
    Q_OBJECT

public:
    explicit Social(QWidget *parent = nullptr);
    ~Social();
    void  refreshFriendList();
private slots:
    void onFriendDoubleClicked(QListWidgetItem* item);
    void on_becomeFriend_clicked();

private:
    Ui::Social *ui;

};

#endif // SOCIAL_H
