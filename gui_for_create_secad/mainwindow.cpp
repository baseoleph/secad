#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->addTab(new Form1(this), "Form 1");
    ui->tabWidget->addTab(new Form2(this), "Form 2");
    ui->tabWidget->addTab(new Form3(this), "Form 3");
    ui->tabWidget->addTab(new Form4(this), "Form 6");
    ui->tabWidget->addTab(new Form5(this), "Form 5");
}

MainWindow::~MainWindow()
{
    delete ui;
}

