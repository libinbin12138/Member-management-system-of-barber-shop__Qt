#include "createuser.h"
#include "ui_createuser.h"
#include<QString>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include<QDebug>
#include<QFile>
#include <windows.h>
#include<QMessageBox>
#include<QTimer>
#include<QPainter>

CreateUser::CreateUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateUser)
{
    ui->setupUi(this);
    this->setFixedSize(350,600);
     this->setWindowIcon(QIcon(":/image/mmexport1662627162101.jpg"));
}

CreateUser::~CreateUser()
{
    delete ui;
}

void CreateUser::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix(":/image/mmexport1604530988404.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void CreateUser::on_pushButton_clicked()
{
 //读配置文件
    QFile loadFile(QApplication::applicationDirPath()+"./Login.json");

        if(!loadFile.open(QIODevice::ReadOnly))
        {
            qDebug() << " Login.Json 不存在 ";

        }
        else
        {
            qDebug() << " 打开 Login.Json 成功 ";

        }

        QByteArray byteArray = loadFile.readAll();
        loadFile.close();

        QJsonParseError jsonError;

        QJsonDocument doucment(QJsonDocument::fromJson(byteArray, &jsonError)); // 转化为 JSON 文档

        QJsonObject rootObj = doucment.object();

        //新增用户
    QString UserName=this->ui->UserName->text();
    QString PassWord=ui->PassWord->text();

        // 构建 JSON 对象
        QJsonObject json;
        // 构建 JSON 文档
      QJsonDocument Newdocument;

      QJsonArray arr=rootObj["LoginArray"].toArray();

       QJsonObject Member;     //定义数组成员
       Member["UserName"] = UserName;
       Member["Password"] =PassWord;
       arr.append(Member);

       json["LoginArray"] = arr;

       Newdocument.setObject(json);

        QFile file(QApplication::applicationDirPath()+"./Login.json");
           if(!file.open(QIODevice::WriteOnly)) {
               qDebug() << "File open failed!";
           } else {
               qDebug() <<"File open successfully!";
           }


           int num=file.write(Newdocument.toJson(QJsonDocument::Indented)); //Indented:表示自动添加/n回车符

           file.close();

           if(num==-1)
           {
                qDebug() <<"创建用户失败";
           }
           else
           {
               QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("通知"),QString("创建用户成功，即将自动返回!"));
               QTimer::singleShot(2000,m_box,SLOT(accept()));
               m_box->exec();

              this->close();
           }
}
