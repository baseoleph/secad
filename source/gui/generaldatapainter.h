#ifndef GENERALDATAPAINTER_H
#define GENERALDATAPAINTER_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class GeneralDataPainter;
}

class GeneralDataPainter : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralDataPainter(QWidget *parent = nullptr);
    ~GeneralDataPainter();

    void paintEvent(QPaintEvent *e);

private:
    Ui::GeneralDataPainter *ui;
};

#endif // GENERALDATAPAINTER_H
