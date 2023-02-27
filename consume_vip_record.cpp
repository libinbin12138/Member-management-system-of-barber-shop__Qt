#include "consume_vip_record.h"
#include "ui_consume_vip_record.h"

#include<QMessageBox>
#include<QString>
#include<QDebug>
#include<QPainter>

Consume_Vip_Record::Consume_Vip_Record(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Consume_Vip_Record)
{
    ui->setupUi(this);

    this->setWindowTitle("会员消费记录");

    //QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate(), this);
    QDateTimeEdit *dateEdit=this->ui->dateEdit;
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setMinimumDate(QDate::currentDate().addDays(-365*3));  // -365天
    dateEdit->setMaximumDate(QDate::currentDate().addDays(365*3));  // +365天
    dateEdit->setCalendarPopup(true);

    QDateTimeEdit *dateEdit2=this->ui->dateEdit_2;
    dateEdit2->setDate(QDate::currentDate());
    dateEdit2->setMinimumDate(QDate::currentDate().addDays(-365*3));  // -365天
    dateEdit2->setMaximumDate(QDate::currentDate().addDays(365*3));  // +365天

    QDateTimeEdit *dateEdit3=this->ui->dateEdit_3;
    dateEdit3->setDate(QDate::currentDate());
    dateEdit3->setMinimumDate(QDate::currentDate().addDays(-365*3));  // -365天
    dateEdit3->setMaximumDate(QDate::currentDate().addDays(365*3));  // +365天



    ui->qTableWidget1->hide();
    ui->qTableWidget2->hide();

    startpage=new StartPage;
 this->setWindowIcon(QIcon(":/image/mmexport1662627162101.jpg"));
}

Consume_Vip_Record::~Consume_Vip_Record()
{
    delete ui;
}

void Consume_Vip_Record::Consume_Vip_Info(Consume_Vip_Record::PrintFlag flag)
{
    list_vip_consume1.clear();
    list_vip_consume2.clear();
    list_vip_consume_show1.clear();
    list_vip_consume_show2.clear();

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

        int consume_flag=0;
        if(vip_temp->Vip_type_flag=="按折扣消费")
        {
            consume_flag=1;
        }
        else if(vip_temp->Vip_type_flag=="按次数消费")
        {
            consume_flag=2;
        }
        qDebug()<<"consume_flag=="<<consume_flag;

        switch(consume_flag)
        {
        case 1:
            vip_temp->Vip_consume_money=stringlist[5].toFloat();//获取折扣后消费金额
            vip_temp->Vip_discount=stringlist[4].toFloat();
            vip_temp->Vip_remain_money=stringlist[3].toFloat();//用Vip_remain_money获取折扣前消费金额
            list_vip_consume1.append(vip_temp);
            break;

        case 2:
            vip_temp->Vip_ramain_Num=stringlist[5].toFloat();//获取消费后次数
            vip_temp->Vip_consume_Num=stringlist[4].toFloat();
            vip_temp->Vip_discount=stringlist[3].toFloat();//用Vip_discount获取消费前次数
            list_vip_consume2.append(vip_temp);
            break;
        }

        qDebug()<<"vip初始化成功";
    }

    if(list_vip_consume1.size()==0&&list_vip_consume2.size()==0)
    {
        QMessageBox::warning(this,"警告","当前所选时间暂无消费信息");
        this->ui->pushButton->setEnabled(true);
        this->ui->pushButton_2->setEnabled(true);
        this->ui->pushButton_3->setEnabled(true);
        return;
    }
    qDebug()<<"list_vip_consume 1 2添加 成功";

    SetPrintList(flag);
    if(list_vip_consume_show1.size()==0&&list_vip_consume_show2.size()==0)
    {
        QMessageBox::warning(this,"警告","当前所选时间暂无消费信息");
        this->ui->pushButton->setEnabled(true);
        this->ui->pushButton_2->setEnabled(true);
        this->ui->pushButton_3->setEnabled(true);
        return;
    }
    qDebug()<<"list_vip_consume_show 1 2添加 成功";

    SetQTableWidget1(flag);
    SetQTableWidget2(flag);
}

