#ifndef LOGININ_H
#define LOGININ_H

#include <QMainWindow>
#include"createuser.h"


#include <QtCore/QCoreApplication>
#include <QtMultimedia/QMediaPlayer>
#include"startpage.h"

namespace Ui {
class LoginIn;
}

class LoginIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginIn(QWidget *parent = 0);
    ~LoginIn();


private slots:
    void on_pushButton_Create_clicked();

    void on_pushButtonLogin_clicked();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::LoginIn *ui;
    CreateUser createuser_page;
    StartPage startpage;
};

#endif // LOGININ_H
