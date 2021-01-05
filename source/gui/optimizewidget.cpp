#include "optimizewidget.h"
#include "ui_optimizewidget.h"

OptimizeWidget::OptimizeWidget(QWidget *parent, SMainClass *m, SBlockData *block, QString label_text) :
    QWidget(parent),
    ui(new Ui::OptimizeWidget)
{
    ui->setupUi(this);
    this->label_text = label_text;
    this->m = m;
    ui->label->setText(label_text);
    setBlock(block);
}

void OptimizeWidget::setBlock(SBlockData *block)
{
    block_data = block;

    if (label_text == "Коэффициент пропорциональности длины")
    {
        test = 1;
        current_type = &block_data->K_L;
        with_golden_section = true;
    }
    else if ( label_text == "Коэффициент пропорциональности высоты")
    {
        test = 2;
        current_type = &block_data->K_H;
        with_golden_section = true;
    }
    else if ( label_text == "Угол наклона носовой стенки, градус")
    {
        test = 3;
        current_type = &block_data->alpha_F;
        with_golden_section = false;
    }
    else if ( label_text == "Угол наклона кормовой стенки, градус")
    {
        test = 4;
        current_type = &block_data->alpha_A;
        with_golden_section = false;
    }
    else if ( label_text == "Ордината размещения, м")
    {
        test = 5;
        current_type = &block_data->X;
        with_golden_section = false;
    }

    if (not with_golden_section)
    {
        ui->checkBox_disc_gsl->hide();
    }
    else
    {
        ui->checkBox_disc_gsl->show();
    }
}

void OptimizeWidget::setGSState(int state)
{
    state_of_gs = state;
}

OptimizeWidget::~OptimizeWidget()
{
    delete ui;
}

void OptimizeWidget::updateCombo()
{
    if (current_type->is_golden_section)
    {
        if (state_of_gs == GSL)
        {
            current_type->desc_link = m->general->GS_L;
        }
        else
        {
            current_type->desc_link = m->general->GS_H;
        }
    }
    else
    {
        current_type->desc_link = current_type->desc_not_gs;
    }
    ui->comboBox_disc_var->clear();
    foreach (auto e, current_type->desc_link)
    {
        ui->comboBox_disc_var->addItem(QString::number(e));
    }
}


void OptimizeWidget::on_comboBox_activated(int index)
{
    if (index == CONS)
    {
        ui->horizontalWidget_cons->setVisible(true);
        ui->horizontalWidget_cont->setVisible(false);
        ui->horizontalWidget_disc->setVisible(false);

    }
    else if (index == CONT)
    {
        ui->horizontalWidget_cons->setVisible(false);
        ui->horizontalWidget_cont->setVisible(true);
        ui->horizontalWidget_disc->setVisible(false);
    }
    else
    {
        ui->horizontalWidget_cons->setVisible(false);
        ui->horizontalWidget_cont->setVisible(false);
        ui->horizontalWidget_disc->setVisible(true);
    }

    current_type->type = index;
}

void OptimizeWidget::updateWidgetsDCC()
{
    ui->comboBox->setCurrentIndex(current_type->type);
    ui->comboBox->activated(current_type->type);
}

void OptimizeWidget::on_lineEdit_cons_textChanged(const QString &arg1)
{
    current_type->cons = arg1.toDouble();
}

void OptimizeWidget::on_lineEdit_cont_min_textChanged(const QString &arg1)
{
    current_type->cont_min = arg1.toDouble();
}

void OptimizeWidget::on_lineEdit_cont_max_textChanged(const QString &arg1)
{
    current_type->cont_max = arg1.toDouble();
}

void OptimizeWidget::on_checkBox_disc_gsl_toggled(bool checked)
{
    current_type->is_golden_section = checked;
    ui->lineEdit_disc->setEnabled(not checked);
    ui->pushButton_disc_add->setEnabled(not checked);
    ui->pushButton_disc_delete->setEnabled(not checked);

    updateCombo();
}

void OptimizeWidget::on_lineEdit_disc_textChanged(const QString &arg1)
{
    if (arg1 != "")
    {
        desc_temp = arg1.toDouble();
        ui->pushButton_disc_add->setEnabled(true);
    }
    else
    {
        desc_temp = 0;
        ui->pushButton_disc_add->setEnabled(false);
    }
}

void OptimizeWidget::on_pushButton_disc_add_clicked()
{
    current_type->desc_not_gs.push_back(desc_temp);
    ui->lineEdit_disc->clear();
    std::sort(current_type->desc_not_gs.begin(), current_type->desc_not_gs.end());
    updateCombo();
}

void OptimizeWidget::on_comboBox_disc_var_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    if (not current_type->is_golden_section &&
            ui->comboBox_disc_var->currentText() != "")
    {
        ui->pushButton_disc_delete->setEnabled(true);
    }
    else
    {
        ui->pushButton_disc_delete->setEnabled(false);
    }
}

void OptimizeWidget::on_pushButton_disc_delete_clicked()
{
    double el_for_del = ui->comboBox_disc_var->currentText().toDouble();
    int pos = -1;
    for (unsigned int i = 0; i < current_type->desc_not_gs.size(); ++i)
    {
        if (current_type->desc_not_gs[i] == el_for_del)
        {
            pos = i;
            break;
        }
    }
    if (pos != -1)
    {
        current_type->desc_not_gs.erase(current_type->desc_not_gs.begin() + pos);
        updateCombo();
    }
}

void OptimizeWidget::setTextInLineEditWidgets()
{
    setTextInLineEdit(ui->lineEdit_cons, current_type->cons);
    setTextInLineEdit(ui->lineEdit_cont_max, current_type->cont_max);
    setTextInLineEdit(ui->lineEdit_cont_min, current_type->cont_min);
}

void OptimizeWidget::setTextInLineEdit(QLineEdit *line, double val)
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

void OptimizeWidget::setCheckBoxState()
{
    ui->checkBox_disc_gsl->setChecked(current_type->is_golden_section);
}
