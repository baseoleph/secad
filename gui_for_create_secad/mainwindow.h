#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "form1.h"
#include "form2.h"
#include "form3.h"
<<<<<<< Updated upstream
#include "form4.h"
=======
#include "gofuckyourself.h"
>>>>>>> Stashed changes

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
};
#endif // MAINWINDOW_H
