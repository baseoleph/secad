#include "jsonparserclass.h"

JsonParserClass::JsonParserClass(QWidget *parent, SMainClass *m)
{
    this->parent = parent;
    this->m = m;
}

void JsonParserClass::saveGeneralData()
{
    QJsonObject jsonobj;
    general = m->general;

    QJsonObject json_main_general;
    QJsonObject json_general_calc_data;
    QJsonObject json_general_user_data;
    json_general_user_data[s_project_name] = general->project_name;
    json_general_user_data[s_L] = general->L;
    json_general_user_data[s_p_w] = general->p_w;
    json_general_user_data[s_theta] = general->theta;
    json_general_user_data[s_B] = general->B;
    json_general_user_data[s_D] = general->D;
    json_general_user_data[s_T] = general->T;
    json_general_user_data[s_H] = general->H;
    json_general_user_data[s_delta] = general->delta;
    json_general_user_data[s_k_DS] = general->k_DS;
    json_general_user_data[s_GM] = general->GM;
    json_general_user_data[s_t_] = general->t_;
    json_general_user_data[s_q_] = general->q_;
    json_general_user_data[s_p_] = general->p_;



    json_general_calc_data[s_L_V_max] = general->L_V_max;
    json_general_calc_data[s_FB] = general->FB;
    json_general_calc_data[s_t] = general->t;
    json_general_calc_data[s_q] = general->q;
    json_general_calc_data[s_p] = general->p;


    QJsonArray json_ar_gsl;
    foreach (auto e, general->GS_L)
    {
        json_ar_gsl.append(e);
    }
    json_general_calc_data[s_GS_L] = json_ar_gsl;


    QJsonArray json_ar_gsh;
    foreach (auto e, general->GS_H)
    {
        json_ar_gsh.append(e);
    }
    json_general_calc_data[s_GS_H] = json_ar_gsh;


    QJsonArray json_ar_sef_coef;
    foreach (auto e, general->cn)
    {
        json_ar_sef_coef.append(e);
    }
    json_general_calc_data[s_cn] = json_ar_sef_coef;


    json_main_general[s_user] = json_general_user_data;
    json_main_general[s_calc] = json_general_calc_data;

    json_main[GENERAL] = json_main_general;
}

void JsonParserClass::saveBlocksData()
{
    QJsonArray jsonar;
    blocks = m->blocks;

    foreach (auto e, blocks)
    {
        if (e->titleblock != "")
        {
            QJsonObject jsonobj;
            QJsonObject json_block;
            json_block[s_titleblock] = e->titleblock;
            json_block[s_habitability] = e->habitability;
            json_block[s_pap] = e->pap;
            json_block[s_foremast] = e->foremast;
            json_block[s_mainmast] = e->mainmast;
            json_block[s_funnel] = e->funnel;
            json_block[s_wheelhause] = e->wheelhause;
            json_block[s_L_HB_L] = e->L_HB_L;
            json_block[s_a] = e->a;
            json_block[s_b] = e->b;
            json_block[s_h] = e->h;
            json_block[s_S] = e->S;
            json_block[s_M_a] = e->M_a;
            json_block[s_M_b] = e->M_b;
            json_block[s_x_g] = e->x_g;
            json_block[s_z_g] = e->z_g;
            json_block[s_X_U_A] = e->X_U_A;
            json_block[s_X_U_F] = e->X_U_F;
            json_block[s_HB_H] = e->HB_H;
            json_block[s_HB_L] = e->HB_L;
            json_block[s_sb_h] = e->sb_h;
            json_block[s_sb_l] = e->sb_l;
            json_block[s_is_hull] = e->is_hull;
            json_block[s_Z] = e->Z;
            json_block[s_K_L] = addToJsonOptimizeObject(&e->K_L);
            json_block[s_K_H] = addToJsonOptimizeObject(&e->K_H);
            json_block[s_alpha_F] = addToJsonOptimizeObject(&e->alpha_F);
            json_block[s_alpha_A] = addToJsonOptimizeObject(&e->alpha_A);
            json_block[s_X] = addToJsonOptimizeObject(&e->X);
            jsonar.append(json_block);
        }
    }
    json_main[BLOCKS] = jsonar;
}

