#include "info_table.h"
#include "ui_info_table.h"

void Info_Table::set_doubleclick_table(QTableWidgetItem *item)
{
    if(item != nullptr  && info_stu.size()!=0)
    {
        ui->student_table->setCurrentItem(item);
        modify_table();
    }
}
void Info_Table::set_click_table(QTableWidgetItem *item)
{

    if(find_list.size() != 0)
    {
        for(int i = 0;i < find_list.size();i++)
        {
            find_list[i]->setBackgroundColor(QColor(255,248,220));
        }
        find_list.clear();
    }
    if(get_find != nullptr)
    {
        get_find->close();
        get_find=nullptr;
    }
}

void Info_Table::new_table()     // new a file  新建一个表格
{
    for(int i = 0;i < info_stu.size();i++)
    {
        info_stu.pop_back();                  // 清空之前的vector数据
    }
    show_table();
}

void Info_Table::save_table()    // save a file
{
    if(!info_stu.empty())
    {
        QFileDialog filelog;
        QString str = filelog.getSaveFileName(this,tr("保存文件"),"student.txt",tr("File(*.txt"));
        if(str == "")
        {
            QMessageBox::warning(this,tr("Warning"),tr("文件夹为空！"));
        }
        else
        {
            ofstream outfile(str.toStdString(),ios::out);
            for(int i=  0;i < info_stu.size()-1;i++)
            {
                outfile<<info_stu[i]->s_id<<" "<<info_stu[i]->s_name<<" "<<info_stu[i]->s_sex<<
                         " "<<info_stu[i]->s_age<<" "<<info_stu[i]->s_dept<<" "<<info_stu[i]->s_address<<endl;
            }
            int i = info_stu.size()-1;
            outfile<<info_stu[i]->s_id<<" "<<info_stu[i]->s_name<<" "<<info_stu[i]->s_sex<<
                     " "<<info_stu[i]->s_age<<" "<<info_stu[i]->s_dept<<" "<<info_stu[i]->s_address;

        }
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("txt文件为空！"));
    }
}

void Info_Table::open_table()    // open a file
{
    new_table();  // 打开新文件需要初始化
    QFileDialog filelog;
    QString str = filelog.getOpenFileName(this,tr("打开文件"),"",tr("File(*.txt)"));
    if(str=="")
    {
        QMessageBox::warning(this,tr("Warning"),tr("文件夹为空！"));
    }
    else
    {
        ifstream infile(str.toStdString(),ios::in);
        while(!infile.eof())
        {
            current_stu = new student();
            infile >>current_stu->s_id>>current_stu->s_name>>current_stu->s_sex>>current_stu->s_age
                    >>current_stu->s_dept>>current_stu->s_address;
            info_stu.push_back(current_stu);
        }
        update_table();
    }
}

void Info_Table::add_table()    // add information  打开Manager 类的窗口
{
    if(ui->student_table!=nullptr)
    {
        manager = new Manager();
        manager->setWindowTitle("增加学生信息");
        manager->add_flag = true;
        manager->show();
        connect(manager,SIGNAL(add_info_emit(student *)),this,SLOT(receive_add_emit(student *)));
    }
}
void Info_Table::receive_add_emit(student *stu)
{
    for(int i = 0;i < info_stu.size();i++)
    {
        if(info_stu[i]->s_id == stu->s_id)
        {
            QMessageBox::warning(this,"Warning","该同学已经存在!");
            return;
        }
    }

    info_stu.push_back(stu);
    current_stu = stu;                   //设置current_stu;
    update_table();
}

void Info_Table::receive_modify_finish()
{
    for(int i= 0;i < info_stu.size();i++)
    {
        if(current_stu != info_stu[i] && current_stu->s_id == info_stu[i]->s_id)
        {
            QMessageBox::warning(this,"Warning","该同学已经存在!");
            *current_stu = sample;
            return ;
        }
    }
    update_table();
}
void Info_Table::modify_table()   // modify information
{
    if(get_current_stu() != nullptr)
    {
        sample = *current_stu;
        manager = new Manager();
        manager->stu_once = current_stu;
        manager->modify_flag = true;
        manager->setWindowTitle("修改学生信息");
        manager->show();
        connect(this,SIGNAL(emit_modify_start()),manager,SLOT(receive_modify_start()));
        connect(manager,SIGNAL(emit_modify_finish()),this,SLOT(receive_modify_finish()));
        emit_modify_start();
    }
}

void Info_Table::delete_table()   // delete information
{
    item_list = ui->student_table->selectedItems();
    if(item_list.size()==0)   // 当前未选中
    {
        QMessageBox::warning(this,"warning","请选择对应行!");
    }
    else // 当前选中
    {
        for(int i = 0;i < item_list.size()/ui->student_table->columnCount();i++)
        {
            int row = ui->student_table->row(item_list[0]);
            vector<student*>::iterator it = info_stu.begin();
            for(int k=  0;k < row;k++,it++);
            info_stu.erase(it);
        }
        item_list.clear();   // item_list 清零
        show_table();                         // 删除操作需要重新创建table
        update_table();
    }
}

bool camp_id(student *first,student *second)
{
    if(first->s_id < second->s_id)
    {
        return true;
    }
    return false;
}
void Info_Table::sort_by_id()       // sort by id
{
    sort(info_stu.begin(),info_stu.end(),camp_id);
    update_table();
}

bool camp_date(student *first,student *second)
{
    QDate a = QDate::fromString(QString::fromStdString(first->s_age),"yyyy/M/d");
    QDate b = QDate::fromString(QString::fromStdString(second->s_age),"yyyy/M/d");
    if(a.year() < b.year())  return true;
    else if(a.year() > b.year())  return false;
    else
    {
        if(a.month() > b.month()) return false;
        else if(a.month() < b.month()) return true;
        else
        {
            if(a.day() > b.day())  return false;
            else if(a.day() < b.day()) return true;
            else // 日期相等
            {
                if(first->s_id > second->s_id) return false;
                else return true;
            }
        }
    }

}
void Info_Table::sort_by_date()     // sort by name
{
    sort(info_stu.begin(),info_stu.end(),camp_date);
    update_table();
}

bool camp_name(student *first,student *second)
{
    QString a = QString::fromStdString(first->s_name);
    QString b = QString::fromStdString(second->s_name);
    return (a.localeAwareCompare(b)<0);
}

void Info_Table::sort_by_name()
{
    sort(info_stu.begin(),info_stu.end(),camp_name);
    update_table();
}
