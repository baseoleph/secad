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

    QString dir_to_projects = "../projects";

    SMainClass *m;
};

#endif // MAINWINDOW_H
