#ifndef FRIENDDETAILDIALOG_H
#define FRIENDDETAILDIALOG_H

#include <QDialog>
#include <person.h>
namespace Ui {
class friendDetailDialog;
}

class friendDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit friendDetailDialog(const QString &username, QWidget *parent = nullptr);
    ~friendDetailDialog();

private slots:
    void on_deleteButton_clicked();

private:
    Ui::friendDetailDialog *ui;
    QString m_username;
};

#endif // FRIENDDETAILDIALOG_H
