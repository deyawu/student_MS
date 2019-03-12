#ifndef MANAGER_H
#define MANAGER_H

#pragma once
#include <QWidget>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <string.h>
#include <QString>
#include <QDate>
#include <QDebug>
#include<QPalette>
#include <QMessageBox>
using namespace std;
struct student
{
    string s_id;
    string s_name;
    string s_date;
    string s_age;
    string s_dept;
    string s_address;
    string s_sex;
};

namespace Ui {
class Manager;
}

class Manager : public QWidget
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = nullptr); // 避免隐式类型转换
    ~Manager();
private slots:
    void on_add_btn_clicked();

    void on_cancle_btn_clicked();

    void receive_modify_start();

    void get_value();

 signals:
    void add_info_emit(student *stu);
    void emit_modify_finish();
    void cancle_info_emit(student *stu);
public:
    Ui::Manager *ui;
    student *stu_once;
    bool add_flag,modify_flag;
};





#endif // MANAGER_H










