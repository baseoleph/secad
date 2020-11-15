#include "enteringblocks.h"
#include "ui_enteringblocks.h"

EnteringBlocks::EnteringBlocks(QWidget *parent, SMainClass *m) :
    QWidget(parent),
    ui(new Ui::EnteringBlocks)
{
    ui->setupUi(this);
    this->m = m;

    ui->widget_block->setEnabled(false);
}

EnteringBlocks::~EnteringBlocks()
{
    delete ui;
}

void EnteringBlocks::on_lineEdit_titleblock_textChanged(const QString &arg1)
{
    block_data->titleblock = arg1.toStdString();
}

void EnteringBlocks::on_checkBox_habitability_toggled(bool checked)
{
    block_data->habitability = checked;
}

void EnteringBlocks::on_checkBox_wheelhouse_toggled(bool checked)
{
    block_data->wheelhause = checked;
}

void EnteringBlocks::on_checkBox_pap_toggled(bool checked)
{
    block_data->pap = checked;
}

void EnteringBlocks::on_checkBox_mainmast_toggled(bool checked)
{
    block_data->mainmast = checked;
}

void EnteringBlocks::on_checkBox_foremast_toggled(bool checked)
{
    block_data->foremast = checked;
}

void EnteringBlocks::on_checkBox_funnel_toggled(bool checked)
{
    block_data->funnel = checked;
}

void EnteringBlocks::on_pushButton_saveEnteringData_clicked()
{
    signalSaveEnteringBlocks();
}

void EnteringBlocks::on_pushButton_addBlock_clicked()
{
    ui->widget_block->setEnabled(true);

    m->addBlock();
    block_data = m->blocks[m->blocks.size()-1];
    QStringList list_of_block_titles;
    foreach (auto e, m->blocks)
    {
       list_of_block_titles.append(QString::fromStdString(e->titleblock));
    }
    QString new_title = "Новый блок";
    QStringList words_in_new_title = new_title.split(" ");

    while (list_of_block_titles.contains(new_title))
    {
       if (words_in_new_title.size() == 2)
       {
           words_in_new_title.append("1");
       }
       else
       {
            int cnt = words_in_new_title.back().toInt();
            cnt += 1;
            words_in_new_title.pop_back();
            words_in_new_title.push_back(QString::number(cnt));
       }
       new_title = words_in_new_title.join(" ");
    }
    block_data->titleblock = new_title.toStdString();
    ui->lineEdit_titleblock->setText(new_title);
    ui->comboBox_blocks->clear();
    foreach (auto e, m->blocks)
    {
        ui->comboBox_blocks->addItem(QString::fromStdString(e->titleblock));
    }
    ui->comboBox_blocks->setCurrentText(new_title);
}
