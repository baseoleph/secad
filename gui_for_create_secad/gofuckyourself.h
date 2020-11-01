#ifndef GOFUCKYOURSELF_H
#define GOFUCKYOURSELF_H

#include <QWidget>

namespace Ui {
class GoFuckYourself;
}

class GoFuckYourself : public QWidget
{
    Q_OBJECT

public:
    explicit GoFuckYourself(QWidget *parent = nullptr);
    ~GoFuckYourself();

private:
    Ui::GoFuckYourself *ui;
};

#endif // GOFUCKYOURSELF_H
