#include "gofuckyourself.h"
#include "ui_gofuckyourself.h"

GoFuckYourself::GoFuckYourself(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoFuckYourself)
{
    ui->setupUi(this);
}

GoFuckYourself::~GoFuckYourself()
{
    delete ui;
}
