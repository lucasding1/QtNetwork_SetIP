#include "mainwindow.h"
#include "ui_mainwindow.h"

//构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

