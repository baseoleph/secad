#include "form1.h"
#include "ui_form1.h"

Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1)
{
    ui->setupUi(this);

    ui->pushButton_8->setEnabled(false);
}

Form1::~Form1()
{
    delete ui;
}
