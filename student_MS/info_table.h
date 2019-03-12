#ifndef INFO_TABLE_H
#define INFO_TABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QMouseEvent>
#include <QFont>
#include <algorithm>
#include <QMdiArea>
#include <QDebug>
#include <fstream>
#include <QtAlgorithms>
#include <QMenu>
#include <QAction>
#include "manager.h"

namespace Ui {
class Info_Table;
}

class Info_Table : public QWidget
{
    Q_OBJECT

public:
    explicit Info_Table(QWidget *parent = nullptr);
    ~Info_Table();
    void closeEvent(QCloseEvent *event);
    student *get_current_stu();
    void show_table();
    void update_table();  // use vector info_stu to update
    void new_table();
    void save_table();
    void open_table();
    void add_table();
    void modify_table();
    void delete_table();
    void sort_by_id();
    void sort_by_date();
    void sort_by_name();
    void find_table(){emit_find_table();}   // 给出调用查找的接口

private slots:

    void emit_delete_table(){delete_table();}
    void emit_find_table();
    void get_find_table();        // 文本框enter时触发
    void receive_add_emit(student *stu);
    void receive_modify_finish();
    void set_doubleclick_table(QTableWidgetItem *item);   // 双击修改
    void set_click_table(QTableWidgetItem *item);
    void click_menu(QPoint pos);// 添加菜单栏

signals:
     void emit_modify_start();


private:
    Manager *manager;
    vector<student *>info_stu;
    student *current_stu;
    student sample;
    QList<QTableWidgetItem *> item_list,find_list;
    QLineEdit *get_find;         // 文本框

private:
    Ui::Info_Table *ui;
};

bool camp_id(student *first,student *second);
bool camp_date(student *first,student *second);
bool camp_name(student *first,student *second);



#endif // INFO_TABLE_H
