#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H

#include <QThread>
#include <QWidget>
#include <QApplication>
#include <QTimer>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include "../core/smainclass.h"

namespace Ui {
class ResultsWidget;
}

class ResultsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResultsWidget(QWidget *parent = nullptr, SMainClass *m_new = nullptr);
    ~ResultsWidget();

private slots:
    void resizeEvent(QResizeEvent *event);

    void on_pushButton_opt_clicked();

private:
    QGraphicsScene *scene = nullptr;
   QGraphicsPathItem *item = nullptr;
    QTimer *tm = nullptr;
    SMainClass *m = nullptr;
    Ui::ResultsWidget *ui;
    bool is_clicked = false;

    QPointF fromDataToScene(QPointF p);
    QPainterPath createBlock(SBlockData *e);
    void setScene();
    void drawShip();
};

#endif
