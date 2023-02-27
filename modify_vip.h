#ifndef MODIFY_VIP_H
#define MODIFY_VIP_H

#include <QMainWindow>
//#include"startpage.h"
#include"add_vip.h"
#include"consume_vip.h"

class StartPage;
class Vip;
namespace Ui {
class Modify_Vip;
}

class Modify_Vip : public QMainWindow
{
    Q_OBJECT
    friend StartPage;
    friend Consume_Vip;
public:
    explicit Modify_Vip(QWidget *parent = 0);
    ~Modify_Vip();
    void ReadInfo();
    void Set_LineEDit();
    void ModifySaved(int num);
    void Modify();
protected:
    void paintEvent(QPaintEvent *event);
    void ConnectEnterKey();
    void keyPressEvent(QKeyEvent *event);
void closeEvent(QCloseEvent *event);
private slots:
   void on_pushButton_clicked();

private:
    Ui::Modify_Vip *ui;
    Vip*vip;
    Vip*vip_new;
    StartPage *startpage;

    Add_Vip *add_vip;
};

#endif // MODIFY_VIP_H
