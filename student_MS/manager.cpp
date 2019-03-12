#include "manager.h"
#include "ui_manager.h"

Manager::Manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manager)
{

    ui->setupUi(this);
    int height = 500,width=500;
    this->setGeometry(300,300,height,width);
    this->setFixedSize(QSize(height,width));
    QPalette p(palette());
    p.setBrush(QPalette::Window,QBrush(QColor(255,245,230)));
    this->setPalette(p);

    stu_once = new student();
    add_flag = false;
    modify_flag = false;

}

Manager::~Manager()
{
    delete ui;
}
void Manager::receive_modify_start()
{
    ui->line_sno->setText(QString::fromStdString(stu_once->s_id));
    ui->line_sname->setText(QString::fromStdString(stu_once->s_name));
    ui->comboBox_sex->setCurrentText(QString::fromStdString(stu_once->s_sex));
    ui->birth_day->setDate(QDate::fromString(QString::fromStdString(stu_once->s_age),"yyyy/M/d"));
    ui->line_sdepart->setText(QString::fromStdString(stu_once->s_dept));
    ui->line_saddr->setText(QString::fromStdString(stu_once->s_address));
}
void Manager::get_value()
{
    QString sno = ui->line_sno->text();
    QString sname = ui->line_sname->text();
    QString sex = ui->comboBox_sex->currentText();
    QString sage = ui->birth_day->text();
    QString sdepart = ui->line_sdepart->text();
    QString saddr = ui->line_saddr->text();

    stu_once->s_id = sno.toStdString();
    stu_once->s_name = sname.toStdString();
    stu_once->s_sex =sex.toStdString();
    stu_once->s_age = sage.toStdString();
    stu_once->s_dept = sdepart.toStdString();
    stu_once->s_address = saddr.toStdString();
}
void Manager::on_add_btn_clicked()   // add an item  并判断是否为空
{
    get_value();
    if(stu_once->s_id=="" || stu_once->s_name=="" || stu_once->s_dept=="" || stu_once->s_address=="")
    {
        QMessageBox::warning(this,tr("Warning"),tr("部分表单为空!"));
    }
    else if(add_flag)
    {
        this->close();
        emit add_info_emit(stu_once);    // 传参
    }
    else if(modify_flag && stu_once != nullptr)
    {
        this->close();
        emit_modify_finish();
    }
}

void Manager::on_cancle_btn_clicked()   // empty the item
{
    this->close();
}



