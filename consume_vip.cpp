#include "consume_vip.h"
#include "ui_consume_vip.h"
#include<QPainter>
#include<QDebug>
#include<QMessageBox>
#include<QDate>
Consume_Vip::Consume_Vip(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Consume_Vip),
    flag(0)
{
    ui->setupUi(this);
    this->setWindowTitle("会员消费");
    vip_consume=new Vip;
    this->modify_vip=new Modify_Vip;
    modify_vip->ReadInfo();
    if( modify_vip->vip->Vip_type_flag=="按折扣消费")
    {
        this->ui->label->setText("请输入该会员折扣前的消费金额");
        flag=1;
    }
    else
    {
        this->ui->label->setText("请输入本次要扣除的该会员的理发次数，默认值为1");
        this->ui->lineEdit->setText("1");
        flag=2;
    }

    this->ui->label_2->hide();
    this->ui->qTableWidget->hide();

    //绑定回车键
    connect(ui->lineEdit, SIGNAL(returnPressed()), ui->pushButton, SLOT(click()), Qt::UniqueConnection);

     this->setWindowIcon(QIcon(":/image/mmexport1662627162101.jpg"));
}

Consume_Vip::~Consume_Vip()
{
    delete ui;
}

void Consume_Vip::CreateConsume(Consume_Vip::ConsumeFlag consume_flag)
{
    add_vip =new Add_Vip;
    add_vip->Read_Vip_Info();

    QMessageBox box(QMessageBox::Warning, "警告", "该会员的消费结果即将生成");
    box.setStandardButtons(QMessageBox::Ok|QMessageBox::No);
    box.setButtonText(QMessageBox::Ok,QString("确定"));
    box.setButtonText(QMessageBox::No,QString("取消"));
    box.setDefaultButton(QMessageBox::Ok);
    int ret= box.exec();
    switch( ret)
    {
    case QMessageBox::Ok:
    {
        QList<Vip*>::iterator it;
        for(it=add_vip->list_vip.begin();it!=add_vip->list_vip.end();it++)
        {
            if((*it)->Vip_name==modify_vip->vip->Vip_name&&(*it)->Vip_phone==modify_vip->vip->Vip_phone)
            {
                modify_vip->vip->Year=(*it)->Year;
                modify_vip->vip->Month=(*it)->Month;
                modify_vip->vip->Day=(*it)->Day;

                qDebug()<<"相等------------------------------------";
                add_vip->list_vip.erase(it);

                switch(consume_flag)
                {
                case 1:
                {
                    float consume_money=ui->lineEdit->text().toFloat();
                    modify_vip->vip->Vip_remain_money-=((consume_money*modify_vip->vip->Vip_discount/10.0000));
                    modify_vip->vip->Vip_consume_money+=(consume_money*modify_vip->vip->Vip_discount/10.0000);

                }
                    break;
                case 2:
                {
                    int consume_num=ui->lineEdit->text().toFloat();
                    modify_vip->vip->Vip_ramain_Num-=consume_num;
                    modify_vip->vip->Vip_consume_Num+=consume_num;
                }
                    break;
                }
                add_vip->list_vip.insert(++it, modify_vip->vip);
                break;
            }
        }
        add_vip->Save_Vip_Info();
        ShowConsume(consume_flag);
        SaveConusmeResult(consume_flag);
        add_vip->list_vip.clear();
        this->ui->pushButton->setEnabled(true);}
        break;

   case QMessageBox::No:
        add_vip->list_vip.clear();
        this->ui->pushButton->setEnabled(true);
        return;
    }

}

void Consume_Vip::ShowConsume(Consume_Vip::ConsumeFlag consume_flag)
{
    this->ui->label_2->setText("本次消费结果如下所示 ：");
    this->ui->label_2->show();


    ui->qTableWidget->setColumnCount(7);//设置列数
    ui->qTableWidget->setRowCount(1);//设置行数
    ui->qTableWidget->setWindowTitle("QTableWidget");

    //ui->qTableWidget->setma
    //设置列标签
    QStringList m_Header;

    switch(consume_flag)
    {
    case 1:
        m_Header<<QString("姓名")<<QString("手机号码")<<QString("本次消费金额")<<QString("当前享受折扣")<<QString("折扣后金额")<<QString("消费后余额")<<QString("消费生成时间");
        break;
    case 2:
        m_Header<<QString("姓名")<<QString("手机号码")<<QString("扣除前剩余次数")<<QString("本次扣除次数")<<QString("扣除后剩余次数")<<QString("消费后余额")<<QString("消费生成时间");
        break;
    }
    SetTableContent(consume_flag);
    ui->qTableWidget->setHorizontalHeaderLabels(m_Header);//添加横向表头
    ui->qTableWidget->verticalHeader()->setVisible(true);//纵向表头可视化
    ui->qTableWidget->horizontalHeader()->setVisible(true);//横向表头可视化

    ui->qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中

    ui->qTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->qTableWidget->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色


    for(int columns=0;columns<7;columns++)
    {
        ui->qTableWidget->setColumnWidth(columns,110);
        ui->qTableWidget->setRowHeight(0,30);

        ui->qTableWidget->item(0,columns)->setTextAlignment(Qt::AlignCenter);//居中显示
        ui->qTableWidget->item(0,columns)->setTextColor(QColor(0,0,0));//设置文本颜色
        ui->qTableWidget->item(0,columns)->setFont(QFont("Helvetica"));//设置字体为黑体
    }

    ui->qTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置水平滚动条
    ui->qTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条

    this->ui->qTableWidget->show();

}

