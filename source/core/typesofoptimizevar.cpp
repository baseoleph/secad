#include "typesofoptimizevar.h"

TypesOfOptimizeVar::TypesOfOptimizeVar()
{

}

void TypesOfOptimizeVar::setRandomAvValue()
{
    QRandomGenerator rand = QRandomGenerator();

    if (type == CONS)
    {
        av = cons;
    }
    else if (type == CONT)
    {
        double frac = rand.global()->generateDouble();
        av = rand.global()->bounded((int)cont_min, (int)cont_max) + frac;
    }
    else if (type == DISC)
    {
        int l = desc_link.size();
        int i = rand.global()->bounded(0, desc_link.size());
        av = desc_link[i];
//        av = (*desc_link)[0];
    }
}
