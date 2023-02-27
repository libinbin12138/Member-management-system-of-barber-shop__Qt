#ifndef RECHARGE_VIP_H
#define RECHARGE_VIP_H

#include <QMainWindow>

namespace Ui {
class Recharge_Vip;
}

class Recharge_Vip : public QMainWindow
{
    Q_OBJECT

public:
    explicit Recharge_Vip(QWidget *parent = 0);
    ~Recharge_Vip();

private:
    Ui::Recharge_Vip *ui;
};

#endif // RECHARGE_VIP_H
