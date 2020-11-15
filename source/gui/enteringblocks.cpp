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

void EnteringBlocks::updateWidgetsDCC()
{

    SVarParent lrc;

    // Коэффициент пропорциональности высоты блока
    // Height Ratio Coefficient
    // proportion
    SVarParent hrc;

    // Угол наклона носовой стенки блока
    // Fore Wall Inclination Heel
    // degrees
    SVarParent fwih;

    // Угол наклона кормовой стенки блока
    // Aft Wall Inclination Heel
    // degrees
    SVarParent awih;

    // Ордината размещения блока
    // Block Positioning Ordinate
    // metres
    SVarParent x;

    // Аппликата размещения блока
    // Block Positioning Applicate
    // metres
    SVarParent z;

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
        ui->horizontalWidget_lrc_desc->setVisible(false);

    }
    else if (index == CONT)
    {
        ui->horizontalWidget_lrc_cons->setVisible(false);
        ui->horizontalWidget_lrc_cont->setVisible(true);
        ui->horizontalWidget_lrc_desc->setVisible(false);
    }
    else
    {
        ui->horizontalWidget_lrc_cons->setVisible(false);
        ui->horizontalWidget_lrc_cont->setVisible(false);
        ui->horizontalWidget_lrc_desc->setVisible(true);
    }
    block_data->lrc.setType(index);
}
