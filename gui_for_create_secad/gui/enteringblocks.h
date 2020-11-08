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

private:
    SMainClass *m;
    Ui::EnteringBlocks *ui;
};

#endif // ENTERINGBLOCKS_H
