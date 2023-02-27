#include "add_vip.h"
#include "ui_add_vip.h"

#include<QDateTime>
#include<QTimer>
#include<QFile>
#include<QDebug>

#include<QString>
#include<QStringList>

#include<QMessageBox>
#include<QPainter>
#include<windows.h>
#include<QTimer>


Add_Vip::Add_Vip(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Add_Vip)
{
    ui->setupUi(this);
    this->setWindowTitle("新增会员");
    ui->comboBox->addItem("按折扣消费");        //直接增加 用addItem
    ui->comboBox->addItem("按次数消费");
    //        QStringList a;      //  定义一个字符串    //连续增加用 addItems
    //        a.clear();      //  清除字符串中内容
    //        a<<"天"<<"地"<<"玄"<<"黄";
    //        ui->comboBox_2->addItems(a);

    ConnectEnterKey();

     this->setWindowIcon(QIcon(":/image/mmexport1662627162101.jpg"));
}

Add_Vip::~Add_Vip()
{
    delete ui;
}

int Add_Vip::Read_Vip_Info()
{
    list_vip.clear();
    int vip_num=0;
    QFile data("./Vip_Info.txt");
    if(data.open(QIODevice::ReadOnly))
    {
        qDebug()<<"打开Vip_Info.txt成功";
    }
    else
    {
        qDebug()<<"打开Vip_Info.txt失败";
        return -1;
    }
    while(!data.atEnd())
    {
        if(data.atEnd())
        {
            data.close();
            break;
        }
        QString line;
        line = data.readLine();//逐行读取文件内容
        QStringList strList = line.split(" ");
        if(strList.size()<=0)
        {
            qDebug()<<"strList为空";
            return -1;
        }
        //qDebug()<<"创建vip_temp";
        Vip* vip_temp=new Vip;

        vip_temp->Vip_name=strList[0];
        vip_temp->Vip_phone=strList[1];
        vip_temp->Vip_type_flag=strList[2];

        vip_temp->Vip_remain_money=strList[3].toFloat();
        vip_temp->Vip_ramain_Num=strList[4].toFloat();
        vip_temp->Vip_discount=strList[5].toFloat();
        vip_temp->Vip_consume_Num=strList[6].toFloat();
        vip_temp->Vip_consume_money=strList[7].toFloat();
        vip_temp->Year=strList[8].toFloat();
        vip_temp->Month=strList[9].toFloat();
        vip_temp->Day=strList[10].toFloat();
        //qDebug()<<"准备向list—_vip读取添加vip_temp";
        list_vip.append(vip_temp);
        vip_num++;
        //qDebug()<<"读取添加vip_temp";
    }
    return vip_num;
}

void Add_Vip::Save_Vip_Info( )
{
    //    else
    //    {
    //        if(data.open(QIODevice::WriteOnly|QIODevice::Append))
    //            qDebug()<<"打开Vip_Info.txt成功Append";
    //    }

    QFile data("./Vip_Info.txt");

    if(data.open(QIODevice::WriteOnly|QIODevice::Truncate))

    {
        qDebug()<<"打开Vip_Info.txt成功Truncate";
    }
    else
    {
        qDebug()<<"打开Vip_Info.txt失败Truncate";
        return;
    }
    for(auto vip:list_vip)
    {
        QTextStream stream(&data);
        stream.setCodec("utf-8");

        QString time_str;
        time_str +=QString("%1").arg(vip->Year);
        time_str+=" ";
        time_str+=QString("%1").arg(vip->Month);
        time_str+=" ";
        time_str+=QString("%1").arg(vip->Day);

        QString save_text;
        save_text=(vip->Vip_name+" "+vip->Vip_phone+" "+ vip->Vip_type_flag
                   +" "+QString::number(vip->Vip_remain_money,'f',2)
                   +" "+QString::number(vip->Vip_ramain_Num,'f',2)
                   +" "+QString::number(vip->Vip_discount,'f',2)
                   +" "+QString::number( vip->Vip_consume_Num,'f',2)
                   +" "+QString::number(vip->Vip_consume_money,'f',2)
                   +" "+time_str);
        stream << save_text<<endl;
    }
    qDebug()<<"baocun成功";
    data.close();

}

