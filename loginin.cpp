#include "loginin.h"
#include "ui_loginin.h"

#include<QString>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include <QJsonParseError>


#include<QDebug>
#include<QFile>

#include<QPainter>
//#include <QMediaPlayer>
#include<QMessageBox>
#include<QTimer>
#include<QLineEdit>

LoginIn::LoginIn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginIn)
{
    ui->setupUi(this);

    this->setWindowTitle("尚雅美学理发管理系统");
    this->setWindowIcon(QIcon(":/image/mmexport1662627162101.jpg"));
    this->setFixedSize(480,653);

    connect(ui->PassWord, SIGNAL(returnPressed()), ui->pushButtonLogin, SLOT(click()), Qt::UniqueConnection);
    connect(ui->UserName, SIGNAL(returnPressed()), ui->pushButtonLogin, SLOT(click()), Qt::UniqueConnection);

    QLineEdit * LineEdit_Key=new QLineEdit(this);
    int x=this->pos().x()+80;
    int y=this->pos().y()+580;
    LineEdit_Key->setFixedSize(300,50);
    LineEdit_Key->setText("请联系管理员获取产品激活码");
    LineEdit_Key->move(x,y);
    LineEdit_Key->setAlignment( Qt::AlignHCenter);
}

LoginIn::~LoginIn()
{
    delete ui;
}

void LoginIn::on_pushButton_Create_clicked()
{
    createuser_page.show();

}

void LoginIn::on_pushButtonLogin_clicked()
{
    if(ui->PassWord->text().size()==0)
    {
        QMessageBox::warning(this,"警告","请输入用户的密码");
        return;
    }
    if(ui->UserName->text().size()==0)
    {
        QMessageBox::warning(this,"警告","请输入一个用户的账号");
        return;
    }
    QString UserName;
    QString PassWord;

    UserName=this->ui->UserName->text();
    PassWord=this->ui->PassWord->text();

    QJsonObject LoginUser;

    LoginUser["Password"]=PassWord;
    LoginUser["UserName"]=UserName;

    QFile loadFile(QApplication::applicationDirPath()+"./Login.json");

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << " 打开 Login.Json 失败";
        return;
    }
    else
    {
        qDebug() << " 打开 Login.Json 成功";

    }

    QByteArray byteArray = loadFile.readAll();
    loadFile.close();

    QJsonParseError jsonError;

    QJsonDocument doucment(QJsonDocument::fromJson(byteArray, &jsonError)); // 转化为 JSON 文档

    QJsonObject rootObj = doucment.object();
    if (jsonError.error == QJsonParseError::NoError)
    {
        // 解析未发生错误
        qDebug()<<" 解析未发生错误 ";

        if(rootObj.contains("LoginArray") && rootObj["LoginArray"].isArray())
        { // JSON 文档为数组
            qDebug() << "是数组 ";
            QJsonArray arr=rootObj["LoginArray"].toArray();
            int nSize = arr.size();  // 获取数组大小

            for (int i = 0; i < nSize; ++i)
            {
                if(LoginUser["UserName"].toString()==arr[i].toObject()["UserName"].toString()
                        &&
                        LoginUser["Password"].toString()==arr[i].toObject()["Password"].toString())
                {
                    qDebug()<<arr[i].toObject()["UserName"];
                    qDebug()<<arr[i].toObject()["Password"];
                    qDebug()<<"相等";

                    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("通知"),QString("账号核验成功，即将登陆!"));
                    QTimer::singleShot(1500,m_box,SLOT(accept()));
                    m_box->exec();

                    this->close();
                    startpage.show();
                    return;
                }
            }
        }
    }

    QMessageBox::warning(this,"警告","账号或密码错误，请重新输入");

}



void LoginIn::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix(":/Res/R-C.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
