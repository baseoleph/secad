#include "generaldatapainter.h"
#include "ui_generaldatapainter.h"

GeneralDataPainter::GeneralDataPainter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralDataPainter)
{
    ui->setupUi(this);
}

GeneralDataPainter::~GeneralDataPainter()
{
    delete ui;
}

void GeneralDataPainter::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.drawEllipse(0,0,10,10);
}