void JsonParserClass::saveData()
{
    saveGeneralData();
    saveBlocksData();

    QString saveFileName = QFileDialog::getSaveFileName(parent,
                                                        QObject::tr("Save Json File"),
                                                        m->general->project_name,
                                                        QObject::tr("*.json"));

    // Узнаем директорию для сохранения файла
    QFileInfo fileInfo(saveFileName);
    // Делаем ее текущей
    QDir::setCurrent(fileInfo.path());

    QFile jsonFile(saveFileName);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    // Записываем текущий объект Json в файл
    jsonFile.write(QJsonDocument(json_main).toJson(QJsonDocument::Indented));
    jsonFile.close();
}

void JsonParserClass::loadGeneralData(QJsonObject general_json)
{
    QJsonObject general_obj = general_json.value(s_user).toObject();

    m->general->project_name = general_obj.value(s_project_name).toString();
    m->general->p_w = general_obj.value(s_p_w).toDouble();
    m->general->theta = general_obj.value(s_theta).toDouble();
    m->general->L = general_obj.value(s_L).toDouble();
    m->general->B = general_obj.value(s_B).toDouble();
    m->general->D = general_obj.value(s_D).toDouble();
    m->general->T = general_obj.value(s_T).toDouble();
    m->general->H = general_obj.value(s_H).toDouble();
    m->general->delta = general_obj.value(s_delta).toDouble();
    m->general->k_DS = general_obj.value(s_k_DS).toDouble();
    m->general->GM = general_obj.value(s_GM).toDouble();
    m->general->t_ = general_obj.value(s_t_).toDouble();
    m->general->q_ = general_obj.value(s_q_).toDouble();
    m->general->p_ = general_obj.value(s_p_).toDouble();

    general_obj = general_json.value(s_calc).toObject();

    m->general->L_V_max = general_obj.value(s_L_V_max).toDouble();
    m->general->FB = general_obj.value(s_FB).toDouble();
    m->general->t = general_obj.value(s_t).toDouble();
    m->general->q = general_obj.value(s_q).toDouble();
    m->general->p = general_obj.value(s_p).toDouble();

    QJsonArray json_gsl = general_obj.value(s_GS_L).toArray();
    m->general->GS_L.clear();
    foreach (auto e, json_gsl)
    {
        m->general->GS_L.push_back(e.toDouble());
    }
    QJsonArray json_gsh = general_obj.value(s_GS_H).toArray();
    m->general->GS_H.clear();
    foreach (auto e, json_gsh)
    {
        m->general->GS_H.push_back(e.toDouble());
    }

    QJsonArray json_sef_coef = general_obj.value(s_cn).toArray();
    m->general->cn.clear();
    foreach (auto e, json_sef_coef)
    {
        m->general->cn.push_back(e.toDouble());
    }
}

