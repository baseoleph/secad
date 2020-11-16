#ifndef ENTERINGBLOCKS_H
#define ENTERINGBLOCKS_H

#include <QWidget>
#include <iterator>
#include <QLineEdit>
#include <QtAlgorithms>

#include "../core/smainclass.h"

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

    void on_comboBox_blocks_textActivated(const QString &arg1);

    void on_comboBox_hb_h_textActivated(const QString &arg1);

    void on_comboBox_hb_l_textActivated(const QString &arg1);

    void on_lineEdit_l_hb_l_textChanged(const QString &arg1);

    void on_pushButton_optimize_clicked();

    void on_comboBox_lrc_activated(int index);

    void on_lineEdit_lrc_cons_textChanged(const QString &arg1);

    void on_lineEdit_lrc_cont_min_textChanged(const QString &arg1);

    void on_lineEdit_lrc_cont_max_textChanged(const QString &arg1);

    void on_checkBox_lrc_disc_gsl_toggled(bool checked);

    void on_lineEdit_lrc_disc_textChanged(const QString &arg1);

    void on_pushButton_lrc_disc_add_clicked();

    void on_comboBox_lrc_disc_var_currentTextChanged(const QString &arg1);

    void on_pushButton_lcr_disc_delete_clicked();

private:
    SMainClass *m;
    SBlockData *block_data;

    Ui::EnteringBlocks *ui;

    QString generateNewTemplateTitle();
    void updateComboBlocks(QString current_item);
    void updateComboHBBlocks();
    void setTextInLineEdit(QLineEdit *line, double val);
    void updateLrcCombo();
    // blocks with disc cont and cons values
    void updateWidgetsDCC();
    const QString TEMPLATE_TITLE = "Новый блок";

    double lrc_desc_temp;
};

#endif // ENTERINGBLOCKS_H
