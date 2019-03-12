#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(100,100,900,800);
    this->setFixedSize(900,900);
    this->setWindowTitle("学生信息管理");
    QBrush b=QBrush(QColor(255,248,128),Qt::FDiagPattern);
    ui->mdiArea->setBackground(b);
    ui->mdiArea->setTabPosition(QTabWidget::North);
    ui->mdiArea->setTabShape(QTabWidget::Triangular);
    ui->mdiArea->setTabsMovable(true);
    ui->mdiArea->setViewMode(QMdiArea::TabbedView);
    ui->mdiArea->setTabsClosable(false);
    this->setCentralWidget(ui->mdiArea);
    current_table = nullptr;
    label = 0;


}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_current_table()
{
    QMdiSubWindow *cur = ui->mdiArea->currentSubWindow();
    if(cur != nullptr)
    {
        current_table = (Info_Table *)cur->widget();
    }
    else
    {
        current_table = nullptr;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!ui->mdiArea->subWindowList().empty())
    {
        QMessageBox::StandardButton button;
        button=QMessageBox::question(this,"Warning","这不会保存你的文件，是否关闭？",QMessageBox::Yes|QMessageBox::No);
        if(button == QMessageBox::Yes)
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        this->close();
    }
}

void MainWindow::on_actionNew_triggered()     // new a file  新建一个表格
{
    current_table = new Info_Table();
    QMdiSubWindow *w_add = ui->mdiArea->addSubWindow(current_table);
    QString title = "Tab "+QString::number(label,10);
    current_table->setWindowTitle(title);
    w_add->show();
    w_add->resize(ui->mdiArea->width(),ui->mdiArea->height());
    current_table->new_table();
    label ++;                                // 标记窗口id
}

void MainWindow::on_actionSave_triggered()    // save a file
{
    if(!ui->mdiArea->subWindowList().empty())
    {
        set_current_table();
        current_table->save_table();
    }
}

void MainWindow::on_actionOpen_triggered()    // open a file
{
    on_actionNew_triggered();   // current 指向当前窗口
    current_table->open_table();
}

void MainWindow::on_actionclose_triggered()  // close file save!!
{
    if(!ui->mdiArea->subWindowList().empty())
    {
        set_current_table();
        ui->mdiArea->closeActiveSubWindow();
    }
}


void MainWindow::on_actionAdd_triggered()    // add information  打开Manager 类的窗口
{
    if(ui->mdiArea->subWindowList().empty())
    {
        on_actionNew_triggered(); // 创建新窗口
    }
    set_current_table();
    current_table->add_table();
}

void MainWindow::on_actionModify_triggered()   // modify information
{
    if(!ui->mdiArea->subWindowList().empty())
    {
        set_current_table();
        current_table->modify_table();
    }
}

void MainWindow::on_actionDelete_triggered()   // delete information
{
    if(!ui->mdiArea->subWindowList().empty())
    {
        set_current_table();
        current_table->delete_table();
    }
}


void MainWindow::on_actionID_triggered()       // sort by id
{
    if(!ui->mdiArea->subWindowList().empty())
    {
        set_current_table();
        current_table->sort_by_id();
    }
}


void MainWindow::on_actionName_triggered()     // sort by name
{
    if(!ui->mdiArea->subWindowList().empty())
    {
        set_current_table();
        current_table->sort_by_name();
    }
}

void MainWindow::on_actionDate_triggered()  // sort by date
{
    if(!ui->mdiArea->subWindowList().empty())
    {
        set_current_table();
        current_table->sort_by_date();
    }
}

void MainWindow::on_action_triggered()
{
    if(!ui->mdiArea->subWindowList().empty())
    {
        set_current_table();
        current_table->find_table();
    }
}
