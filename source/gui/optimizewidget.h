#ifndef OPTIMIZEWIDGET_H
#define OPTIMIZEWIDGET_H

#include <QWidget>

namespace Ui {
class OptimizeWidget;
}

class OptimizeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptimizeWidget(QWidget *parent = nullptr, QString label_text = "");
    ~OptimizeWidget();

private:
    Ui::OptimizeWidget *ui;
    QString label_text;
};

#endif // OPTIMIZEWIDGET_H
