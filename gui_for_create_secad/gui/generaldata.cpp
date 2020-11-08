#include "generaldata.h"
#include "ui_generaldata.h"

GeneralData::GeneralData(QWidget *parent, SMainClass *m) :
    QWidget(parent),
    ui(new Ui::GeneralData)
{
    ui->setupUi(this);
    Q_UNUSED(m)
}

GeneralData::~GeneralData()
{
    delete ui;
}
