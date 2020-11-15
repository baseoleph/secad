#ifndef ENTERINGBLOCKS_H
#define ENTERINGBLOCKS_H

#include <QWidget>

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

private:
    SMainClass *m;
    SBlockData *block_data;

    Ui::EnteringBlocks *ui;

    QString generateNewTemplateTitle();
    void updateComboBlocks(QString current_item);
    void updateComboHBBlocks();
    const QString TEMPLATE_TITLE = "Новый блок";
};

#endif // ENTERINGBLOCKS_H