int Add_Vip::Read_Origin_Vip_Info()
{
    list_vip_Origin.clear();

    int vip_num=0;
    QFile data("./Vip_Origin_Info.txt");
    if(data.open(QIODevice::ReadOnly))
    {
        qDebug()<<"打开Vip_Origin_Info.txt成功";
    }
    else
    {
        qDebug()<<"打开Vip_Origin_Info.txt失败";
        return -1;
    }

    while(!data.atEnd())
    {
        if(data.atEnd())
        {
            data.close();
            break;
        }
        QString line;
        line = data.readLine();//逐行读取文件内容
        QStringList strList = line.split(" ");
        if(strList.size()<=0)
        {
            qDebug()<<"strList为空";
            return -1;
        }
        //qDebug()<<"创建vip_temp";
        Vip* vip_temp=new Vip;

        vip_temp->Vip_name=strList[0];
        vip_temp->Vip_phone=strList[1];
        vip_temp->Vip_type_flag=strList[2];

        vip_temp->Vip_remain_money=strList[3].toDouble();
        vip_temp->Vip_ramain_Num=strList[4].toFloat();
        vip_temp->Vip_discount=strList[5].toFloat();
        vip_temp->Vip_consume_Num=strList[6].toFloat();
        vip_temp->Vip_consume_money=strList[7].toDouble();
        vip_temp->Year=strList[8].toFloat();
        vip_temp->Month=strList[9].toFloat();
        vip_temp->Day=strList[10].toFloat();
        list_vip_Origin.append(vip_temp);
        vip_num++;
    }
}

void Add_Vip::Save_Origin_Vip_Info()
{
    QFile data("./Vip_Origin_Info.txt");

    if(data.open(QIODevice::WriteOnly|QIODevice::Truncate))

    {
        qDebug()<<"打开Vip_Origin_Info.txt成功Truncate";
    }
    else
    {
        qDebug()<<"打开Vip_Origin_Info.txt失败Truncate";
        return;
    }

    for(auto vip:list_vip_Origin)
    {
        QTextStream stream(&data);
        stream.setCodec("utf-8");

        QString time_str;
        time_str+=QString("%1").arg(vip->Year);
        time_str+=" ";
        time_str+=QString("%1").arg(vip->Month);
        time_str+=" ";
        time_str+=QString("%1").arg(vip->Day);

        QString save_text;
        save_text=(vip->Vip_name+" "+vip->Vip_phone+" "+ vip->Vip_type_flag
                   +" "+QString::number(vip->Vip_remain_money,'f',2)
                   +" "+QString::number(vip->Vip_ramain_Num,'f',2)
                   +" "+QString::number(vip->Vip_discount,'f',2)
                   +" "+QString::number( vip->Vip_consume_Num,'f',2)
                   +" "+QString::number(vip->Vip_consume_money,'f',2)
                   +" "+time_str);
        stream << save_text<<endl;
    }

     qDebug()<<"充值成功";
    data.close();

}


void Add_Vip::ReadVipConsumeInfo(Add_Vip::FindConsumeFlag flag)
{
    QFile file("./Vip_Consume_Info.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"打开Vip_Consume_Info成功";
    }
    else
    {
        qDebug()<<"打开Vip_Consume_Info成功";
        return;
    }
    while(!file.atEnd())
    {
        QString line;
        line=file.readLine();
        QStringList stringlist=line.split(" ");
        Vip*vip_temp=new Vip;
        vip_temp->Vip_name=stringlist[0];
        vip_temp->Vip_phone=stringlist[1];
        vip_temp->Vip_type_flag=stringlist[2];
        vip_temp->Year=stringlist[6].toFloat();
        vip_temp->Month=stringlist[7].toFloat();
        vip_temp->Day=stringlist[8].toFloat();
        switch(flag)
        {
        case 1:
            vip_temp->Vip_consume_money=stringlist[5].toFloat();//获取折扣后消费金额
            vip_temp->Vip_discount=stringlist[4].toFloat();
            vip_temp->Vip_remain_money=stringlist[3].toFloat();//用Vip_remain_money获取折扣前消费金额
            break;
        case 2:
            vip_temp->Vip_ramain_Num=stringlist[5].toFloat();//获取消费后次数
            vip_temp->Vip_consume_Num=stringlist[4].toFloat();
            vip_temp->Vip_discount=stringlist[3].toFloat();//用flag获取消费前次数

            break;
        }
        list_vip_consume.append(vip_temp);
    }


}

