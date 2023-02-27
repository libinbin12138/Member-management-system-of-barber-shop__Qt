#include "charged_vip_record.h"
#include "ui_charged_vip_record.h"

#include"vip.h"
#include<QDate>
#include<QString>
#include<QMessageBox>
#include<QDebug>

#include<QPainter>
Charged_Vip_Record::Charged_Vip_Record(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Charged_Vip_Record)
{
    ui->setupUi(this);

    this->setWindowTitle("会员充值记录");

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

    ui->qTableWidget->hide();
    add_vip=new Add_Vip;
     this->setWindowIcon(QIcon(":/image/mmexport1662627162101.jpg"));
}

Charged_Vip_Record::~Charged_Vip_Record()
{
    delete ui;
}

void Charged_Vip_Record::Set_PrintList(Charged_Vip_Record::PrintFlag flag)
{
    list_print.clear();
    add_vip->Read_Origin_Vip_Info();
    qDebug()<<"读取充值信息成功";
    QDate date;
    int Year=0;
    int Month=0;
    int Day=0;

    for(auto single:add_vip->list_vip_Origin)
    {
        switch(flag)
        {
        case 1:
            date=ui->dateEdit->date();
            Year=date.year();
            Month=date.month();
            Day=date.day();
            qDebug()<<"选择的时间为："<<date.toString("yyyy MM dd");
            if(single->Day==Day&&single->Month==Month&&single->Year==Year)
            {
                list_print.append(single);
            }
            break;
        case 2:
            date=ui->dateEdit_2->date();
            Year=date.year();
            Month=date.month();
            qDebug()<<"选择的时间为："<<date.toString("yyyy MM");
            if(single->Month==Month&&single->Year==Year)
            {
                list_print.append(single);
            }
            break;
        case 3:
            date=ui->dateEdit_3->date();
            Year=date.year();
            qDebug()<<"选择的时间为："<<date.toString("yyyy");
            if(single->Year==Year)
            {
                list_print.append(single);
            }
            break;
        }
    }
}

