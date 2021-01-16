// Ship Exterior CAD
// Copyright (C) 2020 baseoleph@gmail.com,
//					  github.com/RoninHikami

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
    checkCombobox();
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

void ProjectManager::checkCombobox()
{
    if (ui->comboBox->currentText() == "")
    {
        ui->pushButton_go->setEnabled(false);
    }
    else
    {
        ui->pushButton_go->setEnabled(true);
    }
}

void ProjectManager::on_comboBox_currentTextChanged(const QString &arg1)
{
    project_name = arg1;
    checkCombobox();
}

void ProjectManager::on_pushButton_create_new_proj_clicked()
{
    signalOpenProject();
}

void ProjectManager::on_pushButton_go_clicked()
{
    signalOpenProject(project_name);
}
