#include "startpage.h"
#include "ui_startpage.h"

#include<QPushButton>
#include"mybtn.h"
#include"QPainter"
#include"QDebug"
#include<QMessageBox>
#include <QComboBox>

#include<QString>
#include<QFile>
#include"vip.h"
#include<windows.h>

#include<QInputDialog>
#include<QTimer>
#include<QDate>

StartPage::StartPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartPage)
{
    ui->setupUi(this);
    this->setWindowTitle("尚雅美发会员管理系统");

    // this->setFixedSize(900,600);
    this->ui->comboBox->hide();

    QPushButton *btn_temp_custom_consume=ui->pushButton_Temp_Consume;

    connect(btn_temp_custom_consume,&MyBtn::clicked,[=]()
    {
        this->OnBtnTempCustomConsumeClicked();
    }
    );
    QPushButton *btn_add_vip=ui->pushButton_Add_Vip;
    connect(btn_add_vip,&MyBtn::clicked,[=]()
    {
        this->OnbtnAddVipClicked();
    }
    );

    QPushButton *btn_modify_vip=ui->pushButton_Modify_vip;
    connect(btn_modify_vip,&QPushButton::clicked,[=]()
    {
        this->OnBtnModifyVipClicked();
    }
    );
    QPushButton *btn_consume_vip=ui->pushButton_Consume_Vip;
    connect(btn_consume_vip,&QPushButton::clicked,[=]()
    {
        this->OnBtnConsumeVipClicked();
    }
    );

    //绑定回车键
    connect(ui->lineEdit_Find, SIGNAL(returnPressed()), ui->pushButton_Find, SLOT(click()), Qt::UniqueConnection);

    this->ui->qTableWidget->hide();
    this->ui->label_10->hide();
    this->setWindowIcon(QIcon(":/Res/0147885543e2790000019ae90fad09.jpg@2o.jpg"));

    connect(ui->Vip_Recharge,&QAction::triggered,[=]
    {
        RechargeVip(VipRechargeFlag::RechargeMOney);
    });

    connect(ui->Recharge_Vip_Num,&QAction::triggered,[=]
    {
        RechargeVip(VipRechargeFlag::RechargeNum);
    });

    connect(ui->Sum_Vip_Consume,&QAction::triggered,[=]
    {
        Vip_Record();
    });

    connect(ui->Show_All_Vip,&QAction::triggered,[=]
    {
        Show_Vip_Info();
    });

    this->ui->tableWidget->hide();
     this->setWindowIcon(QIcon(":/image/mmexport1662627162101.jpg"));
}

StartPage::~StartPage()
{/*
    if(vip!=nullptr)
    {
        delete vip;
    }
    if(modify_vip!=nullptr)
    {
        delete modify_vip;
    }

    if(consume_vip!=nullptr)
    {
        delete consume_vip;
    }释放就奔了

*/
    delete ui;
}

void StartPage::ShowVipInfo(Vip*single)
{
    this->ui->lineEdit_2->setText(single->Vip_type_flag);
    this->ui->lineEdit_3->setText(QString::number(single->Vip_consume_Num,'f',2));
    this->ui->lineEdit_4->setText(QString::number(single->Vip_ramain_Num,'f',2));
    this->ui->lineEdit_5->setText(single->Vip_name);
    this->ui->lineEdit_6->setText(single->Vip_phone);
    this->ui->lineEdit_7->setText(QString::number(single->Vip_remain_money,'f',2));
    this->ui->lineEdit_8->setText(QString::number(single->Vip_discount,'f',2));
    this->ui->lineEdit_9->setText(QString::number(single->Vip_consume_money,'f',2));

    if(single->Vip_type_flag=="按折扣消费")
    {
        ShowVipConsumeInfo(VipConsumeFlag::DiscountFlag);
    }
    else
    {
        ShowVipConsumeInfo(VipConsumeFlag::NUmberFlag);
    }

}

