#ifndef OPTIMIZEWIDGET_H
#define OPTIMIZEWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "../core/smainclass.h"
namespace Ui {
class OptimizeWidget;
}

enum
{
GSH,
GSL
};

class OptimizeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptimizeWidget(QWidget *parent = nullptr, SMainClass *m = nullptr, SBlockData *block = nullptr, QString label_text = "");
    ~OptimizeWidget();

    void updateWidgetsDCC();
    void updateCombo();
    void setBlock(SBlockData *block);
    void setGSState(int state);

    void setTextInLineEditWidgets();
    void setTextInLineEdit(QLineEdit *line, double val);
private slots:
    void on_lineEdit_cons_textChanged(const QString &arg1);
    void on_lineEdit_cont_min_textChanged(const QString &arg1);
    void on_lineEdit_cont_max_textChanged(const QString &arg1);
    void on_checkBox_disc_gsl_toggled(bool checked);
    void on_lineEdit_disc_textChanged(const QString &arg1);
    void on_pushButton_disc_add_clicked();
    void on_comboBox_disc_var_currentTextChanged(const QString &arg1);
    void on_pushButton_disc_delete_clicked();
    void on_comboBox_activated(int index);

private:
    Ui::OptimizeWidget *ui;
    QString label_text;
    SMainClass *m;
    SBlockData *block_data;

    TypesOfOptimizeVar *current_type;
    int test = 0;
    double desc_temp;
    bool with_golden_section = false;
    int state_of_gs = GSH;
};

#endif // OPTIMIZEWIDGET_H
