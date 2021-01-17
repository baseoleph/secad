// Ship Exterior CAD
// Copyright (C) 2020 baseoleph@gmail.com,
//					  nepryaho@gmail.com

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    changeCurrentDir();

    clearAll();
}


MainWindow::~MainWindow()
{
    removeAll();
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

void MainWindow::removeAll()
{
    delete m;
    delete proj_man;
    delete gen_data;
    delete ent_blocks;
    delete res_widget;
}

void MainWindow::clearAll()
{
    m = new SMainClass();
    connect(m, &SMainClass::emitStatusBarSignal, this, &MainWindow::statusBarSlot);
    jpc = JsonParserClass(this, m);

    proj_man = new ProjectManager(this, m);
    gen_data = new GeneralData(this, m);
    ent_blocks = new EnteringBlocks(this, m);
    res_widget = new ResultsWidget(this, m);

    ui->tabWidget->addTab(proj_man, "Project Manager");
    ui->tabWidget->addTab(gen_data, "General Data");
    ui->tabWidget->addTab(ent_blocks, "Entering Data");
    ui->tabWidget->addTab(res_widget, "Results");

    connect(proj_man, &ProjectManager::signalOpenProject,
            this, &MainWindow::slotOpenProject);
    connect(gen_data, &GeneralData::signalSaveGeneralData,
            this, &MainWindow::slotSaveGeneralData);
    connect(ent_blocks, &EnteringBlocks::signalSaveEnteringBlocks,
            this, &MainWindow::slotSaveEnteringData);
}

void MainWindow::slotOpenProject(QString proj_name)
{
    removeAll();
    clearAll();

    if (proj_name != "")
    {
        fillGeneralData(proj_name);
        gen_data->fillForms();
        ent_blocks->setUpForms();
    }
    else
    {
        m->restoreSGeneralData();
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

void MainWindow::statusBarSlot(const QString str)
{
    ui->statusbar->showMessage(str);
}

void MainWindow::fillGeneralData(QString proj_name)
{
    jpc.loadData(proj_name);
}