void StartPage::ClearLineEdit()
{
    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_3->clear();
    this->ui->lineEdit_4->clear();
    this->ui->lineEdit_5->clear();
    this->ui->lineEdit_6->clear();
    this->ui->lineEdit_7->clear();
    this->ui->lineEdit_8->clear();
    this->ui->lineEdit_9->clear();
    this->ui->lineEdit_Find->clear();
    this->ui->qTableWidget->clear();
    this->ui->qTableWidget->hide();


}

int StartPage::TransferVipInfo()
{
    if(ui->lineEdit_5->text().size()<=0)
    {
        return 0;
    }
    QString temp_vip_info=
            ui->lineEdit_5->text()+" "+ui->lineEdit_6->text()+" "
            +ui->lineEdit_2->text()+" "+ui->lineEdit_7->text()+" "
            +ui->lineEdit_4->text()+" "+ui->lineEdit_8->text()+" "
            +ui->lineEdit_3->text()+" "+ui->lineEdit_9->text();
    QFile file("./Vip_OPeration_Temp.txt");

    if(file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<<"打开Vip_OPeration_Temp成功";
        QTextStream stream(&file);
        stream.setCodec("utf-8");
        stream<<temp_vip_info<<endl;
        qDebug()<<"传递信息文件写入成功";
    }
    file.close();
    return 1;
}

void StartPage::ShowVipConsumeInfo(StartPage::VipConsumeFlag flag)
{
    QString choice=this->ui->comboBox->currentText();
    qDebug()<<"choice=="<<choice;

    QStringList choiceList;
    choiceList=choice.split(" ");

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
    qDebug()<<"准备读";

    while(!file.atEnd())
    {
        QString line;
        line=file.readLine();
        if(line.size()==0)
        {
            qDebug()<<"当前文件为空或者第一行有误";
            return;
        }
        QStringList stringlist=line.split(" ");

        Vip*vip_temp=new Vip;

        vip_temp->Vip_name=stringlist[0];
        vip_temp->Vip_phone=stringlist[1];
        vip_temp->Vip_type_flag=stringlist[2];

        qDebug()<<"读一半";

        vip_temp->Year=stringlist[6].toFloat();
        vip_temp->Month=stringlist[7].toFloat();
        vip_temp->Day=stringlist[8].toFloat();
        qDebug()<<"读2/3";
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
        qDebug()<<"vip初始化成功";
        list_vip_consume.append(vip_temp);
    }

    qDebug()<<"list_vip_consume 添加 成功";

    int find_vip_num=0;
    for(auto single:list_vip_consume)
    {
        if(single->Vip_name==choiceList[0]&&single->Vip_phone==choiceList[1])
        {
            list_vip_consume_show.append(single);
            find_vip_num++;
        }
    }
    qDebug()<<"list_vip_consume_show 添加 成功";
    SetQTableWiget(find_vip_num,flag);

    if(find_vip_num>0)
    {
        this->ui->qTableWidget->show();
    }

}