void Add_Vip::ConnectEnterKey()
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

void Add_Vip::on_pushButton_clicked()
{
    this->ui->pushButton->setEnabled(false);
    vip=new Vip;
    vip->Vip_name=ui->lineEdit_5->text();
    vip->Vip_phone=ui->lineEdit_6->text();

    vip->Vip_type_flag=ui->comboBox->currentText();
    vip->Vip_remain_money=ui->lineEdit_7->text().toFloat();

    vip->Vip_discount=ui->lineEdit_8->text().toFloat();
    vip->Vip_ramain_Num=ui->lineEdit_4->text().toFloat();

    vip->Vip_consume_Num=ui->lineEdit_3->text().toFloat();
    vip->Vip_consume_money=ui->lineEdit_9->text().toFloat();

    QDate date=QDate::currentDate();
    vip->Year=date.year();
    vip->Month=date.month();
    vip->Day=date.day();

    if(vip->Vip_type_flag=="按折扣消费")
    {
        if( ui->lineEdit_5->text().size()==0||ui->lineEdit_6->text().size()==0
                ||ui->lineEdit_7->text().size()==0||ui->lineEdit_8->text().size()==0)
        {
            QMessageBox::warning(this, "错误","缺少关键信息的输入! ");
            ui->pushButton->setEnabled(true);
            return;
        }
    }
    if(vip->Vip_type_flag=="按次数消费")
    {
        if( ui->lineEdit_5->text().size()==0||ui->lineEdit_6->text().size()==0
                ||ui->lineEdit_4->text().size()==0)
        {
            QMessageBox::warning(this, "错误","缺少关键信息的输入! ");
            ui->pushButton->setEnabled(true);
            return;
        }
    }

    QMessageBox box(QMessageBox::Warning, "警告", "即将新增当前所输入的会员");
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
    box.setButtonText(QMessageBox::Ok, QString("确定"));
    box.setButtonText(QMessageBox::No, QString("取消"));
    box.setDefaultButton(QMessageBox::Ok);
   int ret=box.exec();

    switch(ret)
    {
    case QMessageBox::Ok:
    {
        Read_Vip_Info();
        list_vip.append(vip);
        Save_Vip_Info();

        Read_Origin_Vip_Info();
        list_vip_Origin.append(vip);
        Save_Origin_Vip_Info();

        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("通知"),QString("会员添加成功，无操作将自动返回!"));
        QTimer::singleShot(2000,m_box,SLOT(accept()));
        m_box->exec();

        this->close();
    }
    break;
    case QMessageBox::No:
         this->ui->pushButton->setEnabled(true);
        return;
    break;
    }

}

void Add_Vip::closeEvent(QCloseEvent *event)
{
    this->ui->pushButton->setEnabled(true);

    list_vip.clear();
    this->ui->lineEdit_3->clear();
    this->ui->lineEdit_4->clear();
    this->ui->lineEdit_5->clear();
    this->ui->lineEdit_6->clear();
    this->ui->lineEdit_7->clear();
    this->ui->lineEdit_8->clear();
    this->ui->lineEdit_9->clear();

}

void Add_Vip::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix(":/Res/R-C (5).jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void Add_Vip::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        this->close();
    }
}
