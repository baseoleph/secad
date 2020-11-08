#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->addTab(new GeneralData(this), "General Data");
    ui->tabWidget->addTab(new EnteringBlocks(this), "Entering Blocks");
    ui->tabWidget->addTab(new Form2(this), "Form 2");
    ui->tabWidget->addTab(new RenamedForm(this), "Form 4");


}

MainWindow::~MainWindow()
{
    delete ui;
}