void Consume_Vip_Record::SetPrintList(Consume_Vip_Record::PrintFlag flag)
{
    int Year=0;
    int Month=0;
    int Day=0;
    int find_vip_num1=0,find_vip_num2=0;
    QDate date;

    for(auto single:list_vip_consume1)
    {
        switch (flag) {
        case 1:
            date=ui->dateEdit->date();
            Year=date.year();
            Month=date.month();
            Day=date.day();
            qDebug()<<"选择的时间为："<<date.toString("yyyy MM dd");
            if(single->Day==Day&&single->Month==Month&&single->Year==Year)
            {
                list_vip_consume_show1.append(single);
            }
            break;
        case 2:
            date=ui->dateEdit_2->date();
            Year=date.year();
            Month=date.month();
            qDebug()<<"选择的时间为："<<date.toString("yyyy MM");
            if(single->Month==Month&&single->Year==Year)
            {
                list_vip_consume_show1.append(single);
            }
            break;
        case 3:
            date=ui->dateEdit_3->date();
            Year=date.year();
            qDebug()<<"选择的时间为："<<date.toString("yyyy");
            if(single->Year==Year)
            {
                list_vip_consume_show1.append(single);
            }
            break;

        }
    }
    qDebug()<<"list_vip_consume_show1 添加 成功";

    for(auto single:list_vip_consume2)
    {
        switch (flag) {
        case 1:
            date=ui->dateEdit->date();
            Year=date.year();
            Month=date.month();
            Day=date.day();
            qDebug()<<"选择的时间为："<<date.toString("yyyy MM dd");
            if(single->Day==Day&&single->Month==Month&&single->Year==Year)
            {
                list_vip_consume_show2.append(single);
            }
            break;
        case 2:
            date=ui->dateEdit->date();
            Year=date.year();
            Month=date.month();
            qDebug()<<"选择的时间为："<<date.toString("yyyy MM");
            if(single->Month==Month&&single->Year==Year)
            {
                list_vip_consume_show2.append(single);
            }
            break;
        case 3:
            date=ui->dateEdit->date();
            Year=date.year();
            qDebug()<<"选择的时间为："<<date.toString("yyyy");
            if(single->Year==Year)
            {
                list_vip_consume_show2.append(single);
            }
            break;

        }
    }
    qDebug()<<"list_vip_consume_show2 添加 成功";
}

void Consume_Vip_Record::SetQTableWidget1(Consume_Vip_Record::PrintFlag flag)
{
    if(this->list_vip_consume_show1.size()<=0)
    {
        return;
    }

    ui->label->setText("当前查询时间内会员消费记录如下");
    ui->qTableWidget1->setColumnCount(7);//设置列数
    ui->qTableWidget1->setRowCount(list_vip_consume_show1.size()+1);//设置行数
    ui->qTableWidget1->setWindowTitle("消费记录表");

    //设置列标签
    QStringList m_Header;
    m_Header<<QString("姓名")<<QString("手机号")<<QString("会员卡类型")<<QString("折扣前金额")<<QString("享受折扣数")<<QString("折扣后金额")<<QString("消费生成时间");
    ui->qTableWidget1->setHorizontalHeaderLabels(m_Header);//添加横向表头
    ui->qTableWidget1->verticalHeader()->setVisible(true);//纵向表头可视化
    ui->qTableWidget1->horizontalHeader()->setVisible(true);//横向表头可视化

    //ui->qTableWidget1->setShowGrid(false);//隐藏栅格
    ui->qTableWidget1->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->qTableWidget1->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中
    //ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);//设置表格选择方式：设置表格为整列选中
    ui->qTableWidget1->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->qTableWidget1->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色

    int rows=0,Consume_money=0;
    for(auto single:list_vip_consume_show1)
    {

        for(int columns=0;columns<7;columns++)
        {
            if(columns==0)
            {
                ui->qTableWidget1->setItem(rows,columns,new QTableWidgetItem(single->Vip_name));
            }
            else if(columns==1)
            {
                ui->qTableWidget1->setItem(rows,columns,new QTableWidgetItem(single->Vip_phone));
            }
            else if(columns==3)
            {
                ui->qTableWidget1->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_remain_money,'f',2)));
            }

            else if(columns==4)
            {
                ui->qTableWidget1->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_discount,'f',2)));
            }
            else if(columns==5)
            {
                ui->qTableWidget1->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_consume_money,'f',2)));
            }
            else if(columns==2)
            {
                ui->qTableWidget1->setItem(rows,columns,new QTableWidgetItem(single->Vip_type_flag));
            }
            else if(columns==6)
            {
                QString time_str;
                time_str=(QString("%1").arg(single->Year)+" "+QString("%1").arg(single->Month)+" "+QString("%1").arg(single->Day));
                ui->qTableWidget1->setItem(rows,columns,new QTableWidgetItem(time_str));
            }
        }
        rows++;
        Consume_money+=single->Vip_consume_money;
    }

    qDebug()<<"表格初始化完成";
    for(int rows=0;rows<list_vip_consume_show1.size();rows++)
    {
        //设置属性的时候如果表格里没有内容，无法设置
        for(int columns=0;columns<7;columns++)
        {
            ui->qTableWidget1->setColumnWidth(columns,150);
            ui->qTableWidget1->setRowHeight(rows,30);

            ui->qTableWidget1->item(rows,columns)->setTextAlignment(Qt::AlignCenter);//居中显示
            ui->qTableWidget1->item(rows,columns)->setTextColor(QColor(0,0,0));//设置文本颜色
            ui->qTableWidget1->item(rows,columns)->setFont(QFont("Helvetica"));//设置字体为黑体
        }
    }

    qDebug()<<"开始设置表格属性";
    ui->qTableWidget1->setItem(list_vip_consume_show1.size(),0,new QTableWidgetItem(QString("统计折扣后消费")));
    ui->qTableWidget1->item(list_vip_consume_show1.size(),0)->setTextAlignment(Qt::AlignCenter);//居中显示
    ui->qTableWidget1->item(list_vip_consume_show1.size(),0)->setBackgroundColor(QColor(85,170,255));//设置前景颜色

    ui->qTableWidget1->setItem(list_vip_consume_show1.size(),5,new QTableWidgetItem(QString::number(Consume_money,'f',2)));
    ui->qTableWidget1->item(list_vip_consume_show1.size(),5)->setBackgroundColor(QColor(85,170,255));//设置前景颜色
    ui->qTableWidget1->item(list_vip_consume_show1.size(),5)->setTextAlignment(Qt::AlignCenter);//居中显示

    qDebug()<<"设置表格属性完成";
    ui->qTableWidget1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置水平滚动条
    ui->qTableWidget1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条

    this->ui->qTableWidget1->show();
}

