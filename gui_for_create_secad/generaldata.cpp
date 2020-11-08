#include "generaldata.h"
#include "ui_generaldata.h"

GeneralData::GeneralData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralData)
{
    ui->setupUi(this);
}

GeneralData::~GeneralData()
{
    delete ui;
}
