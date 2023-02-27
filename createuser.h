#ifndef CREATEUSER_H
#define CREATEUSER_H

#include <QMainWindow>

namespace Ui {
class CreateUser;
}

class CreateUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateUser(QWidget *parent = 0);
    ~CreateUser();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateUser *ui;
};

#endif // CREATEUSER_H
