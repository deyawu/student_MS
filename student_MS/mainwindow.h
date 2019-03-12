#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QTableWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QMouseEvent>
#include <QFont>
#include <algorithm>
#include <QMdiArea>
#include <QInputDialog>
#include <QDebug>
#include <vector>
#include <fstream>
#include "info_table.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_current_table();
    void closeEvent(QCloseEvent *event);

private slots:

    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionAdd_triggered();
    void on_actionModify_triggered();
    void on_actionDelete_triggered();
    void on_actionID_triggered();
    void on_actionName_triggered();
    void on_actionclose_triggered();
    void on_actionDate_triggered();
    void on_action_triggered();


private:
    Ui::MainWindow *ui;
    int label;
    Info_Table *current_table;
};





#endif // MAINWINDOW_H
