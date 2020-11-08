#ifndef ENTERINGBLOCKS_H
#define ENTERINGBLOCKS_H

#include <QWidget>

namespace Ui {
class EnteringBlocks;
}

class EnteringBlocks : public QWidget
{
    Q_OBJECT

public:
    explicit EnteringBlocks(QWidget *parent = nullptr);
    ~EnteringBlocks();

private:
    Ui::EnteringBlocks *ui;
};

#endif // ENTERINGBLOCKS_H
