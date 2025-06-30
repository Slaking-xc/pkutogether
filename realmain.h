#ifndef SUB1_H
#define SUB1_H

#include <QMainWindow>

namespace Ui {
class sub1;
}

class sub1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit sub1(QWidget *parent = nullptr);
    ~sub1();

private:
    Ui::sub1 *ui;
};

#endif // SUB1_H
