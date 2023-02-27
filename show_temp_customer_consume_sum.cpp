#include "show_temp_customer_consume_sum.h"
#include "ui_show_temp_customer_consume_sum.h"

#include<QFile>
#include<QDebug>
#include<QDate>
#include<QString>
#include<QStringList>
#include<QMessageBox>
#include<QPainter>

Show_Temp_customer_Consume_Sum::Show_Temp_customer_Consume_Sum(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Show_Temp_customer_Consume_Sum)
{
    ui->setupUi(this);
    this->setFixedSize(400,400);
    this->setWindowTitle("散客消费统计");

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

    //绑定回车键
    // connect(ui->dateEdit,SIGNAL(editingFinished()) , ui->pushButton, SLOT(click()), Qt::UniqueConnection);
 this->setWindowIcon(QIcon(":/image/mmexport1662627162101.jpg"));
}


Show_Temp_customer_Consume_Sum::~Show_Temp_customer_Consume_Sum()
{
    delete ui;
}

void Show_Temp_customer_Consume_Sum::ShowInfo()
{
    setWindowTitle(tr("散客消费统计"));//设置对话框的标题
    ui->qTableWidget->show();
    ui->label->setText("当前散客消费统计如下");
    ui->qTableWidget->setColumnCount(4);//设置列数
    ui->qTableWidget->setRowCount(list_vip_temp.size()+2);//设置行数
    ui->qTableWidget->setWindowTitle("QTableWidget");

    //设置列标签
    QStringList m_Header;
    m_Header<<QString("临时编号")<<QString("消费金额")<<QString("消费时间")<<QString("总金额统计");
    ui->qTableWidget->setHorizontalHeaderLabels(m_Header);//添加横向表头
    ui->qTableWidget->verticalHeader()->setVisible(true);//纵向表头可视化
    ui->qTableWidget->horizontalHeader()->setVisible(true);//横向表头可视化

    //ui->tableWidget->setShowGrid(false);//隐藏栅格
    ui->qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中
    //ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);//设置表格选择方式：设置表格为整列选中
    ui->qTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->qTableWidget->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色

    int rows=0,temp_Id=0,money=0;
    for(auto single:list_vip_temp)
    {
        temp_Id++;
        for(int columns=0;columns<3;columns++)
        {
            if(columns==0)
            {
                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(temp_Id,'f',2)));
            }
            else if(columns==1)
            {
                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(QString::number(single->Vip_consume_money,'f',2)));
            }
            else if(columns==2)
            {
                QString time_str;
                time_str=(QString("%1").arg(single->Year)+" "+QString("%1").arg(single->Month)+" "+QString("%1").arg(single->Day));
                ui->qTableWidget->setItem(rows,columns,new QTableWidgetItem(time_str));
            }

        }
        rows++;
        money+=single->Vip_consume_money;
    }

    for(int rows=0;rows<list_vip_temp.size();rows++)
    {
        for(int columns=0;columns<3;columns++)
        {
            ui->qTableWidget->setColumnWidth(columns,125);
            ui->qTableWidget->setRowHeight(rows,30);

            ui->qTableWidget->item(rows,columns)->setTextAlignment(Qt::AlignCenter);//居中显示
            ui->qTableWidget->item(rows,columns)->setTextColor(QColor(0,0,0));//设置文本颜色
            ui->qTableWidget->item(rows,columns)->setFont(QFont("Helvetica"));//设置字体为黑体
        }
    }
    //如果是空格，无法设置背景等等
    //统计消费设置
    ui->qTableWidget->setItem(list_vip_temp.size(),0,new QTableWidgetItem(QString("统计消费")));
    ui->qTableWidget->item(list_vip_temp.size(),0)->setTextAlignment(Qt::AlignCenter);//居中显示
    ui->qTableWidget->item(list_vip_temp.size(),0)->setBackgroundColor(QColor(85,170,255));//设置前景颜色

    ui->qTableWidget->setItem(list_vip_temp.size(),3,new QTableWidgetItem(QString::number(money,'f',2)));
    ui->qTableWidget->item(list_vip_temp.size(),3)->setBackgroundColor(QColor(85,170,255));//设置前景颜色
    ui->qTableWidget->item(list_vip_temp.size(),3)->setTextAlignment(Qt::AlignCenter);//居中显示

    // ui->qTableWidget->setSpan(2, 2,2 ,1);//合并单元格
    // ui->qTableWidget->setItem(2, 2, new QTableWidgetItem(QIcon("E:\\Qt_Project\\QTableWidget\\1.jpg"), "路飞"));//插入图片
    ui->qTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置水平滚动条
    ui->qTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//设置垂直滚动条
    //设置行和列的大小设为与内容相匹配（如果设置了宽高就不要用了）
    //ui->qTableWidget->resizeColumnsToContents();
    //ui->qTableWidget->resizeRowsToContents();

    //    QString strText = ui->qTableWidget->item(1, 1)->text();//获取单元格的内容
    //    qDebug()<<"单元格内容："<<strText;//输出单元格内容

    //设置列标签
    //    QStringList HStrList;
    //    HStrList.push_back(QString("临时编号"));
    //    HStrList.push_back(QString("消费金额"));
    //    HStrList.push_back(QString("消费时间"));
    //    HStrList.push_back(QString("city"));
    //    HStrList.push_back(QString("other"));
    //设置行列数(只有列存在的前提下，才可以设置列标签)
    //int HlableCnt = HStrList.count();
    //    ui->qTableWidget->setRowCount(10);
    //    ui->qTableWidget->setColumnCount(HlableCnt);
    //设置列标签
    //ui->qTableWidget->setHorizontalHeaderLabels(HStrList);

}

