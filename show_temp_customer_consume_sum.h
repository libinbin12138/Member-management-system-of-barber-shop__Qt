#ifndef SHOW_TEMP_CUSTOMER_CONSUME_SUM_H
#define SHOW_TEMP_CUSTOMER_CONSUME_SUM_H

#include <QMainWindow>
#include"vip.h"
#include<QList>
#include"temp_customer_consume.h"

namespace Ui {
class Show_Temp_customer_Consume_Sum;
}

class Show_Temp_customer_Consume_Sum : public QMainWindow
{
    Q_OBJECT

public:
    explicit Show_Temp_customer_Consume_Sum(QWidget *parent = 0);
    ~Show_Temp_customer_Consume_Sum();
    void ShowInfo();
protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Show_Temp_customer_Consume_Sum *ui;
    QList<Vip*>list_vip_temp;
    Vip*vip;
    Temp_Customer_Consume temp_customer_consume;
};

#endif // SHOW_TEMP_CUSTOMER_CONSUME_SUM_H
