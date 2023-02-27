#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QMainWindow>
#include"temp_customer_consume.h"
#include"show_temp_customer_consume_sum.h"
#include"add_vip.h"
#include"modify_vip.h"
#include"consume_vip.h"
#include"charged_vip_record.h"
#include<QList>
#include"consume_vip_record.h"

class Vip;
namespace Ui {
class StartPage;
}

class StartPage : public QMainWindow
{
    Q_OBJECT

public:
    friend Consume_Vip_Record;
    enum VipConsumeFlag
    {
        DiscountFlag=1,
        NUmberFlag=2
    };
    enum VipRechargeFlag
    {
        RechargeMOney=1,
        RechargeNum=2
    };

    explicit StartPage(QWidget *parent = 0);
    ~StartPage();
    void ShowVipInfo(Vip *single);
    void ClearLineEdit();
    int TransferVipInfo();
    void ShowVipConsumeInfo(VipConsumeFlag flag);

    void SetQTableWiget(int num,VipConsumeFlag flag);
    void SetqTableWidgetContent(int num,VipConsumeFlag flag);

    void RechargeVip(VipRechargeFlag flag);
    void Vip_Record();
 void Show_Vip_Info();
protected:
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

    void OnBtnTempCustomConsumeClicked();
    void OnbtnAddVipClicked();
    void keyPressEvent(QKeyEvent *event);
signals:

private slots:
    void on_Sum_Temp_Consume_triggered();
    void on_pushButton_Find_clicked();
    void on_lineEdit_Find_textEdited(const QString &arg1);
    void on_comboBox_activated(const QString &arg1);
    void OnBtnModifyVipClicked();
    void OnBtnConsumeVipClicked();

private:
    Ui::StartPage *ui;
    Temp_Customer_Consume temp_customer_consume_page;
    Show_Temp_customer_Consume_Sum show_temp_customer_consume_sum;
    Add_Vip add_vip;
    Modify_Vip *modify_vip;
    QList<Vip*>list_temp;
    Vip*vip;
    Consume_Vip *consume_vip;
    QList<Vip*>list_vip_consume;
    QList<Vip*>list_vip_consume_show;
    Charged_Vip_Record * charged_vip_recored;
    //Vip*vip_recharge;

    Consume_Vip_Record *consume_vip_record;
};

#endif // STARTPAGE_H