void StartPage::SetQTableWiget(int num,StartPage::VipConsumeFlag flag)
{
    if(num<=0)
    {
        return;
    }
    ui->qTableWidget->setColumnCount(7);//设置列数
    ui->qTableWidget->setRowCount(num);//设置行数
    ui->qTableWidget->setWindowTitle("QTableWidget");

    qDebug()<<"设置行列数成功";
    //设置列标签
    QStringList m_Header;

    switch(flag)
    {
    case 1:
        m_Header<<QString("姓名")<<QString("手机号码")<<QString("消费类型")<<QString("折扣前消费金额")<<QString("会员享受的折扣")<<QString("折扣后消费金额")<<QString("消费生成时间");
        break;
    case 2:
        m_Header<<QString("姓名")<<QString("手机号码")<<QString("消费类型")<<QString("扣除前剩余次数")<<QString("本次扣除次数")<<QString("扣除后剩余次数")<<QString("消费生成时间");
        break;
    }

    qDebug()<<"开始设置内容";
    SetqTableWidgetContent(num,flag);

    qDebug()<<"设置内容成功";

    ui->qTableWidget->setHorizontalHeaderLabels(m_Header);//添加横向表头
    ui->qTableWidget->verticalHeader()->setVisible(true);//纵向表头可视化
    ui->qTableWidget->horizontalHeader()->setVisible(true);//横向表头可视化

    ui->qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中

    ui->qTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->qTableWidget->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色


    qDebug()<<"开始设置居中";
    for(int rows=0;rows<=num-1;rows++)
    {
        for(int columns=0;columns<7;columns++)
        {
            ui->qTableWidget->setColumnWidth(columns,145);
            ui->qTableWidget->setRowHeight(rows,28);

            ui->qTableWidget->item(rows,columns)->setTextAlignment(Qt::AlignCenter);//居中显示
            ui->qTableWidget->item(rows,columns)->setTextColor(QColor(0,0,0));//设置文本颜色
            ui->qTableWidget->item(rows,columns)->setFont(QFont("Helvetica"));//设置字体为黑体
        }
    }


    qDebug()<<"设置居中成功";

    ui->qTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置水平滚动条
    ui->qTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条

}

void StartPage::SetqTableWidgetContent(int num, StartPage::VipConsumeFlag flag)
{
    int rows=0;
    if(list_vip_consume.size()==0)
    {
        qDebug()<<"当前消费记录为空";
        return;
    }
    for(auto single:list_vip_consume_show)
    {
        for(int columns=0;columns<7;columns++)
        {
            if(columns==0)
            {
                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(single->Vip_name));
            }
            else if(columns==1)
            {
                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(single->Vip_phone));
            }
            else if(columns==2)
            {
                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(single->Vip_type_flag));
            }
            else if(columns==6)
            {
                QString date_str;
                date_str+=QString("%1").arg(single->Year);
                date_str+=" ";
                date_str+=QString("%1").arg(single->Month);
                date_str+=" ";
                date_str+=QString("%1").arg(single->Day);

                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(date_str));
            }
            switch(flag)
            {
            case 1:
            {
                if(columns==3)
                {
                    ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_remain_money,'f',2)));
                }
                else if(columns==4)
                {
                    ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_discount,'f',2)));
                }
                else if(columns==5)
                {
                    ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_consume_money,'f',2)));
                }
            }
                break;
            case 2:
            {
                if(columns==3)
                {
                    ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_discount,'f',2)));
                }
                else if(columns==4)
                {
                    ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_consume_Num,'f',2)));
                }
                else if(columns==5)
                {
                    ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_ramain_Num,'f',2)));
                }

            }
                break;

            }
        }

        rows++;
    }

}

