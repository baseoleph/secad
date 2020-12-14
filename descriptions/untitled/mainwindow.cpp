#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    K.clear();
    K.append(0);
    K.append(1);
    K.append(2);
    K.append(3);
    K.append(4);
    K.append(5);
    K.append(6);
    K.append(7);


    j = 4;
    min_j = 0;
    max_j = 10;
    i = 6;
    k = 3;

    for (M = 0; M < 1000; ++M)
    {
        std::uniform_real_distribution<> dist(-1, 1);
        Y = dist(*QRandomGenerator::global());
        qDebug() << "Y" << Y;
        contOpt();
        disOpt();

        if (crit())
        {
            qDebug() << M << j << k << K[k];
            j = j_c;
            k = k_c;
        }
    }

    qDebug() << j << k << K[k];

    this->close();
}

void MainWindow::contOpt()
{
   j_c = j + (max_j - min_j) * pow(Y, M);

   if (j_c > max_j)
   {
       j_c = max_j;
   }
   if (j_c < min_j)
   {
       j_c = min_j;
   }
}

void MainWindow::disOpt()
{
   k_c = k + K.size() * pow(Y, M);

   if (k_c > K.size()-1)
   {
       k_c = K.size() - 1;
   }

   if (k_c < 0)
   {
       k_c = 0;
   }
}

bool MainWindow::crit()
{
    return (i + j + K[k]) > (i + j_c + K[k_c]);
}

MainWindow::~MainWindow()
{
    delete ui;
}
