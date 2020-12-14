#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void contOpt();
    void disOpt();
    bool crit();

private:
    Ui::MainWindow *ui;


    double M;
    double Y;
    double i;
    double k;
    double k_c;
    double j;
    double j_c;
    double min_j;
    double max_j;
    QVector<int> K;
    double S;
};
#endif // MAINWINDOW_H
