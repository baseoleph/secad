#include "sblockdata.h"
#include <QDebug>
SBlockData::SBlockData()
{
    for (int i = 0; i < 6; ++i)
    {
        optimize_vect.push_back(new SVarParent());
        qDebug() << i;
    }
}
