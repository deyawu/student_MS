#include "info_table.h"
#include "ui_info_table.h"

Info_Table::Info_Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info_Table)
{
    ui->setupUi(this);
    this->setGeometry(100,100,900,800);
    this->setFixedSize(900,800);
    this->setWindowTitle("Student-Manager-System");
    current_stu=nullptr;
    get_find=nullptr;
    ui->student_table->setGeometry(0,0,this->width(),this->height());
    ui->student_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->student_table,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(set_doubleclick_table(QTableWidgetItem *)));
    connect(ui->student_table,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(set_click_table(QTableWidgetItem *)));

    ui->student_table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->student_table,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(click_menu(QPoint)));

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
}

Info_Table::~Info_Table()
{
    delete ui;
}

student *Info_Table::get_current_stu()
{
    int current_row = ui->student_table->currentRow();
    if(current_row < info_stu.size())
    {
        current_stu= info_stu[current_row];
        return current_stu;

    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),"选中区域为空！");
        return nullptr;
    }
}
void Info_Table::update_table()   // 更新表格,每步操作后都需要被调用
{
    QString value;
    ui->student_table->setRowCount(info_stu.size());
    for(int i = 0;i < info_stu.size();i++)
    {
        value = QString::fromStdString(info_stu[i]->s_id);
        ui->student_table->setItem(i,0,new QTableWidgetItem(value));

        value = QString::fromStdString(info_stu[i]->s_name);
        ui->student_table->setItem(i,1,new QTableWidgetItem(value));

        value = QString::fromStdString(info_stu[i]->s_sex);
        ui->student_table->setItem(i,2,new QTableWidgetItem(value));

        value = QString::fromStdString(info_stu[i]->s_age);
        ui->student_table->setItem(i,3,new QTableWidgetItem(value));

        value = QString::fromStdString(info_stu[i]->s_dept);
        ui->student_table->setItem(i,4,new QTableWidgetItem(value));

        value = QString::fromStdString(info_stu[i]->s_address);
        ui->student_table->setItem(i,5,new QTableWidgetItem(value));
        for(int k=  0;k < ui->student_table->columnCount();k++)
        {
            ui->student_table->item(i,k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->student_table->item(i,k)->setBackgroundColor(QColor(255,248,220));
        }
    }
}
void Info_Table::show_table()    // 表头设计
{
    ui->student_table->resize(this->width(),this->height());
    QStringList headlist;
    headlist.push_back(QString("学号"));
    headlist.push_back(QString("姓名"));
    headlist.push_back(QString("性别"));
    headlist.push_back(QString("出生年月"));
    headlist.push_back(QString("专业"));
    headlist.push_back(QString("籍贯"));
    int col_num = headlist.count();
    ui->student_table->setRowCount(0); // 设置行数
    ui->student_table->setColumnCount(col_num); // 设置列数
    ui->student_table->setHorizontalHeaderLabels(headlist);

    for(int i=  0;i < ui->student_table->columnCount();i++)
    {
        ui->student_table->horizontalHeaderItem(i)->setTextColor(QColor(200,111,30));
    }

    ui->student_table->setEditTriggers(QAbstractItemView::NoEditTriggers); // 阻止修改
    ui->student_table->setSelectionBehavior(QAbstractItemView::SelectRows);// 选取整行

    ui->student_table->setShowGrid(true); // 显示网格线
}

void Info_Table::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this,"warning","是否保存？",QMessageBox::Yes|QMessageBox::No);
    if(button == QMessageBox::No)
    {
        event->accept();
    }
    else
    {
        save_table();
    }
}
void Info_Table::emit_find_table()
{
    if(get_find==nullptr && info_stu.size() != 0)
    {
        get_find = new QLineEdit(this);
        get_find->setPlaceholderText("……");
        get_find->setEchoMode(QLineEdit::Normal);
        get_find->setGeometry(200,0,150,40);
        connect(get_find,SIGNAL(returnPressed()),this,SLOT(get_find_table()));
        get_find->show();
    }
}
void Info_Table::get_find_table()
{
    if(find_list.size() != 0)
    {
        for(int i = 0;i < find_list.size();i++)
        {
            find_list[i]->setBackgroundColor(QColor(255,248,220));
        }
        find_list.clear();
    }                                               // add a delete operation

    ui->student_table->clearSelection(); // 清除当前所选行
    QString text = get_find->text();
    if(!text.isEmpty())
    {
        find_list = ui->student_table->findItems(text,Qt::MatchContains);
        for(int i = 0;i < find_list.size();i++)
        {
            find_list[i]->setBackgroundColor(QColor(154,255,154));
        }
    }
    get_find->close();
    get_find=nullptr;
}
void Info_Table::click_menu(QPoint pos)
{
    QMenu *menu = new QMenu(ui->student_table);
    QAction *m_delete  = new QAction("删除",ui->student_table);
    QAction *m_find = new QAction("查找",ui->student_table);
    connect(m_delete,SIGNAL(triggered()),this,SLOT(emit_delete_table()));
    connect(m_find,SIGNAL(triggered()),this,SLOT(emit_find_table()));
    menu->addAction(m_delete);
    menu->addAction(m_find);
    menu->move(cursor().pos().x()+10,cursor().pos().y()+10);
    menu->show();
}
