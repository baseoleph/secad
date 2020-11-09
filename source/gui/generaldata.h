#ifndef GENERALDATA_H
#define GENERALDATA_H

#include <QWidget>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include "../core/smainclass.h"

namespace Ui {
class GeneralData;
}

class GeneralData : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralData(QWidget *parent = nullptr, SMainClass *m = nullptr);
    ~GeneralData();

    void fillForms();
    void unFillForms();

private slots:
    void on_lineEdit_project_name_textChanged(const QString &arg1);
    void on_lineEdit_length_textChanged(const QString &arg1);
    void on_lineEdit_beam_textChanged(const QString &arg1);
    void on_lineEdit_depths_textChanged(const QString &arg1);
    void on_lineEdit_height_textChanged(const QString &arg1);
    void on_lineEdit_gm_textChanged(const QString &arg1);
    void on_lineEdit_cb_textChanged(const QString &arg1);
    void on_lineEdit_csd_textChanged(const QString &arg1);
    void on_lineEdit_wind_pressure_textChanged(const QString &arg1);
    void on_lineEdit_wha_textChanged(const QString &arg1);
    void on_lineEdit_sef_mea_textChanged(const QString &arg1);
    void on_lineEdit_sef_mro_textChanged(const QString &arg1);
    void on_lineEdit_sef_apra_textChanged(const QString &arg1);

    void on_pushButton_save_clicked();
    void on_pushButton_calc_clicked();

private:
    Ui::GeneralData *ui;
    SGeneralData *general;
    QJsonObject jsonobj;

    void saveJsonToFile(QString title);
};

#endif // GENERALDATA_H
