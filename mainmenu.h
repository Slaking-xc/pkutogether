#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QPushButton>
namespace Ui {
class mainMenu;
}

class mainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = nullptr);
    ~mainMenu();

private slots:
    void openMainWindow();
    void openUser();
    void openSocial();


private:
    Ui::mainMenu *ui;
    QPushButton *btnOpenMainWindow;
    QPushButton *btnOpenUser;
    QPushButton *btnOpenSocial;
    QPushButton *btnWelcome;
};

#endif // MAINMENU_H
