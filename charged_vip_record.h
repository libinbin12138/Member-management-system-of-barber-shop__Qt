#ifndef CHARGED_VIP_RECORD_H
#define CHARGED_VIP_RECORD_H

#include <QMainWindow>
#include<QList>
#include<add_vip.h>

namespace Ui {
class Charged_Vip_Record;
}

class Charged_Vip_Record : public QMainWindow
{
    Q_OBJECT

public:
    enum PrintFlag
    {
        PrintDay=1,
        PrintMonth=2,
        PrintYear=3
    };
    explicit Charged_Vip_Record(QWidget *parent = 0);
    ~Charged_Vip_Record();
    void Set_PrintList(PrintFlag flag);
    void Set_QTableWidget(PrintFlag flag);
protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Charged_Vip_Record *ui;
    QList<Vip*>list_print;
    Add_Vip *add_vip;
};

#endif // CHARGED_VIP_RECORD_H
