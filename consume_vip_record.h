#ifndef CONSUME_VIP_RECORD_H
#define CONSUME_VIP_RECORD_H

#include <QMainWindow>
#include<startpage.h>
#include<QList>

namespace Ui {
class Consume_Vip_Record;
}

class Consume_Vip_Record : public QMainWindow
{
    Q_OBJECT

public:
    enum PrintFlag
    {
        PrintDay=1,
        PrintMonth=2,
        PrintYear=3
    };
    explicit Consume_Vip_Record(QWidget *parent = 0);
    ~Consume_Vip_Record();
    void Consume_Vip_Info(PrintFlag flag);
    void SetPrintList(PrintFlag flag);
    void SetQTableWidget1(PrintFlag flag);
    void SetQTableWidget2(PrintFlag flag);
protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
   void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Consume_Vip_Record *ui;

    StartPage *startpage;
    QList<Vip*>list_vip_consume1;//表示按折扣消费的
    QList<Vip*>list_vip_consume2;//表示按次数消费的
    QList<Vip*>list_vip_consume_show1;
    QList<Vip*>list_vip_consume_show2;
};

#endif // CONSUME_VIP_RECORD_H
