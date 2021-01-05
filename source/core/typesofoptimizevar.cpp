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
        av = cons;
        double frac = rand.global()->generateDouble();
        if ((int)cont_min == (int)cont_max)
        {
            av = frac;
        }
        else
        {
            av = rand.global()->bounded((int)cont_min, (int)cont_max) + frac;
        }
    }
    else if (type == DISC)
    {
        av_i = rand.global()->bounded((int)0, (int)desc_link.size());
        av = desc_link[av_i];

        iv_i = av_i;
    }
    iv = av;
}