void JsonParserClass::loadBlocksData(QJsonArray blocks_json)
{
    blocks.clear();
    foreach (auto e, blocks_json)
    {
        m->addBlock();
        blocks = m->blocks;
        SBlockData *block_data = blocks[blocks.size() - 1];
        block_data->titleblock = e.toObject()[s_titleblock].toString();
        block_data->habitability = e.toObject()[s_habitability].toBool();
        block_data->pap = e.toObject()[s_pap].toBool();
        block_data->foremast = e.toObject()[s_foremast].toBool();
        block_data->mainmast = e.toObject()[s_mainmast].toBool();
        block_data->funnel = e.toObject()[s_funnel].toBool();
        block_data->wheelhause = e.toObject()[s_wheelhause].toBool();
        block_data->L_HB_L = e.toObject()[s_L_HB_L].toDouble();
        block_data->a = e.toObject()[s_a].toDouble();
        block_data->b = e.toObject()[s_b].toDouble();
        block_data->h = e.toObject()[s_h].toDouble();
        block_data->S = e.toObject()[s_S].toDouble();

        block_data->M_a = e.toObject()[s_M_a].toDouble();
        block_data->M_b = e.toObject()[s_M_b].toDouble();
        block_data->x_g = e.toObject()[s_x_g].toDouble();
        block_data->z_g = e.toObject()[s_z_g].toDouble();
        block_data->X_U_A = e.toObject()[s_X_U_A].toDouble();
        block_data->X_U_F = e.toObject()[s_X_U_F].toDouble();
        block_data->HB_H = e.toObject()[s_HB_H].toInt();
        block_data->HB_L = e.toObject()[s_HB_L].toInt();
        block_data->sb_h = e.toObject()[s_sb_h].toString();
        block_data->sb_l = e.toObject()[s_sb_l].toString();
        block_data->is_hull = e.toObject()[s_is_hull].toBool();
        block_data->Z = e.toObject()[s_Z].toDouble();
        loadFromJsonOptimizeObject(&block_data->K_L, e.toObject()[s_K_L].toObject());
        loadFromJsonOptimizeObject(&block_data->K_H, e.toObject()[s_K_H].toObject());
        loadFromJsonOptimizeObject(&block_data->alpha_F, e.toObject()[s_alpha_F].toObject());
        loadFromJsonOptimizeObject(&block_data->alpha_A, e.toObject()[s_alpha_A].toObject());
        loadFromJsonOptimizeObject(&block_data->X, e.toObject()[s_X].toObject());


    }
}

void JsonParserClass::loadData(QString proj_name)
{
        // Выбираем файл
        QString openFileName = proj_name + ".json";
        QFile jsonFile(openFileName);
        if (!jsonFile.open(QIODevice::ReadOnly))
        {
            return;
        }

        // Считываем весь файл
        QByteArray saveData = jsonFile.readAll();
        jsonFile.close();
        // Создаём QJsonDocument
        QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
        // Из которого выделяем объект в текущий рабочий QJsonObject
        QJsonObject json = jsonDocument.object();

        loadGeneralData(json.value(GENERAL).toObject());
        loadBlocksData(json.value(BLOCKS).toArray());
}

QJsonObject JsonParserClass::addToJsonOptimizeObject(TypesOfOptimizeVar *types)
{
    QJsonObject optimize_json;
    optimize_json[s_type] = types->type;
    optimize_json[s_cons] = types->cons;
    optimize_json[s_cont_min] = types->cont_min;
    optimize_json[s_cont_max] = types->cont_max;
    optimize_json[s_is_golden_section] = types->is_golden_section;
    optimize_json[s_av] = types->av;
    optimize_json[s_av_i] = types->av_i;
    optimize_json[s_iv] = types->iv;
    optimize_json[s_iv_i] = types->iv_i;


    QJsonArray json_arr;
    foreach (auto e_arr, types->desc_not_gs)
    {
        json_arr.append(e_arr);
    }

    optimize_json[s_desc_not_gs] = json_arr;


    return optimize_json;
}

void JsonParserClass::loadFromJsonOptimizeObject(TypesOfOptimizeVar *types, QJsonObject object)
{
    types->type = object[s_type].toInt();
    types->cons = object[s_cons].toDouble();
    types->cont_min = object[s_cont_min].toDouble();
    types->cont_max = object[s_cont_max].toDouble();
    types->is_golden_section = object[s_is_golden_section].toBool();
    types->av = object[s_av].toDouble();
    types->av_i = object[s_av_i].toDouble();
    types->iv = object[s_iv].toDouble();
    types->iv_i = object[s_iv_i].toDouble();

    QJsonArray object_arr = object[s_desc_not_gs].toArray();
    types->desc_not_gs.clear();
    foreach (auto e_arr, object_arr)
    {
        types->desc_not_gs.push_back(e_arr.toDouble());
    }
}
