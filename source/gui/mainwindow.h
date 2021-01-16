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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QFile>
#include <QDir>

#include "enteringblocks.h"
#include "projectmanager.h"
#include "generaldata.h"
#include "resultswidget.h"

#include "../core/smainclass.h"
#include "jsonparserclass.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слот, который открывает General Data; пустой или из файла
    void slotOpenProject(QString proj_name = "");
    void slotSaveGeneralData();
    void slotSaveEnteringData();
    void statusBarSlot(const QString str);

private:
    // Передаем значения из .json в объект класса SGeneralData
    void fillGeneralData(QString proj_name);

    // Установка рабочей директории для сохранения файлов проекта
    void changeCurrentDir();

    void removeAll();
    void clearAll();

    Ui::MainWindow *ui;
    ProjectManager *proj_man;
    GeneralData *gen_data;
    EnteringBlocks *ent_blocks;
    ResultsWidget *res_widget;
    JsonParserClass jpc;

#ifdef QT_DEBUG
    QString dir_to_projects = "../projects";
#else
    QString dir_to_projects = "projects";
#endif

    SMainClass *m;
};

#endif // MAINWINDOW_H