void Show_Temp_customer_Consume_Sum::closeEvent(QCloseEvent *event)
{
    ui->qTableWidget->clear();
    ui->qTableWidget->hide();
    list_vip_temp.clear();
    temp_customer_consume.list_vip.clear();
    this->ui->label->setText("请选择要查找的日期");
    this->ui->pushButton->setEnabled(true);
}

void Show_Temp_customer_Consume_Sum::keyPressEvent(QKeyEvent *event)
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
            ui->qTableWidget->clear();
            ui->qTableWidget->hide();
            list_vip_temp.clear();
            temp_customer_consume.list_vip.clear();
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

void Show_Temp_customer_Consume_Sum::paintEvent(QPaintEvent *event)
{

        QPainter painter(this);
        QPixmap pix(":/image/mmexport1604531025059.jpg");
        painter.drawPixmap(0,0,this->width(),this->height(),pix);


}

void Show_Temp_customer_Consume_Sum::on_pushButton_clicked()
{
    //    QDate time = QDate::currentDate();
    //    QString time_str = time.toString("yyyy MM dd");
    this->ui->pushButton->setEnabled(false);
    list_vip_temp.clear();
    temp_customer_consume.list_vip.clear();

    temp_customer_consume.Read_Temp_Customer_Consume();

    QDate date=ui->dateEdit->date();
    int Year=0;
    Year=date.year();
    int Month=0;
    Month=date.month();
    int Day=0;
    Day=date.day();

    int sum_num=0;
    for(auto single :temp_customer_consume.list_vip)
    {
        if(single->Year==Year&&single->Month==Month&&single->Day==Day)
        {
            list_vip_temp.append(single);
        }
    }
    if(list_vip_temp.size()==0)
    {
        //QMessageBox::warning(this, "错误","缺少关键信息的输入! ");
        QMessageBox::warning(this,"空","当前所选时间暂无消费记录");
        list_vip_temp.clear();
        temp_customer_consume.list_vip.clear();
        this->ui->pushButton->setEnabled(true);
        return;
    }
    else
    {
        for(auto single :list_vip_temp)
        {
            qDebug()<<single->Vip_consume_money<<" "<<single->Year<<" "<<single->Month<<single->Day<<endl;
        }
    }
    ShowInfo();

    list_vip_temp.clear();
    temp_customer_consume.list_vip.clear();
}

void Show_Temp_customer_Consume_Sum::on_pushButton_2_clicked()
{
    list_vip_temp.clear();
    temp_customer_consume.list_vip.clear();

    temp_customer_consume.Read_Temp_Customer_Consume();

    QDate date=ui->dateEdit_2->date();
    int Year=0;
    Year=date.year();
    int Month=0;
    Month=date.month();
    qDebug()<<"Year=="<<Year;
    qDebug()<<"Month=="<<Month;

    int sum_num=0;
    for(auto single :temp_customer_consume.list_vip)
    {
        if(single->Year==Year&&single->Month==Month)
        {
            list_vip_temp.append(single);
        }
    }
    if(list_vip_temp.size()==0)
    {
        //QMessageBox::warning(this, "错误","缺少关键信息的输入! ");
        QMessageBox::warning(this,"空","当前所选时间暂无消费记录");
        list_vip_temp.clear();
        temp_customer_consume.list_vip.clear();
         this->ui->pushButton_2->setEnabled(true);
        return;
    }
    else
    {
        for(auto single :list_vip_temp)
        {
            qDebug()<<single->Vip_consume_money<<" "<<single->Year<<" "<<single->Month<<single->Day<<endl;
        }
    }
    ShowInfo();

    list_vip_temp.clear();
    temp_customer_consume.list_vip.clear();
}

void Show_Temp_customer_Consume_Sum::on_pushButton_3_clicked()
{
    list_vip_temp.clear();
    temp_customer_consume.list_vip.clear();

    temp_customer_consume.Read_Temp_Customer_Consume();

    QDate date=ui->dateEdit_3->date();
    int Year=0;
    Year=date.year();

    int sum_num=0;
    for(auto single :temp_customer_consume.list_vip)
    {
        if(single->Year==Year)
        {
            list_vip_temp.append(single);
        }
    }
    if(list_vip_temp.size()==0)
    {
        //QMessageBox::warning(this, "错误","缺少关键信息的输入! ");
        QMessageBox::warning(this,"空","当前所选时间暂无消费记录");

        list_vip_temp.clear();
        temp_customer_consume.list_vip.clear();
         this->ui->pushButton_3->setEnabled(true);
        return;
    }
    else
    {
        for(auto single :list_vip_temp)
        {
            qDebug()<<single->Vip_consume_money<<" "<<single->Year<<" "<<single->Month<<single->Day<<endl;
        }
    }
    ShowInfo();

    list_vip_temp.clear();
    temp_customer_consume.list_vip.clear();
}
