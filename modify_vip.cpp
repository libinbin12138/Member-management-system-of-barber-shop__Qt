#include "modify_vip.h"
#include "ui_modify_vip.h"

#include<QPainter>
#include"startpage.h"
#include"vip.h"
#include<QTextCodec>
#include<QApplication>

#include<QString>
#include<QStringList>
#include<QFile>
#include<QComboBox>

#include<QMessageBox>
#include <QtGui>
#include<QDate>

Modify_Vip::Modify_Vip(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Modify_Vip)
{
    ui->setupUi(this);
    this->setWindowTitle("修改会员信息");
    vip=new Vip;
    vip_new=new Vip;

    ReadInfo();
    Set_LineEDit();

    ConnectEnterKey();
     this->setWindowIcon(QIcon(":/image/mmexport1662627162101.jpg"));
}

Modify_Vip::~Modify_Vip()
{
    if(vip!=NULL)
    {
        delete vip;
        vip==NULL;
    }
    delete ui;
}

void Modify_Vip::ReadInfo()
{
    QFile file("./Vip_OPeration_Temp.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
        {
            if(file.atEnd())
            {
                file.close();
                break;
            }
            QString line;
            line = file.readLine();//逐行读取文件内容
            QStringList strList = line.split(" ");
            if(strList.size()<=0)
            {
                qDebug()<<"strList为空";
                return;
            }

            vip->Vip_name=strList[0];
            vip->Vip_phone=strList[1];
            vip->Vip_type_flag=strList[2];

            vip->Vip_remain_money=strList[3].toFloat();
            vip->Vip_ramain_Num=strList[4].toFloat();
            vip->Vip_discount=strList[5].toFloat();
            vip->Vip_consume_Num=strList[6].toFloat();
            vip->Vip_consume_money=strList[7].toFloat();
        }
    }
    file.close();
}

void Modify_Vip::Set_LineEDit()
{
    if(vip==NULL)
    {
        return;
    }

    ui->lineEdit_5->setText(vip->Vip_name);

    if(vip->Vip_type_flag=="按折扣消费")
    {
        ui->comboBox->addItem("按折扣消费");        //直接增加 用addItem
        ui->comboBox->addItem("按次数消费");
    }
    else
    {
        ui->comboBox->addItem("按次数消费");
        ui->comboBox->addItem("按折扣消费");
    }

    ui->lineEdit_4->setText(QString::number(vip->Vip_ramain_Num,'f',2));
    ui->lineEdit_3->setText(QString::number(vip->Vip_consume_Num,'f',2));

    ui->lineEdit_6->setText(vip->Vip_phone);
    ui->lineEdit_7->setText(QString::number(vip->Vip_remain_money,'f',2));
    ui->lineEdit_8->setText(QString::number(vip->Vip_discount,'f',2));
    ui->lineEdit_9->setText(QString::number(vip->Vip_consume_money,'f',2));
}

void Modify_Vip::Modify()
{
    vip_new->Vip_name=ui->lineEdit_5->text();
    vip_new->Vip_phone=ui->lineEdit_6->text();

    vip_new->Vip_type_flag=ui->comboBox->currentText();
    vip_new->Vip_remain_money=ui->lineEdit_7->text().toFloat();

    vip_new->Vip_discount=ui->lineEdit_8->text().toFloat();
    vip_new->Vip_ramain_Num=ui->lineEdit_4->text().toFloat();

    vip_new->Vip_consume_Num=ui->lineEdit_3->text().toFloat();
    vip_new->Vip_consume_money=ui->lineEdit_9->text().toFloat();

}

void Modify_Vip::ModifySaved(int num)
{
    add_vip=new Add_Vip;
    add_vip->Read_Vip_Info();

    qDebug()<<"add_vip.list size=="<<add_vip->list_vip.size();

    QList<Vip*>::iterator it;

    for(it=add_vip->list_vip.begin(); it!=add_vip->list_vip.end();it++)
    {
        if(num==1)
        {
           if((*it)->Vip_name==vip->Vip_name&&(*it)->Vip_phone==vip->Vip_phone)
           {
               qDebug()<<"准备修改";
               add_vip->list_vip.erase(it);

               QDate time=QDate::currentDate();
               vip_new->Year=time.year();
               vip_new->Month=time.month();
               vip_new->Day=time.day();

               add_vip->list_vip.insert(it,vip_new);
               break;
           }
        }
    }
    if(add_vip->list_vip.size()!=0)
    {
        add_vip->Save_Vip_Info();
        add_vip->list_vip.clear();
    }
    qDebug()<<"修改成功";
}

void Modify_Vip::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix(":/Res/R-C (2).jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void Modify_Vip::ConnectEnterKey()
{
    //绑定回车键
    connect(ui->lineEdit_3, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);
    connect(ui->lineEdit_4, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);
    connect(ui->lineEdit_5, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);
    connect(ui->lineEdit_6, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);
    connect(ui->lineEdit_7, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);
    connect(ui->lineEdit_8, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);
    connect(ui->lineEdit_9, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);

    ui->pushButton->setFocus(); /* 设置默认焦点 */
    ui->pushButton->setDefault ( true ); /* 设置默认按钮，设置了这个属性，当用户按下回车的时候，就会按下该按钮 */

}

void Modify_Vip::keyPressEvent(QKeyEvent *event)
{if (event->key() == Qt::Key_Escape)
    {
        this->close();
    }

}

void Modify_Vip::closeEvent(QCloseEvent *event)
{
    this->ui->lineEdit_3->clear();
    this->ui->lineEdit_4->clear();
    this->ui->lineEdit_5->clear();
    this->ui->lineEdit_6->clear();
    this->ui->lineEdit_7->clear();
    this->ui->lineEdit_8->clear();
    this->ui->lineEdit_9->clear();
    ui->comboBox->clear();
    this->ui->pushButton->setEnabled(true);
}



void Modify_Vip::on_pushButton_clicked()
{
    Modify();
    int num=-1,ret=0;

    if(vip_new->Vip_name!=vip->Vip_name||vip_new->Vip_phone!=vip->Vip_phone||
       vip_new->Vip_discount!=vip->Vip_discount||vip_new->Vip_type_flag!=vip->Vip_type_flag||
       vip_new->Vip_consume_money!=vip->Vip_consume_money||vip_new->Vip_consume_Num!=vip->Vip_consume_Num||
       vip_new->Vip_ramain_Num!=vip->Vip_ramain_Num||vip_new->Vip_remain_money!=vip->Vip_remain_money)
    {
        num=1;
    }
    if(num==1)
    {
        QMessageBox box(QMessageBox::Warning, "警告", "当前所选会员信息 即将被修改");
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
        box.setButtonText(QMessageBox::Ok, QString("确定"));
        box.setButtonText(QMessageBox::No, QString("取消"));
        box.setDefaultButton(QMessageBox::Ok);
        ret=box.exec();
        //int ret=QMessageBox::warning(this,"警告","当前会员信息 即将被修改",QMessageBox::Ok,QMessageBox::No);
        //QMessageBox::warning.setDefaultButton(QMessageBox::Save);
    }
    else
    {
        qDebug()<<"无任何修改";
        return;
    }

    switch(ret)
    {
    case QMessageBox::Ok:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        ModifySaved(num);
        this->ui->pushButton->setEnabled(false);
        break;
    case QMessageBox::No:
        return;
        break;
    }


    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("通知"),QString("会员修改成功，无操作将自动返回!"));
    QTimer::singleShot(2000,m_box,SLOT(accept()));
    m_box->exec();

    this->close();

}
