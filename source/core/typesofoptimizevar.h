#ifndef TYPESOFOPTIMIZEVAR_H
#define TYPESOFOPTIMIZEVAR_H

#include "sconstants.h"
#include <vector>
#include <QDebug>
#include <QRandomGenerator>

typedef std::vector<double> d_vector;

class TypesOfOptimizeVar
{
public:
    TypesOfOptimizeVar();
    int type = CONS;
    double cons = NOTHING_VALUE;
    double av = NOTHING_VALUE;
    double iv = NOTHING_VALUE;
    double cont_min = NOTHING_VALUE;
    double cont_max = NOTHING_VALUE;
    bool is_golden_section = false;

    d_vector desc_link;
    d_vector desc_not_gs;

    void setRandomAvValue();
};

#endif // TYPESOFOPTIMIZEVAR_H
