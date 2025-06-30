#include "choosehobby.h"
#include "ui_choosehobby.h"
#include <QMessageBox>
#include <QDebug>
chooseHobby::chooseHobby(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseHobby)
{
    ui->setupUi(this);
    qDebug() << "Confirm button connected:" <<
        connect(ui->confirmButton, &QPushButton::clicked,
                this, &chooseHobby::on_confirmButton_clicked);
}

chooseHobby::~chooseHobby()
{
    delete ui;
}

QStringList chooseHobby::getSelectedHobbies() const  // 注意这里的 const
{
    return selectedHobbies;
}

void chooseHobby::on_confirmButton_clicked()
{
    qDebug() << "Dialog accepted with hobbies:";
    selectedHobbies.clear();

    // 检查哪些复选框被选中
    if(ui->checkBox_sports->isChecked())
        selectedHobbies << ui->checkBox_sports->text();
    if(ui->checkBox_boardgame->isChecked())
        selectedHobbies << ui->checkBox_boardgame->text();
    if(ui->checkBox_eatout->isChecked())
        selectedHobbies << ui->checkBox_eatout->text();
    if(ui->checkBox_trip->isChecked())
        selectedHobbies << ui->checkBox_trip->text();
    if(ui->checkBox_others->isChecked())
        selectedHobbies << ui->checkBox_others->text();

    // 限制最多选择2个
    if(selectedHobbies.size() > 2) {
        QMessageBox::warning(this, "提示", "最多只能选择2个爱好！");
        selectedHobbies.clear();
        return;
    }
    //emit hobbiesSelected(selectedHobbies); // 发射信号
    qDebug() << "Dialog accepted with hobbies:" << selectedHobbies;
    accept(); // 关闭对话框

}

