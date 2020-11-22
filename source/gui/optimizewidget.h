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
    explicit OptimizeWidget(QWidget *parent = nullptr);
    ~OptimizeWidget();

private:
    Ui::OptimizeWidget *ui;
};

#endif // OPTIMIZEWIDGET_H
