#include "temp_customer_consume.h"
#include "ui_temp_customer_consume.h"

#include <QApplication>
#include<QDateTime>
#include<QTimer>
#include<QDebug>

#include<QString>
#include<QStringList>
#include<QPainter>

Temp_Customer_Consume::Temp_Customer_Consume(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Temp_Customer_Consume)
{
    ui->setupUi(this);
    this->setWindowTitle("散客");
    this->resize(300,500);

    this->ui->label_2->hide();
    this->ui->label_3->hide();

    //绑定回车键
    connect(ui->lineEdit, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);
 this->setWindowIcon(QIcon(":/image/mmexport1662627162101.jpg"));
}

Temp_Customer_Consume::~Temp_Customer_Consume()
{

    delete ui;

}

int Temp_Customer_Consume::Read_Temp_Customer_Consume()
{
    QFile data("./Read_Temp_Customer_Consume.txt");
    //确认文件是否存在
    //    bool isExist = data.exists();
    //    if(isExist)
    //    {
    //        qDebug()<<"Temp_Customer_Consume存在 ";
    //    }
    //    else
    //    {
    //        qDebug()<<"Temp_Customer_Consume不存在 ";
    //    }

    int n,vipnum=0;
    if (data.open(QFile::ReadOnly))
    {
        qDebug()<<"打开Temp_Customer_Consume成功 ";

        QString line;
        while (!data.atEnd())
        {

            if(data.atEnd())
            {
                data.close();
                break;
            }
            line = data.readLine();//逐行读取文件内容

            QStringList strList = line.split(" ");
            if(strList.size()<4)
            {
                qDebug()<<"strList为空";
                return -1;
            }
            vip=new Vip;
            vip->Vip_consume_money=strList[0].toDouble();
            vip->Year=strList[1].toFloat();
            vip->Month=strList[2].toFloat();
            vip->Day=strList[3].toFloat();
            list_vip.append(vip);
            n++;
            vipnum++;
            qDebug("读取数据 %d",n);
        }
    }
    return vipnum;

}

void Temp_Customer_Consume::Save_Temp_Customer_Consume(QString num)
{
    int vip_num=Read_Temp_Customer_Consume();
    QFile data("./Read_Temp_Customer_Consume.txt");
    if(num<=0)
    {
        data.open(QIODevice::ReadWrite|QIODevice::Truncate);
    }
    else
    {
        data.open(QIODevice::ReadWrite|QIODevice::Append);
    }
    list_vip.clear();
    QDateTime time = QDateTime::currentDateTime();
    QString time_str = time.toString("yyyy MM dd");

    QTextStream stream(&data);
    stream.setCodec("utf-8");
    num+=" ";
    num+=time_str;
    stream << num<<endl;//num<<" "<<year<<endl;
    data.close();
    list_vip.clear();
}



void Temp_Customer_Consume::closeEvent(QCloseEvent *event)
{
    ui->label_2->hide();
    ui->label_3->hide();
    this->ui->pushButton->setEnabled(true);
    this->ui->lineEdit->clear();
}

void Temp_Customer_Consume::keyPressEvent(QKeyEvent *event)
{
    //绑定esc键触发的事件
    if (event->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

void Temp_Customer_Consume::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix(":/image/mmexport1604530983200.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}



void Temp_Customer_Consume::on_pushButton_clicked()
{
    this->ui->pushButton->setEnabled(false);
    QString num,consume_text;
    num=ui->lineEdit->text();

    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd");
    ui->label_2->setText(str);

    Read_Temp_Customer_Consume();
    float consume_num=0;

    if(list_vip.size()>0)
    {
        for(auto single :list_vip)
        {
            if(single->Year==time.date().year()&&single->Month==time.date().month()&&single->Day==time.date().day())
            {
                qDebug()<<"有当天的数据";
                consume_num+=single->Vip_consume_money;
            }
        }
    }


    if(num.size()==0)//没输入内容的情况
    {
        QString consume_str = QString("%1").arg(consume_num);
        consume_text=("当日散客消费总金额 : "+consume_str);
        this->ui->pushButton->setEnabled(true);
        this->ui->label_3->setText(consume_text);
        this->ui->label_2->show();
        this->ui->label_3->show();
        list_vip.clear();
        return;
    }

    Save_Temp_Customer_Consume(num);
    consume_num+=num.toDouble();
    QString consume_str = QString("%1").arg(consume_num);
    consume_text=("当日散客消费总金额 : "+consume_str);
    this->ui->label_3->setText(consume_text);
    this->ui->label_2->show();
    this->ui->label_3->show();
    list_vip.clear();
}




