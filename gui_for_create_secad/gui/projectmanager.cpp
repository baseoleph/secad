#include "projectmanager.h"
#include "ui_projectmanager.h"

ProjectManager::ProjectManager(QWidget *parent, SMainClass *m) :
    QWidget(parent),
    ui(new Ui::ProjectManager)
{
    ui->setupUi(this);
    general = m->general;

    checkJsonsInDir();
    project_name = ui->comboBox->currentText();
    if (ui->comboBox->currentText() == "")
    {
        ui->pushButton_go->setEnabled(false);
    }
    else
    {
        ui->pushButton_go->setEnabled(true);
    }
}

ProjectManager::~ProjectManager()
{
    delete ui;
}


void ProjectManager::checkJsonsInDir()
{
    QDir dir;
    QStringList jsons = dir.entryList(QStringList("*.json"));
    ui->comboBox->clear();
    foreach (QString file, jsons)
    {
        ui->comboBox->addItem(file.remove(".json"));
    }
}

void ProjectManager::on_comboBox_currentTextChanged(const QString &arg1)
{
    project_name = arg1;
    if (ui->comboBox->currentText() == "")
    {
        ui->pushButton_go->setEnabled(false);
    }
    else
    {
        ui->pushButton_go->setEnabled(true);
    }
}

void ProjectManager::on_pushButton_create_new_proj_clicked()
{
    signalOpenProject();
}

void ProjectManager::on_pushButton_go_clicked()
{
    signalOpenProject(project_name);
}
