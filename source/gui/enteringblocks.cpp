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

        ui->lineEdit_titleblock->setText(current_block_title);

        if (block_data->l_hb_l != NOTHING_VALUE) ui->lineEdit_l_hb_l->setText(QString::number(block_data->l_hb_l));
        else ui->lineEdit_l_hb_l->setText("");

        ui->checkBox_foremast->setChecked(block_data->foremast);
        ui->checkBox_funnel->setChecked(block_data->funnel);
        ui->checkBox_habitability->setChecked(block_data->habitability);
        ui->checkBox_pap->setChecked(block_data->pap);
        ui->checkBox_mainmast->setChecked(block_data->mainmast);
        ui->checkBox_wheelhouse->setChecked(block_data->wheelhause);

        ui->lineEdit_lrc_cons->setText(QString::number(block_data->lrc.cons));
        ui->lineEdit_lrc_cont_max->setText(QString::number(block_data->lrc.cont_max));
        ui->lineEdit_lrc_cont_min->setText(QString::number(block_data->lrc.cont_min));

        updateWidgetsDCC();
        updateLrcCombo();
        updateWidgetsDCC();
    }
}

void EnteringBlocks::setUpForms()
{
    if (m->blocks.size() != 0)
    {
        ui->widget_block->setEnabled(true);
        block_data = m->blocks[0];
        updateComboBlocks(QString::fromStdString(block_data->titleblock));
        updateWidgetsDCC();
    }
}

void EnteringBlocks::on_lineEdit_titleblock_textChanged(const QString &arg1)
{
    foreach (auto e, m->blocks)
    {
        if (e->hb_h == block_data->titleblock)
        {
           e->hb_h = arg1.toStdString();
        }
        if (e->hb_l == block_data->titleblock)
        {
           e->hb_l = arg1.toStdString();
        }
    }

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
    block_data->hb_h = "";
    block_data->hb_l = "";
    updateComboBlocks(new_title);
    updateWidgetsDCC();
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

    updateComboHBBlocks();

    ui->comboBox_blocks->setCurrentText(current_item);
    ui->comboBox_blocks->textActivated(current_item);
}

void EnteringBlocks::updateComboHBBlocks()
{
    ui->comboBox_hb_h->clear();
    ui->comboBox_hb_l->clear();
    ui->comboBox_hb_h->addItem("");
    ui->comboBox_hb_l->addItem("");

    foreach (auto e, m->blocks)
    {
        if (e->titleblock != block_data->titleblock)
        {
            ui->comboBox_hb_h->addItem(QString::fromStdString(e->titleblock));
            if (e->titleblock != block_data->hb_h)
            {
                ui->comboBox_hb_l->addItem(QString::fromStdString(e->titleblock));
            }
        }
    }

    ui->comboBox_hb_h->setCurrentText(QString::fromStdString(block_data->hb_h));
    ui->comboBox_hb_l->setCurrentText(QString::fromStdString(block_data->hb_l));
}

void EnteringBlocks::updateLrcCombo()
{
    if (block_data->lrc.is_golden_section)
    {
        block_data->lrc.desc_link = &m->general->gsl;
    }
    else
    {
        block_data->lrc.desc_link = &block_data->lrc.desc_not_gs;
    }
    ui->comboBox_lrc_disc_var->clear();
    foreach (auto e, *block_data->lrc.desc_link)
    {
        ui->comboBox_lrc_disc_var->addItem(QString::number(e));
    }
}

void EnteringBlocks::updateWidgetsDCC()
{
    ui->comboBox_lrc->setCurrentIndex(block_data->lrc.type);
    ui->comboBox_lrc->activated(block_data->lrc.type);
}

void EnteringBlocks::on_comboBox_hb_h_textActivated(const QString &arg1)
{
    block_data->hb_h = arg1.toStdString();
    if (block_data->hb_h == block_data->hb_l)
    {
        block_data->hb_l = "";
    }
    updateComboHBBlocks();
}

