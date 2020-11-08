#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m = new SMainClass();

    gen_data = new GeneralData(this, m);
    ent_blocks = new EnteringBlocks(this, m);

    ui->tabWidget->addTab(gen_data, "General Data");
    ui->tabWidget->addTab(ent_blocks, "Entering Data");
    ui->tabWidget->addTab(new Form2(this), "Form 2");
    ui->tabWidget->addTab(new RenamedForm(this), "Form 4");
}

MainWindow::~MainWindow()
{
    delete m;
    delete gen_data;
    delete ent_blocks;
    delete ui;
}

