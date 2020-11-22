#include "optimizewidget.h"
#include "ui_optimizewidget.h"

OptimizeWidget::OptimizeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptimizeWidget)
{
    ui->setupUi(this);
}

OptimizeWidget::~OptimizeWidget()
{
    delete ui;
}
