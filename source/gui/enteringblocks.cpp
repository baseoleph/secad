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
    foreach (auto e, opt_vector)
    {
        delete e;
    }
    delete ui;
}

void EnteringBlocks::fillForms()
{
    block_data = m->blocks[current_block_index];

    if (not is_optimize_widgets_created)
    {
        is_optimize_widgets_created = true;
        QString lrc = "lrc";
        QString hrc = "hrc";
        QString fwih = "fwih";
        QString awih = "awih";
        QString x = "x";

        opt_vector.insert(lrc, new OptimizeWidget(this, m, block_data, "Коэффициент пропорциональности длины"));
        opt_vector.insert(hrc, new OptimizeWidget(this, m, block_data, "Коэффициент пропорциональности высоты"));
        opt_vector.insert(fwih, new OptimizeWidget(this, m, block_data, "Угол наклона носовой стенки, градус"));
        opt_vector.insert(awih, new OptimizeWidget(this, m, block_data, "Угол наклона кормовой стенки, градус"));
        opt_vector.insert(x, new OptimizeWidget(this, m, block_data, "Ордината размещения, м"));

        opt_vector[lrc]->setGSState(GSL);
        opt_vector[hrc]->setGSState(GSH);

        ui->widget->layout()->addWidget(opt_vector[lrc]);
        ui->widget->layout()->addWidget(opt_vector[hrc]);
        ui->widget->layout()->addWidget(opt_vector[fwih]);
        ui->widget->layout()->addWidget(opt_vector[awih]);
        ui->widget->layout()->addWidget(opt_vector[x]);
    }
    ui->lineEdit_titleblock->setText(block_data->titleblock);

    setTextInLineEdit(ui->lineEdit_l_hb_l, block_data->L_HB_L);

    ui->checkBox_foremast->setChecked(block_data->foremast);
    ui->checkBox_funnel->setChecked(block_data->funnel);
    ui->checkBox_habitability->setChecked(block_data->habitability);
    ui->checkBox_pap->setChecked(block_data->pap);
    ui->checkBox_mainmast->setChecked(block_data->mainmast);
    ui->checkBox_wheelhouse->setChecked(block_data->wheelhause);

    foreach (auto e, opt_vector)
    {
        e->setBlock(block_data);
        e->setTextInLineEditWidgets();
        e->updateWidgetsDCC();
        e->updateCombo();
        e->setCheckBoxState();
    }
}

void EnteringBlocks::setUpForms()
{
    if (m->blocks.size() != 0)
    {
        ui->widget_block->setEnabled(true);
        current_block_index = 0;
        block_data = m->blocks[current_block_index];
        foreach (auto e, m->blocks)
        {
            titles.append(&e->titleblock);
        }

        updateComboBlocks();
        foreach (auto e, opt_vector)
        {
            e->updateWidgetsDCC();
        }
    }
}

SMainClass *EnteringBlocks::getM()
{
    return m;
}

void EnteringBlocks::on_lineEdit_titleblock_textChanged(const QString &arg1)
{
    block_data->titleblock = arg1;
    updateComboBlocks();
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
    current_block_index = m->blocks.size()-1;
    block_data = m->blocks[current_block_index];
    QString new_title = generateNewTemplateTitle();
    block_data->titleblock = new_title;
    block_data->HB_H = NOTHING_VALUE;
    block_data->HB_L = NOTHING_VALUE;
    updateComboBlocks();
    foreach (auto e, opt_vector)
    {
        e->updateWidgetsDCC();
    }
}

void EnteringBlocks::on_comboBox_blocks_activated(int index)
{
    current_block_index = index;
    fillForms();
}

QString EnteringBlocks::generateNewTemplateTitle()
{
    QString new_title = TEMPLATE_TITLE;
    QStringList list_of_block_titles;
    foreach (auto e, m->blocks)
    {
       list_of_block_titles.append(e->titleblock);
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

void EnteringBlocks::updateComboBlocks()
{
    ui->comboBox_blocks->clear();

    foreach (auto e, m->blocks)
    {
        ui->comboBox_blocks->addItem(e->titleblock);
    }

    updateComboHBBlocks();

    ui->comboBox_blocks->setCurrentIndex(current_block_index);
    ui->comboBox_blocks->activated(current_block_index);
}

void EnteringBlocks::updateComboHBBlocks()
{
    ui->comboBox_hb_h->clear();
    ui->comboBox_hb_l->clear();
    ui->comboBox_hb_h->addItem("");
    ui->comboBox_hb_l->addItem("");

    for (unsigned i = 0; i < m->blocks.size(); ++i)
    {
        ui->comboBox_hb_h->addItem(m->blocks[i]->titleblock);
        ui->comboBox_hb_l->addItem(m->blocks[i]->titleblock);
    }


    ui->comboBox_hb_h->setCurrentIndex(block_data->HB_H);
    ui->comboBox_hb_l->setCurrentIndex(block_data->HB_L);
}

void EnteringBlocks::setTextInLineEdit(QLineEdit *line, double val)
{
    if (val == NOTHING_VALUE)
    {
        line->setText("");
    }
    else
    {
        line->setText(QString::number(val));
    }
}


void EnteringBlocks::on_comboBox_hb_h_activated(int index)
{
    block_data->HB_H = index;
}

void EnteringBlocks::on_comboBox_hb_l_activated(int index)
{
    block_data->HB_L = index;
}

void EnteringBlocks::on_lineEdit_l_hb_l_textChanged(const QString &arg1)
{
    block_data->L_HB_L = arg1.toDouble();
}

void EnteringBlocks::on_pushButton_optimize_clicked()
{
}

void EnteringBlocks::on_pushButton_calc_clicked()
{
    m->calculateData();
}
