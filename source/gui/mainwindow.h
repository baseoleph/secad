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
#include "renamedform.h"

#include "../core/smainclass.h"

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
    void slotOpenProject(QString proj_name = "");

private:
    void fillGeneralData(QString proj_name);

    Ui::MainWindow *ui;
    ProjectManager *proj_man;
    GeneralData *gen_data;
    EnteringBlocks *ent_blocks;

    SMainClass *m;
};

#endif // MAINWINDOW_H