void StartPage::RechargeVip(VipRechargeFlag flag)
{
    if(ui->lineEdit_5->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","请先查找出对应的会员");
        return;
    }
    bool bOk = false;
    float iMoney=0;

    switch(flag)
    {
    case 1:
        iMoney =QInputDialog::getDouble(this,
                                        "QInputDialog_Age",
                                        "请输入充值金额",
                                        100,				//默认值
                                        0,				//最小值
                                        100000,			//最大值
                                        5,				//步进
                                        &bOk);
        break;
    case 2:
        iMoney =QInputDialog::getDouble(this,
                                        "QInputDialog_Age",
                                        "请输入充值次数",
                                        100,				//默认值
                                        0,				//最小值
                                        100000,			//最大值
                                        5,				//步进
                                        &bOk);
        break;
    }


    int show_money=0;
    Vip * vip_recharge=new Vip;
    if (bOk && iMoney > 0)
    {
        add_vip.Read_Vip_Info();
        QList<Vip*>::iterator it;
        for(it=add_vip.list_vip.begin();it!=add_vip.list_vip.end();it++)
        {
            if((*it)->Vip_name==ui->lineEdit_5->text()&&(*it)->Vip_phone==ui->lineEdit_6->text())
            {
                vip_recharge=*it;

                switch(flag)
                {
                case 1:
                    vip_recharge->Vip_remain_money+=iMoney;
                    show_money=vip_recharge->Vip_remain_money;

                    break;
                case 2:
                    vip_recharge->Vip_ramain_Num+=iMoney;
                    show_money=vip_recharge->Vip_ramain_Num;

                    break;
                }

                add_vip.list_vip.erase(it);
                add_vip.list_vip.insert(it,vip_recharge);
                qDebug()<<"充值完毕，原文件修改";
                add_vip.Save_Vip_Info();
                if(it == add_vip.list_vip.end()) break;
                break;
            }
        }
    }
    else
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("通知"),QString("取消充值，无操作将自动返回 !"));
        QTimer::singleShot(2000,m_box,SLOT(accept()));
        m_box->exec();

        return;
    }
    add_vip.Read_Origin_Vip_Info();
    qDebug()<<" add_vip.list_vip_Orign.size=="<< add_vip.list_vip_Origin;

    QDate date=QDate::currentDate();
    switch(flag)
    {
    case 1:
        vip_recharge->Vip_remain_money=iMoney;

        vip_recharge->Year=date.year();
        vip_recharge->Month=date.month();
        vip_recharge->Day=date.day();

        add_vip.list_vip_Origin.append(vip_recharge);
        add_vip.Save_Origin_Vip_Info();
        qDebug()<<"充值完毕，新文件保存";
        ui->lineEdit_7->setText(QString::number(show_money,'f',2));
        break;
    case 2:
        vip_recharge->Vip_ramain_Num=iMoney;

        vip_recharge->Year=date.year();
        vip_recharge->Month=date.month();
        vip_recharge->Day=date.day();

        add_vip.list_vip_Origin.append(vip_recharge);
        add_vip.Save_Origin_Vip_Info();
        qDebug()<<"充值完毕，新文件保存";

        ui->lineEdit_4->setText(QString::number(show_money,'f',2));
        break;
    }
    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("通知"),QString("充值成功，无操作将自动返回 !"));
    QTimer::singleShot(2000,m_box,SLOT(accept()));
    m_box->exec();
}


void StartPage::Vip_Record()
{
    QMessageBox box(QMessageBox::Information, "会员记录", "请选择你要查找的记录");
    box.setStandardButtons(QMessageBox::Ok|QMessageBox::Open|QMessageBox::No);
    box.setButtonText(QMessageBox::Ok, QString("会员充值记录"));
    box.setButtonText(QMessageBox::Open, QString("会员消费记录"));
    box.setButtonText(QMessageBox::No, QString("返回"));
    box.setDefaultButton(QMessageBox::Ok);
    int ret= box.exec();
    switch(ret)
    {
    case QMessageBox::Ok:
        charged_vip_recored=new Charged_Vip_Record;
        charged_vip_recored->show();
        break;
    case QMessageBox::Open:
        consume_vip_record=new Consume_Vip_Record;
        consume_vip_record->show();
        break;
    default:
        break;
    }
}

