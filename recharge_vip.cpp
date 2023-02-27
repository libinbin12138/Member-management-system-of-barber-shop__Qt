#include "recharge_vip.h"
#include "ui_recharge_vip.h"

Recharge_Vip::Recharge_Vip(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Recharge_Vip)
{
    ui->setupUi(this);
}

Recharge_Vip::~Recharge_Vip()
{
    delete ui;
}
