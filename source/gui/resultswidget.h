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

    void on_pushButton_stop_clicked();

private:
    QGraphicsScene *scene = nullptr;
   QGraphicsPathItem *item = nullptr;
    QTimer *tm = nullptr;
    SMainClass *m = nullptr;
    Ui::ResultsWidget *ui;
    bool is_clicked = false;

    QPointF fromDataToScene(QPointF p);
    QPolygonF createBlock(SBlockData *e);
    void setScene();
    void drawShip();
};

#endif