void StartPage::Show_Vip_Info()
{
    add_vip.Read_Vip_Info();

    if(add_vip.list_vip.size()<=0)
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("通知"),QString("当前暂无会员记录!"));
        QTimer::singleShot(2000,m_box,SLOT(accept()));
        m_box->exec();
        return;
    }
    ui->tableWidget->show();

    ui->label->setText("当前查询时间内会员充值记录如下");
    ui->tableWidget->setColumnCount(7);//设置列数
    ui->tableWidget->setRowCount(add_vip.list_vip.size()+1);//设置行数
    ui->tableWidget->setWindowTitle("充值记录表");

    //设置列标签
    QStringList m_Header;
    m_Header<<QString("姓名")<<QString("手机号")<<QString("会员卡类型")<<QString("会员余额")<<QString("会员剩余次数")<<QString("充值时间")<<QString("统计");
    ui->tableWidget->setHorizontalHeaderLabels(m_Header);//添加横向表头
    ui->tableWidget->verticalHeader()->setVisible(true);//纵向表头可视化
    ui->tableWidget->horizontalHeader()->setVisible(true);//横向表头可视化

    //ui->tableWidget->setShowGrid(false);//隐藏栅格
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中
    //ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);//设置表格选择方式：设置表格为整列选中
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->tableWidget->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色

    int rows=0,money=0;
    for(auto single:add_vip.list_vip)
    {
        int discount_flag=0;
        if(single->Vip_type_flag=="按折扣消费")
        {
            discount_flag=1;
        }
        else if(single->Vip_type_flag=="按次数消费")
        {
            discount_flag=2;
        }
        for(int columns=0;columns<7;columns++)
        {
            if(columns==0)
            {
                ui->tableWidget->setItem(rows,columns,new QTableWidgetItem(single->Vip_name));
            }
            else if(columns==1)
            {
                ui->tableWidget->setItem(rows,columns,new QTableWidgetItem(single->Vip_phone));
            }
            else if(columns==5)
            {
                QString time_str;
                time_str=(QString("%1").arg(single->Year)+" "+QString("%1").arg(single->Month)+" "+QString("%1").arg(single->Day));
                ui->tableWidget->setItem(rows,columns,new QTableWidgetItem(time_str));
            }
            else if(columns==3)
            {
                if(discount_flag==1)
                {
                    ui->tableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_remain_money,'f',2)));
                }
                else if(discount_flag==2)
                {
                    ui->tableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(0,'f',2)));
                }

            }
            else if(columns==4)
            {
                if(discount_flag==1)
                {
                    ui->tableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(0,'f',2)));
                }
                else if(discount_flag==2)
                {
                    ui->tableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_ramain_Num,'f',2)));
                }
            }
            else if(columns==2)
            {
                ui->tableWidget->setItem(rows,columns,new QTableWidgetItem(single->Vip_type_flag));
            }

        }
        rows++;
        money+=single->Vip_remain_money;
    }

    qDebug()<<"表格初始化完成";
    for(int rows=0;rows<add_vip.list_vip.size();rows++)
    {
        //设置属性的时候如果表格里没有内容，无法设置
        for(int columns=0;columns<6;columns++)
        {
            ui->tableWidget->setColumnWidth(columns,150);
            ui->tableWidget->setRowHeight(rows,30);

            ui->tableWidget->item(rows,columns)->setTextAlignment(Qt::AlignCenter);//居中显示
            ui->tableWidget->item(rows,columns)->setTextColor(QColor(0,0,0));//设置文本颜色
            ui->tableWidget->item(rows,columns)->setFont(QFont("Helvetica"));//设置字体为黑体
        }
    }

    qDebug()<<"开始设置表格属性";
    ui->tableWidget->setItem(add_vip.list_vip.size(),0,new QTableWidgetItem(QString("充值总金额为")));
    ui->tableWidget->item(add_vip.list_vip.size(),0)->setTextAlignment(Qt::AlignCenter);//居中显示
    ui->tableWidget->item(add_vip.list_vip.size(),0)->setBackgroundColor(QColor(85,170,255));//设置前景颜色

    ui->tableWidget->setItem(add_vip.list_vip.size(),6,new QTableWidgetItem(QString::number(money,'f',2)));
    ui->tableWidget->item(add_vip.list_vip.size(),6)->setBackgroundColor(QColor(85,170,255));//设置前景颜色
    ui->tableWidget->item(add_vip.list_vip.size(),6)->setTextAlignment(Qt::AlignCenter);//居中显示

    qDebug()<<"设置表格属性完成";
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置水平滚动条
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条

    this->ui->tableWidget->show();
    add_vip.list_vip.clear();
}

