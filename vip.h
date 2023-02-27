#ifndef VIP_H
#define VIP_H

#include<QString>

class Temp_Customer_Consume;
class Add_Vip;
class StartPage;
class Show_Temp_customer_Consume_Sum;
class Modify_Vip;
class Consume_Vip;
class Charged_Vip_Record;
class Consume_Vip_Record;
class Vip
{
    friend Temp_Customer_Consume;
    friend Add_Vip;
    friend StartPage;
    friend Show_Temp_customer_Consume_Sum;
    friend Modify_Vip;
    friend Consume_Vip;
    friend Charged_Vip_Record;
    friend Consume_Vip_Record;
public:
    Vip();
    ~Vip();

private:
    QString Vip_name;
    QString Vip_phone;

    QString Vip_type_flag;

    float Vip_remain_money;
    int Vip_ramain_Num;
    int Vip_discount;

    int Vip_consume_Num;
    float Vip_consume_money;

    int Year;
    int Month,Day;

};

#endif // VIP_H
