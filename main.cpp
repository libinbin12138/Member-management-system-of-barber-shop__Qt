#include "mainwindow.h"
#include <QApplication>

#include"loginin.h"
#include"startpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginIn login;
    login.show();
//    StartPage startpage;
//    startpage.show();

    return a.exec();
}
