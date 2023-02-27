#ifndef TEMP_CUSTOMER_CONSUME_H
#define TEMP_CUSTOMER_CONSUME_H

#include <QMainWindow>
#include<QLabel>
#include <QCloseEvent>

#include<QList>
#include<QDebug>

#include"vip.h"
//class Show_Temp_customer_Consume_Sum;

namespace Ui {
class Temp_Customer_Consume;
}

class Temp_Customer_Consume : public QMainWindow
{
    Q_OBJECT
friend class Show_Temp_customer_Consume_Sum;
public:
    explicit Temp_Customer_Consume(QWidget *parent = 0);
    ~Temp_Customer_Consume();

protected:
    int Read_Temp_Customer_Consume();
     void Save_Temp_Customer_Consume(QString num);
     void closeEvent(QCloseEvent *event);
     void keyPressEvent(QKeyEvent *event);
void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_clicked();

private:

    Ui::Temp_Customer_Consume *ui;
      Vip*vip;
   QList<Vip*>list_vip;

};

#endif // TEMP_CUSTOMER_CONSUME_H
