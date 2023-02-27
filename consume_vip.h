#ifndef CONSUME_VIP_H
#define CONSUME_VIP_H

#include <QMainWindow>
#include"modify_vip.h"
#include"vip.h"
#include"add_vip.h"
namespace Ui {
class Consume_Vip;
}

class Consume_Vip : public QMainWindow
{
    Q_OBJECT

public:

    enum ConsumeFlag
    {
        DiscountFlag=1,
        NUmberFlag=2
    };
    explicit Consume_Vip(QWidget *parent = 0);
    ~Consume_Vip();
    void CreateConsume(ConsumeFlag consume_flag);
    void ShowConsume(ConsumeFlag consume_flag);
    void SetTableContent(ConsumeFlag consume_flag);

    void SaveConusmeResult(ConsumeFlag consume_flag);
protected:
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
private slots:
    void on_pushButton_clicked();
void keyPressEvent(QKeyEvent *event);
private:
    Ui::Consume_Vip *ui;
    Modify_Vip * modify_vip;
    int flag;
    Add_Vip *add_vip;
    Vip * vip_consume;
};

#endif // CONSUME_VIP_H
