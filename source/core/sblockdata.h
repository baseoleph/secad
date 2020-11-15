#ifndef SBLOCKDATA_H
#define SBLOCKDATA_H

#include "svarparent.h"
#include <vector>
#include <string>

typedef std::string string;

class SBlockData
{
public:
    SBlockData();

    std::vector<SVarParent *> optimize_vect;

    double lrc;
    double hrc;
    double fwih;
    double awih;
    double x;
    double z;
    bool habitability;
    bool pap;
    bool foremast;
    bool mainmast;
    bool funnel;
    bool wheelhause;
    string hb_h;
    string hb_l;
    double l_hb_l;
    string sb_h;
    string sb_l;
    double bb_l;
    double bb_u;
    double h;
    double s;
    double m_a;
    double m_b;
    double x_g;
    double z_g;
    double uxa;
    double uxf;
};

#endif // SBLOCKDATA_H
