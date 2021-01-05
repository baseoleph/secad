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
//        int p = 0;
//        double lower = desc_link[0];
//        for (unsigned i = 0; i < desc_link.size(); ++i)
//        {
//            if (desc_link[i] <= cons)
//            {
//                p = i;
//                lower = desc_link[i];
//            }
//        }

        av_i = rand.global()->bounded(0, desc_link.size());
        av = desc_link[av_i];

        iv_i = av_i;
//        av = lower;
//        av_i = p;
//        iv_i = av_i;
    }
    iv = av;
}
