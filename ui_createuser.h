/********************************************************************************
** Form generated from reading UI file 'createuser.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEUSER_H
#define UI_CREATEUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateUser
{
public:
    QAction *actionquit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *UserName;
    QLabel *label_2;
    QLineEdit *PassWord;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *CreateUser)
    {
        if (CreateUser->objectName().isEmpty())
            CreateUser->setObjectName(QStringLiteral("CreateUser"));
        CreateUser->resize(222, 243);
        actionquit = new QAction(CreateUser);
        actionquit->setObjectName(QStringLiteral("actionquit"));
        centralwidget = new QWidget(CreateUser);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        UserName = new QLineEdit(centralwidget);
        UserName->setObjectName(QStringLiteral("UserName"));

        gridLayout->addWidget(UserName, 0, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        PassWord = new QLineEdit(centralwidget);
        PassWord->setObjectName(QStringLiteral("PassWord"));
        PassWord->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        gridLayout->addWidget(PassWord, 1, 1, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 2, 0, 1, 2);

        CreateUser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CreateUser);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 222, 17));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        CreateUser->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionquit);

        retranslateUi(CreateUser);
        QObject::connect(actionquit, SIGNAL(triggered()), CreateUser, SLOT(close()));

        QMetaObject::connectSlotsByName(CreateUser);
    } // setupUi

    void retranslateUi(QMainWindow *CreateUser)
    {
        CreateUser->setWindowTitle(QApplication::translate("CreateUser", "MainWindow", Q_NULLPTR));
        actionquit->setText(QApplication::translate("CreateUser", "\350\277\224\345\233\236", Q_NULLPTR));
        label->setText(QApplication::translate("CreateUser", "\350\257\267\350\276\223\345\205\245\346\263\250\345\206\214\350\264\246\345\217\267\347\232\204\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("CreateUser", "\350\257\267\350\276\223\345\205\245\346\263\250\345\206\214\350\264\246\345\217\267\347\232\204\345\257\206\347\240\201", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CreateUser", "\346\263\250\345\206\214", Q_NULLPTR));
        menu->setTitle(QApplication::translate("CreateUser", "\350\217\234\345\215\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CreateUser: public Ui_CreateUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEUSER_H
