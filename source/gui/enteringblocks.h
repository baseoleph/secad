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

private:
    SMainClass *m;
    SBlockData *block_data;

    Ui::EnteringBlocks *ui;
};

#endif // ENTERINGBLOCKS_H
