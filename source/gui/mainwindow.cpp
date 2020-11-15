#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    changeCurrentDir();

    m = new SMainClass();
    jpc = JsonParserClass(this, m);

    proj_man = new ProjectManager(this, m);
    gen_data = new GeneralData(this, m);
    ent_blocks = new EnteringBlocks(this, m);

    ui->tabWidget->addTab(proj_man, "Project Manager");
    ui->tabWidget->addTab(gen_data, "General Data");
    ui->tabWidget->addTab(ent_blocks, "Entering Data");
    ui->tabWidget->addTab(new RenamedForm(this), "Form 4");

    connect(proj_man, &ProjectManager::signalOpenProject,
            this, &MainWindow::slotOpenProject);
    connect(gen_data, &GeneralData::signalSaveGeneralData,
            this, &MainWindow::slotSaveGeneralData);
    connect(ent_blocks, &EnteringBlocks::signalSaveEnteringBlocks,
            this, &MainWindow::slotSaveEnteringData);
}


MainWindow::~MainWindow()
{
    delete m;
    delete proj_man;
    delete gen_data;
    delete ent_blocks;
    delete ui;
}

void MainWindow::changeCurrentDir()
{
    if (not QDir(dir_to_projects).exists())
    {
        QDir().mkdir(dir_to_projects);
    }
    QDir::setCurrent(QDir::currentPath() + "/" + dir_to_projects);
}

void MainWindow::slotOpenProject(QString proj_name)
{
    if (proj_name != "")
    {
        fillGeneralData(proj_name);
        gen_data->fillForms();
    }
    else
    {
        m->restoreSGeneralData();
        gen_data->unFillForms();
    }
    ui->tabWidget->setCurrentWidget(gen_data);
}

void MainWindow::slotSaveGeneralData()
{
    jpc.saveData();
}

void MainWindow::slotSaveEnteringData()
{
    jpc.saveData();
}

void MainWindow::fillGeneralData(QString proj_name)
{
    jpc.loadData(proj_name);
}

