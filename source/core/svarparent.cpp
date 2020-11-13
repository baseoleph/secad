#include "svarparent.h"
#include <QDebug>
SVarParent::SVarParent()
{
    qDebug() << 10;
}

void SVarParent::setType(int type)
{
    this->type = type;
}

int SVarParent::getInt(int type)
{
    if (type == CONST)
    {
        return constant.t;
    }
    else if (type == CONT)
    {
        return continuous.t;
    }
    else if (type == DISC)
    {
        return discrete.t;
    }
    else
    {
        return 0;
    }
}
