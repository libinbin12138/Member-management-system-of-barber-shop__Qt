#ifndef ADD_VIP_H
#define ADD_VIP_H

#include <QMainWindow>
#include<vip.h>
#include<QList>
#include<modify_vip.h>

class StartPage;
class Consume_Vip;
class Charged_Vip_Record;

namespace Ui {
class Add_Vip;
}

class Add_Vip : public QMainWindow
{

    Q_OBJECT
    friend StartPage;
    friend Modify_Vip;
    friend Consume_Vip;
    friend Charged_Vip_Record;

public:
    enum FindConsumeFlag
    {
        DiscountConsume =1,
        NUmberConsume=2
    };
    explicit Add_Vip(QWidget *parent = 0);
    ~Add_Vip();

    int Read_Vip_Info();//读会员信息，一直在消费后变化
    void Save_Vip_Info();//保存会员每次有改动后的信息

    int Read_Origin_Vip_Info();//读会员信息，除每次充值外，不发生变化
    void Save_Origin_Vip_Info();//保存会员信息，除每次充值外，不发生变化

    void ShowVipConsume(FindConsumeFlag flag);
  void ReadVipConsumeInfo(FindConsumeFlag flag);

protected:
    void ConnectEnterKey();
private slots:
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::Add_Vip *ui;

    Vip*vip;

    QList<Vip*>list_vip;
    QList<Vip*>list_vip_consume;
    QList<Vip*>list_vip_Origin;
};

#endif // ADD_VIP_H
