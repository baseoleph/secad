#include "enteringblocks.h"
#include "ui_enteringblocks.h"

EnteringBlocks::EnteringBlocks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnteringBlocks)
{
    ui->setupUi(this);

    ui->pushButton_8->setEnabled(false);
}

EnteringBlocks::~EnteringBlocks()
{
    delete ui;
}