void Charged_Vip_Record::Set_QTableWidget(Charged_Vip_Record::PrintFlag flag)
{
    Set_PrintList(flag);
    if(list_print.size()<=0)
    {
        QMessageBox::warning(this,"警告","所选时间暂无充值记录");
        this->ui->pushButton->setEnabled(true);
        this->ui->pushButton_2->setEnabled(true);
        this->ui->pushButton_3->setEnabled(true);
        return;
    }
    ui->qTableWidget->show();

    ui->label->setText("当前查询时间内会员充值记录如下");
    ui->qTableWidget->setColumnCount(7);//设置列数
    ui->qTableWidget->setRowCount(list_print.size()+1);//设置行数
    ui->qTableWidget->setWindowTitle("充值记录表");

    //设置列标签
    QStringList m_Header;
    m_Header<<QString("姓名")<<QString("手机号")<<QString("会员卡类型")<<QString("充值金额")<<QString("充值次数")<<QString("充值时间")<<QString("统计");
    ui->qTableWidget->setHorizontalHeaderLabels(m_Header);//添加横向表头
    ui->qTableWidget->verticalHeader()->setVisible(true);//纵向表头可视化
    ui->qTableWidget->horizontalHeader()->setVisible(true);//横向表头可视化

    //ui->tableWidget->setShowGrid(false);//隐藏栅格
    ui->qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中
    //ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);//设置表格选择方式：设置表格为整列选中
    ui->qTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->qTableWidget->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色

    int rows=0,money=0;
    for(auto single:list_print)
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
                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(single->Vip_name));
            }
            else if(columns==1)
            {
                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(single->Vip_phone));
            }
            else if(columns==5)
            {
                QString time_str;
                time_str=(QString("%1").arg(single->Year)+" "+QString("%1").arg(single->Month)+" "+QString("%1").arg(single->Day));
                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(time_str));
            }
            else if(columns==3)
            {
                if(discount_flag==1)
                {
                    ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_remain_money,'f',2)));
                }
                else if(discount_flag==2)
                {
                    ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(0,'f',2)));
                }

            }
            else if(columns==4)
            {
                if(discount_flag==1)
                {
                    ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(0,'f',2)));
                }
                else if(discount_flag==2)
                {
                    ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_ramain_Num,'f',2)));
                }
            }
            else if(columns==2)
            {
                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(single->Vip_type_flag));
            }

        }

        if(single->Vip_type_flag=="按折扣消费")
        {
            money+=single->Vip_remain_money;
        }
        rows++;
    }

    qDebug()<<"表格初始化完成";
    for(int rows=0;rows<list_print.size();rows++)
    {
        //设置属性的时候如果表格里没有内容，无法设置
        for(int columns=0;columns<6;columns++)
        {
            ui->qTableWidget->setColumnWidth(columns,150);
            ui->qTableWidget->setRowHeight(rows,30);

            ui->qTableWidget->item(rows,columns)->setTextAlignment(Qt::AlignCenter);//居中显示
            ui->qTableWidget->item(rows,columns)->setTextColor(QColor(0,0,0));//设置文本颜色
            ui->qTableWidget->item(rows,columns)->setFont(QFont("Helvetica"));//设置字体为黑体
        }
    }

    qDebug()<<"开始设置表格属性";
    ui->qTableWidget->setItem(list_print.size(),0,new QTableWidgetItem(QString("统计充值金额为")));
    ui->qTableWidget->item(list_print.size(),0)->setTextAlignment(Qt::AlignCenter);//居中显示
    ui->qTableWidget->item(list_print.size(),0)->setBackgroundColor(QColor(85,170,255));//设置前景颜色

    ui->qTableWidget->setItem(list_print.size(),6,new QTableWidgetItem(QString::number(money,'f',2)));
    ui->qTableWidget->item(list_print.size(),6)->setBackgroundColor(QColor(85,170,255));//设置前景颜色
    ui->qTableWidget->item(list_print.size(),6)->setTextAlignment(Qt::AlignCenter);//居中显示

    qDebug()<<"设置表格属性完成";
    ui->qTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置水平滚动条
    ui->qTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条



}

void Charged_Vip_Record::closeEvent(QCloseEvent *event)
{
    add_vip->list_vip_Origin.clear();
    this->ui->qTableWidget->clear();
    this->ui->qTableWidget->hide();
    list_print.clear();
    this->ui->label->setText("请选择要查找的日期");
    this->ui->pushButton->setEnabled(true);
    this->ui->pushButton_2->setEnabled(true);
    this->ui->pushButton_3->setEnabled(true);
}


void Charged_Vip_Record::keyPressEvent(QKeyEvent *event)
{
    //绑定esc键触发的事件
    if (event->key() == Qt::Key_Escape)
    {

        if(ui->qTableWidget->isHidden())
        {
            this->close();
        }
        else
        {
            add_vip->list_vip_Origin.clear();
            ui->qTableWidget->clear();
            ui->qTableWidget->hide();
            list_print.clear();
            this->ui->label->setText("请选择要查找的日期");
            this->ui->pushButton->setEnabled(true);
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

void Charged_Vip_Record::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix(":/image/mmexport1604531021035.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void Charged_Vip_Record::on_pushButton_clicked()
{
    this->ui->pushButton->setEnabled(false);
    Set_QTableWidget(PrintFlag::PrintDay);
}

void Charged_Vip_Record::on_pushButton_2_clicked()
{
    this->ui->pushButton->setEnabled(false);
    Set_QTableWidget(PrintFlag::PrintMonth);
}

void Charged_Vip_Record::on_pushButton_3_clicked()
{
    this->ui->pushButton->setEnabled(false);
    Set_QTableWidget(PrintFlag::PrintYear);

}