void Consume_Vip::SetTableContent(Consume_Vip::ConsumeFlag consume_flag)
{
    switch(consume_flag)
    {
    case 1:
    {
        for(int columns=0;columns<7;columns++)
        {
            if(columns==0)
            {
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(modify_vip->vip->Vip_name));
            }
            else if(columns==1)
            {
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(modify_vip->vip->Vip_phone));
            }
            else if(columns==2)
            {
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(ui->lineEdit->text()));
            }
            else if(columns==3)
            {
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(QString::number(modify_vip->vip->Vip_discount,'f',2)));
            }
            else if(columns==4)
            {
                int num=0;
                num=ui->lineEdit->text().toFloat()*modify_vip->vip->Vip_discount/10.0000;
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(QString::number(num,'f',2)));
            }
            else if(columns==5)
            {
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(QString("%1").arg(modify_vip->vip->Vip_remain_money)));
            }
            else if(columns==6)
            {
                QDate date=QDate::currentDate();
                QString date_str=date.toString("yyyy MM dd ");

                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(date_str));
            }
        }
    }
        break;
    case 2:
    {
        for(int columns=0;columns<7;columns++)
        {
            if(columns==0)
            {
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(modify_vip->vip->Vip_name));
            }
            else if(columns==1)
            {
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(modify_vip->vip->Vip_phone));
            }
            else if(columns==2)
            {
                int num=0;
                num=modify_vip->vip->Vip_ramain_Num+ui->lineEdit->text().toFloat();
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(QString::number(num,'f',2)));
            }
            else if(columns==3)
            {
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(ui->lineEdit->text()));
            }
            else if(columns==4)
            {
                int num=0;
                num=ui->lineEdit->text().toFloat()*modify_vip->vip->Vip_discount/10.0000;
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(QString::number(modify_vip->vip->Vip_ramain_Num,'f',2)));
            }
            else if(columns==5)
            {
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(QString::number(modify_vip->vip->Vip_remain_money,'f',2)));
            }
            else if(columns==6)
            {
                QDate date=QDate::currentDate();
                QString date_str=date.toString("yyyy MM dd ");
                ui->qTableWidget->setItem(0,columns,new QTableWidgetItem(date_str));
            }
        }
    }

        break;

    }
}


void Consume_Vip::SaveConusmeResult(Consume_Vip::ConsumeFlag consume_flag)
{
    QFile data("./Vip_Consume_Info.txt");

    if(data.open(QIODevice::WriteOnly|QIODevice::Append))

    {
        qDebug()<<"Vip_Consume_Info Append";
    }
    else
    {
        qDebug()<<"打开Vip_Consume_Info失败Append";
        return;
    }

    QTextStream stream(&data);
    stream.setCodec("utf-8");

    QDateTime time = QDateTime::currentDateTime();
    QString time_str = time.toString("yyyy MM dd");

    vip_consume=modify_vip->vip;
    QString save_text;
     int num=0;
    switch (consume_flag) {
    case 1:
    {
         num=ui->lineEdit->text().toFloat()*vip_consume->Vip_discount/10.0000;
        save_text=(vip_consume->Vip_name+" "+vip_consume->Vip_phone
                   +" "+ vip_consume->Vip_type_flag
                   +" "+ui->lineEdit->text()
                   +" "+QString::number(vip_consume->Vip_discount,'f',2)
                   +" "+QString::number(num,'f',2)
                   +" "+time_str);
    }
        break;
    case 2:
    {
        num=modify_vip->vip->Vip_ramain_Num+ui->lineEdit->text().toFloat();
        save_text=(vip_consume->Vip_name+" "+vip_consume->Vip_phone
                   +" "+ vip_consume->Vip_type_flag
                   +" "+QString::number(num,'f',2)
                   +" "+ui->lineEdit->text()
                   +" "+QString::number(vip_consume->Vip_ramain_Num,'f',2)
                   +" "+time_str);
    }
        break;
    default:
        break;
    }

    stream << save_text<<endl;
    qDebug()<<"baocun成功";
    data.close();

}



void Consume_Vip::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix(":/Res/R-C (1).jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void Consume_Vip::closeEvent(QCloseEvent *event)
{
    this->ui->label->clear();
    this->ui->label_2->clear();
    this->ui->lineEdit->clear();
    this->ui->qTableWidget->clear();
    this->ui->pushButton->setEnabled(true);
}

void Consume_Vip::on_pushButton_clicked()
{
    if(ui->lineEdit->text().size()==0)
    {
        return;
    }
    this->ui->pushButton->setEnabled(false);
    switch (flag)
    {
    case 1:
        CreateConsume(ConsumeFlag::DiscountFlag);
        break;
    case 2:
        CreateConsume(ConsumeFlag::NUmberFlag);
        break;
    default:
        return;
        break;
    }
    add_vip->list_vip.clear();

}

void Consume_Vip::keyPressEvent(QKeyEvent *event)
{if (event->key() == Qt::Key_Escape)
    {
        this->close();
    }

}
