#include "enteringblocks.h"
#include "ui_enteringblocks.h"

EnteringBlocks::EnteringBlocks(QWidget *parent, SMainClass *m) :
    QWidget(parent),
    ui(new Ui::EnteringBlocks)
{
    ui->setupUi(this);
    m->addBlock();
    qDebug() << "size" << m->blocks.size();
    m->blocks[m->blocks.size()-1]->optimize_vect[0]->setType(2);
    qDebug() << m->blocks[m->blocks.size()-1]->optimize_vect[0]->type;
}

EnteringBlocks::~EnteringBlocks()
{
    delete ui;
}

void EnteringBlocks::on_comboBox_currentIndexChanged(int index)
{
    m->blocks[m->blocks.size()-1]->optimize_vect[0]->setType(index);
}
