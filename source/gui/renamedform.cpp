#include "renamedform.h"
#include "ui_renamedform.h"

RenamedForm::RenamedForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenamedForm)
{
    ui->setupUi(this);
}

RenamedForm::~RenamedForm()
{
    delete ui;
}
