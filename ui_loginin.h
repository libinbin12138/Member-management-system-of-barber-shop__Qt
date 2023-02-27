/********************************************************************************
** Form generated from reading UI file 'loginin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGININ_H
#define UI_LOGININ_H

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

class Ui_LoginIn
{
public:
    QAction *actionquit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *UserName;
    QLabel *label;
    QLineEdit *PassWord;
    QPushButton *pushButton_Create;
    QPushButton *pushButtonLogin;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *LoginIn)
    {
        if (LoginIn->objectName().isEmpty())
            LoginIn->setObjectName(QStringLiteral("LoginIn"));
        LoginIn->resize(271, 301);
        actionquit = new QAction(LoginIn);
        actionquit->setObjectName(QStringLiteral("actionquit"));
        centralWidget = new QWidget(LoginIn);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        UserName = new QLineEdit(centralWidget);
        UserName->setObjectName(QStringLiteral("UserName"));

        gridLayout->addWidget(UserName, 0, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        PassWord = new QLineEdit(centralWidget);
        PassWord->setObjectName(QStringLiteral("PassWord"));
        PassWord->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        gridLayout->addWidget(PassWord, 1, 1, 1, 1);

        pushButton_Create = new QPushButton(centralWidget);
        pushButton_Create->setObjectName(QStringLiteral("pushButton_Create"));

        gridLayout->addWidget(pushButton_Create, 2, 0, 1, 1);

        pushButtonLogin = new QPushButton(centralWidget);
        pushButtonLogin->setObjectName(QStringLiteral("pushButtonLogin"));

        gridLayout->addWidget(pushButtonLogin, 2, 1, 1, 1);

        LoginIn->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LoginIn);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 271, 17));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        LoginIn->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionquit);

        retranslateUi(LoginIn);
        QObject::connect(actionquit, SIGNAL(triggered()), LoginIn, SLOT(close()));

        QMetaObject::connectSlotsByName(LoginIn);
    } // setupUi

    void retranslateUi(QMainWindow *LoginIn)
    {
        LoginIn->setWindowTitle(QApplication::translate("LoginIn", "LoginIn", Q_NULLPTR));
        actionquit->setText(QApplication::translate("LoginIn", "\351\200\200\345\207\272", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginIn", "\350\264\246\345\217\267", Q_NULLPTR));
        label->setText(QApplication::translate("LoginIn", "\345\257\206\347\240\201", Q_NULLPTR));
        pushButton_Create->setText(QApplication::translate("LoginIn", "\346\263\250\345\206\214", Q_NULLPTR));
        pushButtonLogin->setText(QApplication::translate("LoginIn", "\347\231\273\345\275\225", Q_NULLPTR));
        menu->setTitle(QApplication::translate("LoginIn", "\350\217\234\345\215\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginIn: public Ui_LoginIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGININ_H
