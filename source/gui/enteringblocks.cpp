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

void EnteringBlocks::fillForms()
{
    QString current_block_title = ui->comboBox_blocks->currentText();
    if (current_block_title != "")
    {
        foreach (auto e, m->blocks)
        {
            if (QString::fromStdString(e->titleblock) == current_block_title)
            {
                block_data = e;
                break;
            }
        }
    }

    ui->lineEdit_titleblock->setText(current_block_title);
    ui->lineEdit_l_hb_l->setText(QString::number(block_data->l_hb_l));
    ui->checkBox_foremast->setChecked(block_data->foremast);
    ui->checkBox_funnel->setChecked(block_data->funnel);
    ui->checkBox_habitability->setChecked(block_data->habitability);
    ui->checkBox_pap->setChecked(block_data->pap);
    ui->checkBox_mainmast->setChecked(block_data->mainmast);
    ui->checkBox_wheelhouse->setChecked(block_data->wheelhause);
}

void EnteringBlocks::on_lineEdit_titleblock_textChanged(const QString &arg1)
{
    block_data->titleblock = arg1.toStdString();
    updateComboBlocks(arg1);
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
    QString new_title = generateNewTemplateTitle();
    block_data->titleblock = new_title.toStdString();
    updateComboBlocks(new_title);
}

void EnteringBlocks::on_comboBox_blocks_textActivated(const QString &arg1)
{
    Q_UNUSED(arg1)
    fillForms();
}

QString EnteringBlocks::generateNewTemplateTitle()
{
    QString new_title = TEMPLATE_TITLE;
    QStringList list_of_block_titles;
    foreach (auto e, m->blocks)
    {
       list_of_block_titles.append(QString::fromStdString(e->titleblock));
    }
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

    return new_title;
}

void EnteringBlocks::updateComboBlocks(QString current_item)
{
    ui->comboBox_blocks->clear();
    foreach (auto e, m->blocks)
    {
        ui->comboBox_blocks->addItem(QString::fromStdString(e->titleblock));
    }
    ui->comboBox_blocks->setCurrentText(current_item);
    ui->comboBox_blocks->textActivated(current_item);


}
