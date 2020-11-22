#include "optimizewidget.h"
#include "ui_optimizewidget.h"

OptimizeWidget::OptimizeWidget(QWidget *parent, QString label_text) :
    QWidget(parent),
    ui(new Ui::OptimizeWidget)
{
    ui->setupUi(this);
    this->label_text = label_text;
    ui->label->setText(label_text);
}

OptimizeWidget::~OptimizeWidget()
{
    delete ui;
}
