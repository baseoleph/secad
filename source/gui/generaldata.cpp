#include "generaldata.h"
#include "ui_generaldata.h"

GeneralData::GeneralData(QWidget *parent, SMainClass *m) :
    QWidget(parent),
    ui(new Ui::GeneralData)
{
    ui->setupUi(this);
    new QVBoxLayout(ui->widget_chart);
    general = m->general;
    initChart();

    ui->lineEdit_wind_pressure->setText(QString::number(general->p_w));
    ui->lineEdit_wha->setText(QString::number(general->theta));

    scene = new QGraphicsScene(this);
}

GeneralData::~GeneralData()
{
    delete series;
    delete chart;
    delete scene;
    delete ui;
}

void GeneralData::fillForms()
{
    ui->lineEdit_project_name->setText(general->project_name);
    ui->lineEdit_length->setText(QString::number(general->L));
    ui->lineEdit_wind_pressure->setText(QString::number(general->p_w));
    ui->lineEdit_wha->setText(QString::number(general->theta));
    ui->lineEdit_length->setText(QString::number(general->L));
    ui->lineEdit_beam->setText(QString::number(general->B));
    ui->lineEdit_draft->setText(QString::number(general->T));
    ui->lineEdit_height->setText(QString::number(general->H));
    ui->lineEdit_cb->setText(QString::number(general->delta));
    ui->lineEdit_csd->setText(QString::number(general->k_DS));
    ui->lineEdit_gm->setText(QString::number(general->GM));
    ui->lineEdit_sef_mea->setText(QString::number(general->t_));
    ui->lineEdit_sef_mro->setText(QString::number(general->q_));
    ui->lineEdit_sef_apra->setText(QString::number(general->p_));
    ui->lineEdit_freeboard->setText(QString::number(general->FB));

    QString str_gsl = "{";
    foreach (auto e, general->GS_L)
    {
       str_gsl += QString::number(e) + ", ";
    }
    str_gsl.chop(2);
    str_gsl += "}";
    ui->lineEdit_gsl->setText(str_gsl);

    QString str_gsh = "{";
    foreach (auto e, general->GS_H)
    {
       str_gsh += QString::number(e) + ", ";
    }
    str_gsh.chop(2);
    str_gsh += "}";
    ui->lineEdit_gsh->setText(str_gsh);
}

void GeneralData::unFillForms()
{
    ui->lineEdit_project_name->clear();
    ui->lineEdit_length->clear();
    ui->lineEdit_wind_pressure->clear();
    ui->lineEdit_wha->clear();
    ui->lineEdit_length->clear();
    ui->lineEdit_beam->clear();
    ui->lineEdit_draft->clear();
    ui->lineEdit_height->clear();
    ui->lineEdit_cb->clear();
    ui->lineEdit_csd->clear();
    ui->lineEdit_gm->clear();
    ui->lineEdit_sef_mea->clear();
    ui->lineEdit_sef_mro->clear();
    ui->lineEdit_sef_apra->clear();
    ui->lineEdit_freeboard->clear();

    ui->lineEdit_wind_pressure->setText(QString::number(WIND_PRESSURE));
    ui->lineEdit_wha->setText(QString::number(WHA));
}

double GeneralData::sef_function(double x)
{
    double a0 = general->cn[0];
    double a1 = general->cn[1];
    double a2 = general->cn[2];
    double a3 = general->cn[3];
    return a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
}

void GeneralData::initChart()
{
    series = new QSplineSeries();
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->widget_chart->layout()->addWidget(chartView);
}

void GeneralData::on_lineEdit_project_name_textChanged(const QString &arg1)
{
    general->project_name = arg1;
}

void GeneralData::on_lineEdit_length_textChanged(const QString &arg1)
{
    general->L = arg1.toDouble();
}

void GeneralData::on_lineEdit_beam_textChanged(const QString &arg1)
{
    general->B = arg1.toDouble();
}

void GeneralData::on_lineEdit_draft_textChanged(const QString &arg1)
{
    general->T = arg1.toDouble();
}

void GeneralData::on_lineEdit_height_textChanged(const QString &arg1)
{
    general->H = arg1.toDouble();
}

void GeneralData::on_lineEdit_gm_textChanged(const QString &arg1)
{
    general->GM = arg1.toDouble();
}

void GeneralData::on_lineEdit_cb_textChanged(const QString &arg1)
{
    general->delta = arg1.toDouble();
}

void GeneralData::on_lineEdit_csd_textChanged(const QString &arg1)
{
    general->k_DS = arg1.toDouble();
}

void GeneralData::on_lineEdit_wind_pressure_textChanged(const QString &arg1)
{
    general->p_w = arg1.toDouble();
}

void GeneralData::on_lineEdit_wha_textChanged(const QString &arg1)
{
    general->theta = arg1.toDouble();
}

void GeneralData::on_lineEdit_sef_mea_textChanged(const QString &arg1)
{
    general->t_ = arg1.toDouble();
}

void GeneralData::on_lineEdit_sef_mro_textChanged(const QString &arg1)
{
    general->q_ = arg1.toDouble();
}

void GeneralData::on_lineEdit_sef_apra_textChanged(const QString &arg1)
{
    general->p_ = arg1.toDouble();
}

void GeneralData::on_pushButton_save_clicked()
{
    signalSaveGeneralData();
}

void GeneralData::on_pushButton_calc_clicked()
{
    general->calcData();
    fillForms();
    series->clear();
    for (double i = 0; i <= general->L; ++i)
    {
        series->append(QPointF(i, sef_function(i)));
    }
    chart->axes(Qt::Vertical).first()->setRange(0, general->t_ * 1.1);
    chart->axes(Qt::Horizontal).first()->setRange(0, general->L);
}
