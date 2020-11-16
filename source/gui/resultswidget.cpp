#include "resultswidget.h"
#include "ui_resultswidget.h"

ResultsWidget::ResultsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultsWidget)
{
    ui->setupUi(this);
}

ResultsWidget::~ResultsWidget()
{
    delete ui;
}