void StartPage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix(":/Res/R-C (4).jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void StartPage::closeEvent(QCloseEvent *event)
{
    //this->temp_customer_consume_page.close();

}

void StartPage::OnBtnTempCustomConsumeClicked()
{
    int x=this->pos().x()+this->ui->line->x()*1.5;
    int y=this->pos().y()+this->ui->line_2->y()*1.5;
    temp_customer_consume_page.move(x,y);
    temp_customer_consume_page.show();
}

void StartPage::OnbtnAddVipClicked()
{
    add_vip.show();
}

void StartPage::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        this->ui->tableWidget->hide();
    }
}

void StartPage::on_Sum_Temp_Consume_triggered()
{
    int x=this->pos().x()+this->ui->line->x()*1.5;
    int y=this->pos().y()+this->ui->line_2->y()*1.5;
    temp_customer_consume_page.move(x,y);
    show_temp_customer_consume_sum.show();

}

void StartPage::on_pushButton_Find_clicked()
{
    ClearLineEdit();
    this->ui->lineEdit_Find->setText(ui->comboBox->currentText());

    if(list_temp.size()==1)
    {
        for(auto single :list_temp)
        {
            ShowVipInfo(single);
        }

    }
    else if(list_temp.size()>1)
    {

        QString choice =ui->comboBox->currentText();
        QStringList strList = choice.split(" ");

        for(auto single :list_temp)
        {
            if(single->Vip_name==strList[0]&&(single->Vip_phone==strList[1]||single->Vip_phone.indexOf(choice)!=-1))
            {
                ShowVipInfo(single);
                break;
            }

        }
    }

    this->ui->comboBox->clear();
    this->ui->comboBox->hide();
    list_temp.clear();
    add_vip.list_vip.clear();
    list_vip_consume.clear();
    list_vip_consume_show.clear();

}

void StartPage::on_lineEdit_Find_textEdited(const QString &arg1)
{
    // TransferVipInfo();
    ui->comboBox->clear();
    list_temp.clear();
    add_vip.list_vip.clear();

    QString choice;
    choice=ui->lineEdit_Find->text();
    qDebug()<<"(ui->lineEdit_Find->text())"<<ui->lineEdit_Find->text();
    if(choice.size()==0)
    {
        return;
    }
    qDebug()<<"choice==="<<choice;

    add_vip.Read_Vip_Info();

    for(auto single:add_vip.list_vip)
    {

        if(single->Vip_name==choice||single->Vip_phone==choice||single->Vip_phone.indexOf(choice)!=-1)
        {

            list_temp.append(single);
        }

    }

    qDebug()<<"list_temp.size=="<<list_temp.size();
    for(auto single:list_temp)
    {
        qDebug()<<single->Vip_name<<single->Vip_phone;
    }

    for(auto single:list_temp)
    {
        QString Item;
        Item+=single->Vip_name;
        Item+=" ";
        Item+=single->Vip_phone;
        ui->comboBox->addItem(Item);
    }
    this->ui->comboBox->show();

}
void StartPage::on_comboBox_activated(const QString &arg1)
{
    this->ui->lineEdit_Find->setText(ui->comboBox->currentText());
    this->ui->comboBox->hide();
}
//界面传递数据
void StartPage::OnBtnModifyVipClicked()
{
    TransferVipInfo();
    if(ui->lineEdit_5->text().size()<=0)
    {
        QMessageBox::warning(this, "错误","请先在右侧查找出对应的会员! ");
        return;
    }
    modify_vip=new Modify_Vip;
    this->ClearLineEdit();
    modify_vip->show();
}

void StartPage::OnBtnConsumeVipClicked()
{
    TransferVipInfo();
    if(ui->lineEdit_5->text().size()<=0)
    {
        QMessageBox::warning(this, "错误","请先在右侧查找出对应的会员! ");
        return;
    }
    consume_vip=new Consume_Vip;
    consume_vip->show();
}


