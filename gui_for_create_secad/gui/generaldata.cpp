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
    ui->lineEdit_deam->setText(QString::number(general->deam));
    ui->lineEdit_depths->setText(QString::number(general->depths));
    ui->lineEdit_height->setText(QString::number(general->height));
    ui->lineEdit_cb->setText(QString::number(general->cb));
    ui->lineEdit_csd->setText(QString::number(general->csd));
    ui->lineEdit_gm->setText(QString::number(general->gm));
    ui->lineEdit_sef_mea->setText(QString::number(general->sef_mea));
    ui->lineEdit_sef_mro->setText(QString::number(general->sef_mro));
    ui->lineEdit_sef_apra->setText(QString::number(general->sef_apra));
    ui->lineEdit_freeboard->setText(QString::number(general->freeboard));
}

void GeneralData::unFillForms()
{
    ui->lineEdit_project_name->clear();
    ui->lineEdit_length->clear();
    ui->lineEdit_wind_pressure->clear();
    ui->lineEdit_wha->clear();
    ui->lineEdit_length->clear();
    ui->lineEdit_deam->clear();
    ui->lineEdit_depths->clear();
    ui->lineEdit_height->clear();
    ui->lineEdit_cb->clear();
    ui->lineEdit_csd->clear();
    ui->lineEdit_gm->clear();
    ui->lineEdit_sef_mea->clear();
    ui->lineEdit_sef_mro->clear();
    ui->lineEdit_sef_apra->clear();
    ui->lineEdit_freeboard->clear();

    ui->lineEdit_wind_pressure->setText(QString::number(1200));
    ui->lineEdit_wha->setText(QString::number(15));
}

void GeneralData::on_lineEdit_project_name_textChanged(const QString &arg1)
{
    general->project_name = arg1.toStdString();

}

void GeneralData::on_lineEdit_length_textChanged(const QString &arg1)
{
    general->length = arg1.toDouble();
}

void GeneralData::on_lineEdit_deam_textChanged(const QString &arg1)
{
    general->deam = arg1.toDouble();
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

void GeneralData::on_pushButton_add_clicked()
{
    saveJsonToFile(QString::fromStdString(general->project_name));
}

void GeneralData::saveJsonToFile(QString title)
{
    QJsonObject json_general_obj;
    json_general_obj["project_name"] = title;
    json_general_obj["length"] = general->length;
    json_general_obj["wind_pressure"] = general->wind_pressure;
    json_general_obj["wha"] = general->wha;
    json_general_obj["length"] = general->length;
    json_general_obj["deam"] = general->deam;
    json_general_obj["depths"] = general->depths;
    json_general_obj["height"] = general->height;
    json_general_obj["cb"] = general->cb;
    json_general_obj["csd"] = general->csd;
    json_general_obj["gm"] = general->gm;
    json_general_obj["sef_mea"] = general->sef_mea;
    json_general_obj["sef_mro"] = general->sef_mro;
    json_general_obj["sef_apra"] = general->sef_apra;
    json_general_obj["visibility_zone"] = general->visibility_zone;
    json_general_obj["freeboard"] = general->freeboard;
    json_general_obj["sef_ma"] = general->sef_ma;
    json_general_obj["sef_mo"] = general->sef_mo;
    json_general_obj["sef_apa"] = general->sef_apa;

    QJsonArray json_ar_gsl;
    foreach (auto e, general->gsl)
    {
        json_ar_gsl.append(e);
    }
    json_general_obj["gsl"] = json_ar_gsl;

    QJsonArray json_ar_gsh;
    foreach (auto e, general->gsh)
    {
        json_ar_gsh.append(e);
    }
    json_general_obj["gsh"] = json_ar_gsh;

    QJsonArray json_ar_sef_coef;
    foreach (auto e, general->sef_coef)
    {
        json_ar_sef_coef.append(e);
    }
    json_general_obj["sef_coef"] = json_ar_sef_coef;

    jsonobj["General Data"] = json_general_obj;

    // С помощью диалогового окна получаем имя файла с абсолютным путём
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save Json File"),
                                                        QString::fromStdString(general->project_name),
                                                        tr("*.json")) + ".json";

    QFileInfo fileInfo(saveFileName);   // С помощью QFileInfo
    QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл, иначе может не заработать
//    // Создаём объект файла и открываем его на запись
//    qDebug() << saveFileName;
    QFile jsonFile(saveFileName);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    // Записываем текущий объект Json в файл
    jsonFile.write(QJsonDocument(jsonobj).toJson(QJsonDocument::Indented));
    jsonFile.close();   // Закрываем файл
}
