#include "enteringblocks.h"
#include "ui_enteringblocks.h"

EnteringBlocks::EnteringBlocks(QWidget *parent, SMainClass *m) :
    QWidget(parent),
    ui(new Ui::EnteringBlocks)
{
    ui->setupUi(this);
    this->m = m;

    ui->widget_block->setEnabled(false);

//    opt = new OptimizeWidget(this, "asdf");
//    QHBoxLayout *vbox = new QHBoxLayout(opt);
//    ui->widget->layout()->addItem(vbox);
//    ui->widget->layout()->addWidget(opt);

//    ui->widget->
//    vbox->addWidget(opt, 0);
//    ui->widget->setLayout(vbox);
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

        ui->widget->layout()->addWidget(opt_vector[lrc]);
        ui->widget->layout()->addWidget(opt_vector[hrc]);
        ui->widget->layout()->addWidget(opt_vector[fwih]);
        ui->widget->layout()->addWidget(opt_vector[awih]);
        ui->widget->layout()->addWidget(opt_vector[x]);
    }
    ui->lineEdit_titleblock->setText(block_data->titleblock);

    setTextInLineEdit(ui->lineEdit_l_hb_l, block_data->l_hb_l);

    ui->checkBox_foremast->setChecked(block_data->foremast);
    ui->checkBox_funnel->setChecked(block_data->funnel);
    ui->checkBox_habitability->setChecked(block_data->habitability);
    ui->checkBox_pap->setChecked(block_data->pap);
    ui->checkBox_mainmast->setChecked(block_data->mainmast);
    ui->checkBox_wheelhouse->setChecked(block_data->wheelhause);

    setTextInLineEdit(ui->lineEdit_lrc_cons, block_data->lrc.cons);
    setTextInLineEdit(ui->lineEdit_lrc_cont_max, block_data->lrc.cont_max);
    setTextInLineEdit(ui->lineEdit_lrc_cont_min, block_data->lrc.cont_min);

    foreach (auto e, opt_vector)
    {
        e->updateWidgetsDCC();
        e->updateCombo();
    }

    updateWidgetsDCC();
    updateLrcCombo();
//    updateWidgetsDCC();
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
        updateWidgetsDCC();
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
    block_data->hb_h = NOTHING_VALUE;
    block_data->hb_l = NOTHING_VALUE;
    updateComboBlocks();
    foreach (auto e, opt_vector)
    {
        e->updateWidgetsDCC();
    }
    updateWidgetsDCC();
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


    ui->comboBox_hb_h->setCurrentIndex(block_data->hb_h);
    ui->comboBox_hb_l->setCurrentIndex(block_data->hb_l);
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

void EnteringBlocks::on_comboBox_hb_h_activated(int index)
{
    block_data->hb_h = index;
}

void EnteringBlocks::on_comboBox_hb_l_activated(int index)
{
    block_data->hb_l = index;
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



