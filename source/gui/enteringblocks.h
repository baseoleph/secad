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

#ifndef ENTERINGBLOCKS_H
#define ENTERINGBLOCKS_H

#include <QWidget>
#include <QMap>
#include <iterator>
#include <QLineEdit>
#include <QtAlgorithms>

#include "../core/smainclass.h"
#include "optimizewidget.h"

namespace Ui {
class EnteringBlocks;
}

class EnteringBlocks : public QWidget
{
    Q_OBJECT

public:
    explicit EnteringBlocks(QWidget *parent = nullptr, SMainClass *m = nullptr);
    ~EnteringBlocks();

    void fillForms();
    void setUpForms();

protected:
    SMainClass* getM();

signals:
    void signalSaveEnteringBlocks();

private slots:
    void on_lineEdit_titleblock_textChanged(const QString &arg1);

    void on_checkBox_habitability_toggled(bool checked);

    void on_checkBox_wheelhouse_toggled(bool checked);

    void on_checkBox_pap_toggled(bool checked);

    void on_checkBox_mainmast_toggled(bool checked);

    void on_checkBox_foremast_toggled(bool checked);

    void on_checkBox_funnel_toggled(bool checked);

    void on_pushButton_saveEnteringData_clicked();

    void on_pushButton_addBlock_clicked();

    void on_lineEdit_l_hb_l_textChanged(const QString &arg1);

    void on_comboBox_blocks_activated(int index);

    void on_comboBox_hb_h_activated(int index);

    void on_comboBox_hb_l_activated(int index);

    void on_pushButton_delete_block_clicked();

private:
    SMainClass *m;
    SBlockData *block_data;

    OptimizeWidget *opt;
    QMap<QString, OptimizeWidget *> opt_vector;

    Ui::EnteringBlocks *ui;

    QString generateNewTemplateTitle();
    void updateComboBlocks();
    void updateComboHBBlocks();
    void setTextInLineEdit(QLineEdit *line, double val);

    // blocks with disc cont and cons values
    const QString TEMPLATE_TITLE = "Новый блок";

    QList<QString*> titles;
    QVector<unsigned> hbh_really_vector;
    unsigned current_block_index;

    bool is_optimize_widgets_created = false;
};

#endif // ENTERINGBLOCKS_H
