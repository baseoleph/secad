#include "form4.h"
#include "ui_form4.h"

Form4::Form4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form4)
{
    ui->setupUi(this);
}

Form4::~Form4()
{
    delete ui;
}