void EnteringBlocks::on_comboBox_hb_l_textActivated(const QString &arg1)
{
    block_data->hb_l = arg1.toStdString();
    updateComboHBBlocks();
}

void EnteringBlocks::on_lineEdit_l_hb_l_textChanged(const QString &arg1)
{
    block_data->l_hb_l = arg1.toDouble();
}

void EnteringBlocks::on_pushButton_optimize_clicked()
{
}

void EnteringBlocks::on_comboBox_lrc_activated(int index)
{
    if (index == CONS)
    {
        ui->horizontalWidget_lrc_cons->setVisible(true);
        ui->horizontalWidget_lrc_cont->setVisible(false);
        ui->horizontalWidget_lrc_disc->setVisible(false);

    }
    else if (index == CONT)
    {
        ui->horizontalWidget_lrc_cons->setVisible(false);
        ui->horizontalWidget_lrc_cont->setVisible(true);
        ui->horizontalWidget_lrc_disc->setVisible(false);
    }
    else
    {
        ui->horizontalWidget_lrc_cons->setVisible(false);
        ui->horizontalWidget_lrc_cont->setVisible(false);
        ui->horizontalWidget_lrc_disc->setVisible(true);
    }
    block_data->lrc.type = index;
}

void EnteringBlocks::on_lineEdit_lrc_cons_textChanged(const QString &arg1)
{
    block_data->lrc.cons = arg1.toDouble();
}

void EnteringBlocks::on_lineEdit_lrc_cont_min_textChanged(const QString &arg1)
{
    block_data->lrc.cont_min = arg1.toDouble();
}

void EnteringBlocks::on_lineEdit_lrc_cont_max_textChanged(const QString &arg1)
{
    block_data->lrc.cont_max = arg1.toDouble();
}

void EnteringBlocks::on_checkBox_lrc_disc_gsl_toggled(bool checked)
{
    block_data->lrc.is_golden_section = checked;
    ui->lineEdit_lrc_disc->setEnabled(not checked);
    ui->pushButton_lrc_disc_add->setEnabled(not checked);
    ui->pushButton_lcr_disc_delete->setEnabled(not checked);

    updateLrcCombo();
}

void EnteringBlocks::on_lineEdit_lrc_disc_textChanged(const QString &arg1)
{
    if (arg1 != "")
    {
        lrc_desc_temp = arg1.toDouble();
        ui->pushButton_lrc_disc_add->setEnabled(true);
    }
    else
    {
        lrc_desc_temp = 0;
        ui->pushButton_lrc_disc_add->setEnabled(false);
    }
}

void EnteringBlocks::on_pushButton_lrc_disc_add_clicked()
{
    block_data->lrc.desc_not_gs.push_back(lrc_desc_temp);
    ui->lineEdit_lrc_disc->clear();
    std::sort(block_data->lrc.desc_not_gs.begin(), block_data->lrc.desc_not_gs.end());
    updateLrcCombo();
}

void EnteringBlocks::on_comboBox_lrc_disc_var_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    if (not block_data->lrc.is_golden_section &&
            ui->comboBox_lrc_disc_var->currentText() != "")
    {
        ui->pushButton_lcr_disc_delete->setEnabled(true);
    }
    else
    {
        ui->pushButton_lcr_disc_delete->setEnabled(false);
    }
}

void EnteringBlocks::on_pushButton_lcr_disc_delete_clicked()
{
    double el_for_del = ui->comboBox_lrc_disc_var->currentText().toDouble();
    int pos = -1;
    for (unsigned int i = 0; i < block_data->lrc.desc_not_gs.size(); ++i)
    {
        if (block_data->lrc.desc_not_gs[i] == el_for_del)
        {
            pos = i;
            break;
        }
    }
    if (pos != -1)
    {
        block_data->lrc.desc_not_gs.erase(block_data->lrc.desc_not_gs.begin() + pos);
        updateLrcCombo();
    }
}

