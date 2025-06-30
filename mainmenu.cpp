
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QFrame>
#include <QLabel>
#include "mainwindow.h"
#include "user.h"
#include "social.h"
#include<overall.h>
#include <login.h>
mainMenu::mainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);

    setWindowTitle("主菜单");
    resize(900, 600);


    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    QFrame *leftPanel = new QFrame();
    leftPanel->setStyleSheet(
        "QFrame {"
        "   background: transparent;"
        "   border-right: 1px solid #dee2e6;"
        "}"
    );
    leftPanel->setFixedWidth(400);

    centralWidget->setStyleSheet(
        "QWidget {"
        "   background-image: url(:/file/background-3.png);"
        "   background-position: center;"
        "   background-repeat: no-repeat;"
        "   background-attachment: fixed;"
        "}"
    );

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(60, 80, 60, 100);
    leftLayout->setSpacing(100);

    QWidget *buttonContainer = new QWidget();
    buttonContainer->setStyleSheet("background: rgba(248, 249, 250, 150);"
                                   "   border: none;"
                                   "   padding: 12px 20px;"
                                   "   border-radius: 6px;"
                                   );

    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(30, 20, 30, 60);
    buttonLayout->setSpacing(30);

    btnOpenMainWindow = new QPushButton("活动总览");
    btnOpenUser = new QPushButton("用户界面");
    btnOpenSocial = new QPushButton("交友");
    btnWelcome=new QPushButton("WELCOME");

    // 美化按钮样式（不改变名称）
    QString buttonStyle =
        "QPushButton {"
        "   border: none;"
        "   padding: 12px 20px;"
        "   border-radius: 6px;"
        "   font-family: '楷体', 'KaiTi', 'STKaiti';"  // 设置楷体
        "   font-size: 30px;"
        "   color: white;"
        "   background-color: #4e73df;"
        "}"
        "QPushButton:hover {"
        "   background-color: #3a56c0;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #2e44a8;"
        "}";

    btnOpenMainWindow->setStyleSheet(buttonStyle);
    btnOpenUser->setStyleSheet(buttonStyle);//.replace("#4e73df", "#1cc88a").replace("#3a56c0", "#17a673").replace("#2e44a8", "#128f66"));
    btnOpenSocial->setStyleSheet(buttonStyle);

    btnWelcome->setStyleSheet(
        "QPushButton {"
        "   font-size: 38px;"
        "   font-weight: bold;"
        "   color: #4e73df;"                // 字体颜色改为白色
        "   font-weight: bold;"
        "   font-family: 'Arial', 'Helvetica', sans-serif;"
        "   padding: 0px 0px 0px 0px;"  //
        "   background: transparent;"    // 背景透明
        "   border: none;"
        "}"

                );
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(btnWelcome);
    buttonLayout->addSpacing(50);
    buttonLayout->addWidget(btnOpenMainWindow);
    buttonLayout->addSpacing(40);
    buttonLayout->addWidget(btnOpenUser);
    buttonLayout->addSpacing(40);
    buttonLayout->addWidget(btnOpenSocial);
    buttonLayout->addStretch();

    leftLayout->addStretch();
    leftLayout->addWidget(buttonContainer);
    leftLayout->addStretch();

    QWidget *rightPanel = new QWidget();
    rightPanel->setStyleSheet(
                "background: transparent;"
                "border-left: 15px solid #f8f9fa;"
    );

    QLabel *welcomeText = new QLabel("Welcome");
    welcomeText->setStyleSheet(
        "QLabel {"
        "   font-size: 42px;"
        "   color: white;"                // 字体颜色改为白色
        "   font-weight: bold;"
        "   font-style: italic;"
        "   padding: 60px 40px 0 40px;"  // 上边距60px，其他边距40px
        "   background: transparent;"    // 背景透明
        "}"
    );
    welcomeText->setAlignment(Qt::AlignCenter);


    QLabel *welcomeLabel = new QLabel();
    QPixmap pixmap(":/file/3.png"); // 使用资源路径或绝对文件路径
    // 设置图片到QLabel
    welcomeLabel->setPixmap(pixmap);
    // 保持图片比例缩放
    welcomeLabel->setScaledContents(true);

    // 样式表可以保留用于其他样式设置，但字体相关的可以去掉
    welcomeLabel->setStyleSheet(
        "QLabel {"
        "   padding: 40px;"
        "}"
    );
    welcomeLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 24px;"
        "   color: #5a5c69;"
        "   padding: 40px;"
        "   background: transparent;"
        "}"
    );
    welcomeLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->addWidget(welcomeLabel);

    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(rightPanel, 1);  // 右侧占据剩余空间

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(btnOpenMainWindow, &QPushButton::clicked, this, &mainMenu::openMainWindow);
    connect(btnOpenUser, &QPushButton::clicked, this, &mainMenu::openUser);
    connect(btnOpenSocial, &QPushButton::clicked, this, &mainMenu::openSocial);
}

mainMenu::~mainMenu()
{
    delete ui;
}
void mainMenu::openMainWindow()
{
    if (!login::loggedin)
    {login *loginPage = new login;
    loginPage->exec();}
    if (login::loggedin)
    {
    overall::activityList = new MainWindow(this);
    overall::activityList->setWindowModality(Qt::ApplicationModal);
    overall::activityList->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除???
    overall::activityList->show();}
}

void mainMenu::openUser()
{
    if (!login::loggedin)
    {login *loginPage = new login;
    loginPage->exec();}
    if (login::loggedin)
    {
    user* page = new user(this);
    page->setWindowModality(Qt::ApplicationModal);
    page->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除???
    page->show();}

   // *SubWindow2 *subWindow = new SubWindow2(this);
   // subWindow->setAttribute(Qt::WA_DeleteOnClose);
   // subWindow->show();
}

void mainMenu::openSocial()
{
    if (!login::loggedin)
    {login *loginPage = new login;
    loginPage->exec();}
    if (login::loggedin)
    {
    Social* page = new Social(this);
    page->setWindowModality(Qt::ApplicationModal);
    page->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除???
    page->show();}
}
