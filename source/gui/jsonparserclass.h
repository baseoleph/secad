#ifndef JSONPARSERCLASS_H
#define JSONPARSERCLASS_H

#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include "../core/smainclass.h"

class JsonParserClass
{
public:
    JsonParserClass(QWidget *parent = nullptr, SMainClass *m = nullptr);

    void saveGeneralData();
    void saveBlocksData();
    void saveData();
    void loadGeneralData(QJsonObject general_json);
    void loadBlocksData(QJsonArray blocks_json);
    void loadData(QString proj_name);

    QJsonObject addToJsonOptimizeObject(TypesOfOptimizeVar* types, int is_gs = 0);
    QWidget *parent;

    SMainClass *m;
    SGeneralData *general;
    BlocksVector blocks;

    void loadFromJsonOptimizeObject(TypesOfOptimizeVar *types, QJsonObject object);
private:
    QJsonObject json_main;

    QString GENERAL = "General";
    QString BLOCKS = "Blocks";

    // GENERAL
    QString s_project_name = "project_name";
    QString s_L = "L";
    QString s_p_w = "p_w";
    QString s_theta = "theta";
    QString s_B = "B";
    QString s_D = "D";
    QString s_T = "T";
    QString s_H = "H";
    QString s_delta = "delta";
    QString s_k_DS = "k_DS";
    QString s_GM = "GM";
    QString s_t_ = "t_";
    QString s_q_ = "q_";
    QString s_p_ = "p_";
    QString s_L_V_max = "L_V_max";
    QString s_FB = "FB";
    QString s_t = "t";
    QString s_q = "q";
    QString s_p = "p";
    QString s_GS_L = "GS_L";
    QString s_GS_H = "GS_H";
    QString s_cn = "cn";

    QString s_user = "user";
    QString s_calc = "calc";

    // blocks
    QString s_titleblock = "titleblock";
    QString s_habitability = "habitability";
    QString s_pap = "pap";
    QString s_foremast = "foremast";
    QString s_mainmast = "mainmast";
    QString s_funnel = "funnel";
    QString s_wheelhause = "wheelhause";
    QString s_L_HB_L = "L_HB_L";
    QString s_a = "a";
    QString s_b = "b";
    QString s_h = "h";
    QString s_S = "S";
    QString s_M_a = "M_a";
    QString s_M_b = "M_b";
    QString s_x_g = "x_g";
    QString s_z_g = "z_g";
    QString s_X_U_A = "X_U_A";
    QString s_X_U_F = "X_U_F";
    QString s_HB_H = "HB_H";
    QString s_HB_L = "HB_L";
    QString s_sb_h = "sb_h";
    QString s_sb_l = "sb_l";
    QString s_is_hull = "is_hull";
    QString s_Z = "Z";
    QString s_K_L = "K_L";
    QString s_K_H = "K_H";
    QString s_alpha_F = "alpha_F";
    QString s_alpha_A = "alpha_A";
    QString s_X = "X";

    // optimize data
    QString s_desc_not_gs = "desc_not_gs";
    QString s_type = "type";
    QString s_cons = "cons";
    QString s_cont_min = "cont_min";
    QString s_cont_max = "cont_max";
    QString s_is_golden_section = "is_golden_section";
    QString s_av = "av";
    QString s_av_i = "av_i";
    QString s_iv = "iv";
    QString s_iv_i = "iv_i";
    QString s_which_gs = "which_gs";
};

#endif // JSONPARSERCLASS_H