void Consume_Vip_Record::SetQTableWidget2(Consume_Vip_Record::PrintFlag flag)
{
    if(this->list_vip_consume_show2.size()<=0)
    {
        return;
    }
    ui->label->setText("当前查询时间内会员消费记录如下");
    ui->qTableWidget2->setColumnCount(7);//设置列数
    ui->qTableWidget2->setRowCount(list_vip_consume_show2.size()+1);//设置行数
    ui->qTableWidget2->setWindowTitle("消费记录表");

    //设置列标签
    QStringList m_Header;
    m_Header<<QString("姓名")<<QString("手机号")<<QString("会员卡类型")<<QString("消费前次数")<<QString("扣除次数")<<QString("消费后次数")<<QString("消费生成时间");
    ui->qTableWidget2->setHorizontalHeaderLabels(m_Header);//添加横向表头
    ui->qTableWidget2->verticalHeader()->setVisible(true);//纵向表头可视化
    ui->qTableWidget2->horizontalHeader()->setVisible(true);//横向表头可视化

    //ui->qTableWidget1->setShowGrid(false);//隐藏栅格
    ui->qTableWidget2->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->qTableWidget2->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中
    //ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);//设置表格选择方式：设置表格为整列选中
    ui->qTableWidget2->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->qTableWidget2->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色

    int rows=0,Consume_num=0;
    for(auto single:list_vip_consume_show2)
    {

        for(int columns=0;columns<7;columns++)
        {
            if(columns==0)
            {
                ui->qTableWidget2->setItem(rows,columns,new QTableWidgetItem(single->Vip_name));
            }
            else if(columns==1)
            {
                ui->qTableWidget2->setItem(rows,columns,new QTableWidgetItem(single->Vip_phone));
            }
            else if(columns==3)
            {
                ui->qTableWidget2->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_discount,'f',2)));
            }

            else if(columns==4)
            {
                ui->qTableWidget2->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_consume_Num,'f',2)));
            }
            else if(columns==5)
            {
                ui->qTableWidget2->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_remain_money,'f',2)));
            }
            else if(columns==2)
            {
                ui->qTableWidget2->setItem(rows,columns,new QTableWidgetItem(single->Vip_type_flag));
            }
            else if(columns==6)
            {
                QString time_str;
                time_str=(QString("%1").arg(single->Year)+" "+QString("%1").arg(single->Month)+" "+QString("%1").arg(single->Day));
                ui->qTableWidget2->setItem(rows,columns,new QTableWidgetItem(time_str));
            }
        }
        rows++;
        Consume_num+=single->Vip_consume_Num;
    }

    qDebug()<<"表格初始化完成";
    for(int rows=0;rows<list_vip_consume_show2.size();rows++)
    {
        //设置属性的时候如果表格里没有内容，无法设置
        for(int columns=0;columns<7;columns++)
        {
            ui->qTableWidget2->setColumnWidth(columns,150);
            ui->qTableWidget2->setRowHeight(rows,30);

            ui->qTableWidget2->item(rows,columns)->setTextAlignment(Qt::AlignCenter);//居中显示
            ui->qTableWidget2->item(rows,columns)->setTextColor(QColor(0,0,0));//设置文本颜色
            ui->qTableWidget2->item(rows,columns)->setFont(QFont("Helvetica"));//设置字体为黑体
        }
    }

    qDebug()<<"开始设置表格属性";
    ui->qTableWidget2->setItem(list_vip_consume_show2.size(),0,new QTableWidgetItem(QString("按次数共消费")));
    ui->qTableWidget2->item(list_vip_consume_show2.size(),0)->setTextAlignment(Qt::AlignCenter);//居中显示
    ui->qTableWidget2->item(list_vip_consume_show2.size(),0)->setBackgroundColor(QColor(85,170,255));//设置前景颜色

    ui->qTableWidget2->setItem(list_vip_consume_show2.size(),5,new QTableWidgetItem(QString::number(Consume_num,'f',2)));
    ui->qTableWidget2->item(list_vip_consume_show2.size(),5)->setBackgroundColor(QColor(85,170,255));//设置前景颜色
    ui->qTableWidget2->item(list_vip_consume_show2.size(),5)->setTextAlignment(Qt::AlignCenter);//居中显示

    qDebug()<<"设置表格属性完成";
    ui->qTableWidget2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置水平滚动条
    ui->qTableWidget2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条

    this->ui->qTableWidget2->show();
}
void Consume_Vip_Record::closeEvent(QCloseEvent *event)
{

    this->ui->qTableWidget1->clear();
    this->ui->qTableWidget1->hide();

    this->ui->qTableWidget2->clear();
    this->ui->qTableWidget2->hide();

    this->list_vip_consume1.clear();
    list_vip_consume2.clear();
    list_vip_consume_show1.clear();
    list_vip_consume_show2.clear();

    this->ui->pushButton->setEnabled(true);
    this->ui->pushButton_2->setEnabled(true);
    this->ui->pushButton_3->setEnabled(true);

    this->ui->label->setText("请选择要查找的日期");

}

