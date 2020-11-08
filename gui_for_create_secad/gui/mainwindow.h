#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "enteringblocks.h"
#include "form2.h"
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

private:
    Ui::MainWindow *ui;
    GeneralData *gen_data;
    EnteringBlocks *ent_blocks;

    SMainClass *m;
};

#endif // MAINWINDOW_H
