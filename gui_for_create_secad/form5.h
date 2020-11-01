#ifndef GOFUCKYOURSELF_H
#define GOFUCKYOURSELF_H

#include <QWidget>

namespace Ui {
class GoFuckYourself;
}

class Form5 : public QWidget
{
    Q_OBJECT

public:
    explicit Form5(QWidget *parent = nullptr);
    ~Form5();

private:
    Ui::GoFuckYourself *ui;
};

#endif // GOFUCKYOURSELF_H