void Consume_Vip_Record::keyPressEvent(QKeyEvent *event)
{
    //绑定esc键触发的事件
    if (event->key() == Qt::Key_Escape)
    {

        if(ui->qTableWidget1->isHidden()&&ui->qTableWidget2->isHidden())
        {
            this->close();
        }
        else
        {
            this->ui->qTableWidget1->clear();
            this->ui->qTableWidget1->hide();

            this->ui->qTableWidget2->clear();
            this->ui->qTableWidget2->hide();

            this->list_vip_consume1.clear();
            list_vip_consume2.clear();
            list_vip_consume_show1.clear();
            list_vip_consume_show2.clear();

            this->ui->pushButton->setEnabled(true);
            this->ui->pushButton_2->setEnabled(true);
            this->ui->pushButton_3->setEnabled(true);

            this->ui->label->setText("请选择要查找的日期");
            return;
        }
    }
    else if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return)
    {
        qDebug()<<"捕获Key_Enter";
        // 判断鼠标是否在pushButton上
        if (ui->dateEdit->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            qDebug()<<"鼠标在dateEdit上";
            this->on_pushButton_clicked();
        }
        else if(ui->dateEdit_2->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            qDebug()<<"鼠标在dateEdit2上";
            this->on_pushButton_2_clicked();
        }
        else if(ui->dateEdit_3->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        {
            qDebug()<<"鼠标在dateEdit2上";
            this->on_pushButton_3_clicked();
        }
    }
}

void Consume_Vip_Record::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix(":/image/mmexport1604531021035.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void Consume_Vip_Record::on_pushButton_clicked()
{
    this->ui->pushButton->setEnabled(false);
    Consume_Vip_Info(PrintFlag::PrintDay);
}

void Consume_Vip_Record::on_pushButton_2_clicked()
{
    this->ui->pushButton_2->setEnabled(false);
    Consume_Vip_Info(PrintFlag::PrintMonth);
}

void Consume_Vip_Record::on_pushButton_3_clicked()
{
    this->ui->pushButton_3->setEnabled(false);
    Consume_Vip_Info(PrintFlag::PrintYear);
}
