// Ship Exterior CAD
// Copyright (C) 2020 baseoleph@gmail.com,
//					  github.com/RoninHikami

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef GENERALDATA_H
#define GENERALDATA_H

#include <QWidget>
#include <QDebug>
#include <QLogValueAxis>
#include <QSplineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>
#include <QGraphicsScene>
#include <QPainterPath>
#include "../core/smainclass.h"


using namespace QtCharts;
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

signals:
    void signalSaveGeneralData();

private slots:
    void on_lineEdit_project_name_textChanged(const QString &arg1);
    void on_lineEdit_length_textChanged(const QString &arg1);
    void on_lineEdit_beam_textChanged(const QString &arg1);
    void on_lineEdit_draft_textChanged(const QString &arg1);
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

    void on_lineEdit_displacement_textChanged(const QString &arg1);

private:
    Ui::GeneralData *ui;
    SGeneralData *general;
    QGraphicsScene *scene;
    QSplineSeries *series;
    QChart *chart;
    void initChart();
};

#endif // GENERALDATA_H
