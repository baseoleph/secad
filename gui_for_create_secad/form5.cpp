#include "form5.h"
#include "ui_gofuckyourself.h"

Form5::Form5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoFuckYourself)
{
    ui->setupUi(this);
}

Form5::~Form5()
{
    delete ui;
}
