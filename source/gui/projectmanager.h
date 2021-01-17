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

#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QWidget>
#include <QDir>
#include <QDebug>

#include "../core/smainclass.h"

namespace Ui {
class ProjectManager;
}

class ProjectManager : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectManager(QWidget *parent = nullptr, SMainClass *m = nullptr);
    ~ProjectManager();

signals:
    // Отправляет сигнал на открытие проекта из файла или нового
    void signalOpenProject(QString proj_name = "");

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_go_clicked();
    void on_pushButton_create_new_proj_clicked();

private:
    Ui::ProjectManager *ui;
    SGeneralData *general;

    QString project_name;

    // Проверяет наличие готовых проектов *.json
    void checkJsonsInDir();

    // Проверят пустоту combobox
    void checkCombobox();
};

#endif // PROJECTMANAGER_H
