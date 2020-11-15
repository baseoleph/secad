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


void EnteringBlocks::on_comboBox_lrc_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->horizontalWidget_lrc_cons->show();
        ui->horizontalWidget_lrc_cont->hide();
        ui->horizontalWidget_lrc_desc->hide();
    }
    else if (index == 1)
    {
        ui->horizontalWidget_lrc_cons->hide();
        ui->horizontalWidget_lrc_cont->show();
        ui->horizontalWidget_lrc_desc->hide();
    }
    else
    {
        ui->horizontalWidget_lrc_cons->hide();
        ui->horizontalWidget_lrc_cont->hide();
        ui->horizontalWidget_lrc_desc->show();
   }
}
