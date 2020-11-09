#include "generaldata.h"
#include "ui_generaldata.h"

GeneralData::GeneralData(QWidget *parent, SMainClass *m) :
    QWidget(parent),
    ui(new Ui::GeneralData)
{
    ui->setupUi(this);
    general = m->general;

    ui->lineEdit_wind_pressure->setText(QString::number(general->wind_pressure));
    ui->lineEdit_wha->setText(QString::number(general->wha));

    scene = new QGraphicsScene(this);
}

GeneralData::~GeneralData()
{
    delete ui;
}

void GeneralData::fillForms()
{
    ui->lineEdit_project_name->setText(QString::fromStdString(general->project_name));
    ui->lineEdit_length->setText(QString::number(general->length));
    ui->lineEdit_wind_pressure->setText(QString::number(general->wind_pressure));
    ui->lineEdit_wha->setText(QString::number(general->wha));
    ui->lineEdit_length->setText(QString::number(general->length));
    ui->lineEdit_beam->setText(QString::number(general->beam));
    ui->lineEdit_depths->setText(QString::number(general->depths));
    ui->lineEdit_height->setText(QString::number(general->height));
    ui->lineEdit_cb->setText(QString::number(general->cb));
    ui->lineEdit_csd->setText(QString::number(general->csd));
    ui->lineEdit_gm->setText(QString::number(general->gm));
    ui->lineEdit_sef_mea->setText(QString::number(general->sef_mea));
    ui->lineEdit_sef_mro->setText(QString::number(general->sef_mro));
    ui->lineEdit_sef_apra->setText(QString::number(general->sef_apra));
    ui->lineEdit_freeboard->setText(QString::number(general->freeboard));

    QString str_gsl = "{";
    foreach (auto e, general->gsl)
    {
       str_gsl += QString::number(e) + ", ";
    }
    str_gsl.chop(2);
    str_gsl += "}";
    ui->lineEdit_gsl->setText(str_gsl);

    QString str_gsh = "{";
    foreach (auto e, general->gsh)
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
    ui->lineEdit_depths->clear();
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


void GeneralData::saveJsonToFile(QString title)
{
    QJsonObject json_main;
    QJsonObject json_general_calc_data;
    QJsonObject json_general_user_data;
    json_general_user_data["project_name"] = title;
    json_general_user_data["length"] = general->length;
    json_general_user_data["wind_pressure"] = general->wind_pressure;
    json_general_user_data["wha"] = general->wha;
    json_general_user_data["length"] = general->length;
    json_general_user_data["beam"] = general->beam;
    json_general_user_data["depths"] = general->depths;
    json_general_user_data["height"] = general->height;
    json_general_user_data["cb"] = general->cb;
    json_general_user_data["csd"] = general->csd;
    json_general_user_data["gm"] = general->gm;
    json_general_user_data["sef_mea"] = general->sef_mea;
    json_general_user_data["sef_mro"] = general->sef_mro;
    json_general_user_data["sef_apra"] = general->sef_apra;

    json_general_calc_data["visibility_zone"] = general->visibility_zone;
    json_general_calc_data["freeboard"] = general->freeboard;
    json_general_calc_data["sef_ma"] = general->sef_ma;
    json_general_calc_data["sef_mo"] = general->sef_mo;
    json_general_calc_data["sef_apa"] = general->sef_apa;

    QJsonArray json_ar_gsl;
    foreach (auto e, general->gsl)
    {
        json_ar_gsl.append(e);
    }
    json_general_calc_data["gsl"] = json_ar_gsl;

    QJsonArray json_ar_gsh;
    foreach (auto e, general->gsh)
    {
        json_ar_gsh.append(e);
    }
    json_general_calc_data["gsh"] = json_ar_gsh;

    QJsonArray json_ar_sef_coef;
    foreach (auto e, general->sef_coef)
    {
        json_ar_sef_coef.append(e);
    }
    json_general_calc_data["sef_coef"] = json_ar_sef_coef;

    json_main["user"] = json_general_user_data;
    json_main["calc"] = json_general_calc_data;

    jsonobj["General Data"] = json_main;
    // С помощью диалогового окна получаем имя файла с абсолютным путём
#ifdef Q_OS_LINUX
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save Json File"),
                                                        QString::fromStdString(general->project_name),
                                                        tr("*.json")) + ".json";
#else
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save Json File"),
                                                        QString::fromStdString(general->project_name),
                                                        tr("*.json"));
#endif

    // Узнаем директорию для сохранения файла
    QFileInfo fileInfo(saveFileName);
    // Делаем ее текущей
    QDir::setCurrent(fileInfo.path());

    QFile jsonFile(saveFileName);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    // Записываем текущий объект Json в файл
    jsonFile.write(QJsonDocument(jsonobj).toJson(QJsonDocument::Indented));
    jsonFile.close();
}

double GeneralData::sef_function(double x)
{
    double a0 = general->sef_coef[0];
    double a1 = general->sef_coef[1];
    double a2 = general->sef_coef[2];
    double a3 = general->sef_coef[3];
    return a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
}

void GeneralData::on_lineEdit_project_name_textChanged(const QString &arg1)
{
    general->project_name = arg1.toStdString();
}

void GeneralData::on_lineEdit_length_textChanged(const QString &arg1)
{
    general->length = arg1.toDouble();
}

void GeneralData::on_lineEdit_beam_textChanged(const QString &arg1)
{
    general->beam = arg1.toDouble();
}

void GeneralData::on_lineEdit_depths_textChanged(const QString &arg1)
{
    general->depths = arg1.toDouble();
}

void GeneralData::on_lineEdit_height_textChanged(const QString &arg1)
{
    general->height = arg1.toDouble();
}

void GeneralData::on_lineEdit_gm_textChanged(const QString &arg1)
{
    general->gm = arg1.toDouble();
}

void GeneralData::on_lineEdit_cb_textChanged(const QString &arg1)
{
    general->cb = arg1.toDouble();
}

void GeneralData::on_lineEdit_csd_textChanged(const QString &arg1)
{
    general->csd = arg1.toDouble();
}

void GeneralData::on_lineEdit_wind_pressure_textChanged(const QString &arg1)
{
    general->wind_pressure = arg1.toDouble();
}

void GeneralData::on_lineEdit_wha_textChanged(const QString &arg1)
{
    general->wha = arg1.toDouble();
}

void GeneralData::on_lineEdit_sef_mea_textChanged(const QString &arg1)
{
    general->sef_mea = arg1.toDouble();
}

void GeneralData::on_lineEdit_sef_mro_textChanged(const QString &arg1)
{
    general->sef_mro = arg1.toDouble();
}

void GeneralData::on_lineEdit_sef_apra_textChanged(const QString &arg1)
{
    general->sef_apra = arg1.toDouble();
}

void GeneralData::on_pushButton_save_clicked()
{
    saveJsonToFile(QString::fromStdString(general->project_name));
}

void GeneralData::on_pushButton_calc_clicked()
{
    general->calcData();
    fillForms();

    scene->clear();
    qreal width = ui->graphicsView->width();
    qreal height = ui->graphicsView->height();
    scene->setSceneRect(0, 0, width, height);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->addLine(-1, height/2, width+10, height/2);
    scene->addLine(10, -1, 10, height+10);
    qreal xscale = width / general->length;
    QPointF origin_p(10, height/2);
    QPainterPath path;
    path.moveTo(origin_p + QPointF(0, -sef_function(0)));
    for (double i = 0; i <= general->length; ++i)
    {
        path.lineTo(origin_p + QPointF(i/* * xscale*/, -sef_function(i)));
    }
    scene->addPath(path);
}
