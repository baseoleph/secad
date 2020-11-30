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
    json_general_user_data["project_name"] = general->project_name;
    json_general_user_data["length"] = general->length;
    json_general_user_data["wind_pressure"] = general->wind_pressure;
    json_general_user_data["wha"] = general->wha;
    json_general_user_data["length"] = general->length;
    json_general_user_data["beam"] = general->beam;
    json_general_user_data["draft"] = general->draft;
    json_general_user_data["height"] = general->height;
    json_general_user_data["cb"] = general->cb;
    json_general_user_data["csd"] = general->csd;
    json_general_user_data["gm"] = general->gm;
    json_general_user_data["sef_mea"] = general->sef_mea;
    json_general_user_data["sef_mro"] = general->sef_mro;
    json_general_user_data["sef_apra"] = general->sef_apra;

    json_general_calc_data["visibility_zone"] = general->visibility_zone;
    json_general_calc_data["freeboard"] = general->freeboard;
    json_general_calc_data["sef_ma"] = general->sef_ma;
    json_general_calc_data["sef_mo"] = general->sef_mo;
    json_general_calc_data["sef_apa"] = general->sef_apa;

    QJsonArray json_ar_gsl;
    foreach (auto e, general->gsl)
    {
        json_ar_gsl.append(e);
    }
    json_general_calc_data["gsl"] = json_ar_gsl;

    QJsonArray json_ar_gsh;
    foreach (auto e, general->gsh)
    {
        json_ar_gsh.append(e);
    }
    json_general_calc_data["gsh"] = json_ar_gsh;

    QJsonArray json_ar_sef_coef;
    foreach (auto e, general->sef_coef)
    {
        json_ar_sef_coef.append(e);
    }
    json_general_calc_data["sef_coef"] = json_ar_sef_coef;

    json_main_general["user"] = json_general_user_data;
    json_main_general["calc"] = json_general_calc_data;

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
            json_block["titleblock"] = e->titleblock;
            json_block["habitability"] = e->habitability;
            json_block["pap"] = e->pap;
            json_block["foremast"] = e->foremast;
            json_block["mainmast"] = e->mainmast;
            json_block["funnel"] = e->funnel;
            json_block["wheelhause"] = e->wheelhause;
            json_block["l_hb_l"] = e->l_hb_l;
            json_block["bb_l"] = e->bb_l;
            json_block["bb_u"] = e->bb_u;
            json_block["h"] = e->h;
            json_block["s"] = e->s;
            json_block["m_a"] = e->m_a;
            json_block["m_b"] = e->m_b;
            json_block["x_g"] = e->x_g;
            json_block["z_g"] = e->z_g;
            json_block["uxa"] = e->uxa;
            json_block["uxf"] = e->uxf;
            json_block["hb_h"] = e->hb_h;
            json_block["hb_l"] = e->hb_l;
            json_block["sb_h"] = e->sb_h;
            json_block["sb_l"] = e->sb_l;
            json_block["is_hull"] = e->is_hull;

            json_block["lrc"] = addToJsonOptimizeObject(&e->lrc);
            json_block["hrc"] = addToJsonOptimizeObject(&e->hrc);
            json_block["fwih"] = addToJsonOptimizeObject(&e->fwih);
            json_block["awih"] = addToJsonOptimizeObject(&e->awih);
            json_block["x"] = addToJsonOptimizeObject(&e->x);
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
    QJsonObject general_obj = general_json.value("user").toObject();

    m->general->project_name = general_obj.value("project_name").toString();
    m->general->wind_pressure = general_obj.value("wind_pressure").toDouble();
    m->general->wha = general_obj.value("wha").toDouble();
    m->general->length = general_obj.value("length").toDouble();
    m->general->beam = general_obj.value("beam").toDouble();
    m->general->draft = general_obj.value("draft").toDouble();
    m->general->height = general_obj.value("height").toDouble();
    m->general->cb = general_obj.value("cb").toDouble();
    m->general->csd = general_obj.value("csd").toDouble();
    m->general->gm = general_obj.value("gm").toDouble();
    m->general->sef_mea = general_obj.value("sef_mea").toDouble();
    m->general->sef_mro = general_obj.value("sef_mro").toDouble();
    m->general->sef_apra = general_obj.value("sef_apra").toDouble();

    general_obj = general_json.value("calc").toObject();

    m->general->visibility_zone = general_obj.value("visibility_zone").toDouble();
    m->general->freeboard = general_obj.value("freeboard").toDouble();
    m->general->sef_ma = general_obj.value("sef_ma").toDouble();
    m->general->sef_mo = general_obj.value("sef_mo").toDouble();
    m->general->sef_apa = general_obj.value("sef_apa").toDouble();

    QJsonArray json_gsl = general_obj.value("gsl").toArray();
    m->general->gsl.clear();
    foreach (auto e, json_gsl)
    {
        m->general->gsl.push_back(e.toDouble());
    }
    QJsonArray json_gsh = general_obj.value("gsh").toArray();
    m->general->gsh.clear();
    foreach (auto e, json_gsh)
    {
        m->general->gsh.push_back(e.toDouble());
    }

    QJsonArray json_sef_coef = general_obj.value("sef_coef").toArray();
    m->general->sef_coef.clear();
    foreach (auto e, json_sef_coef)
    {
        m->general->sef_coef.push_back(e.toDouble());
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
        block_data->titleblock = e.toObject()["titleblock"].toString();
        block_data->habitability = e.toObject()["habitability"].toBool();
        block_data->pap = e.toObject()["pap"].toBool();
        block_data->foremast = e.toObject()["foremast"].toBool();
        block_data->mainmast = e.toObject()["mainmast"].toBool();
        block_data->funnel = e.toObject()["funnel"].toBool();
        block_data->wheelhause = e.toObject()["wheelhause"].toBool();
        block_data->l_hb_l = e.toObject()["l_hb_l"].toDouble();
        block_data->bb_l = e.toObject()["bb_l"].toDouble();
        block_data->bb_u = e.toObject()["bb_u"].toDouble();
        block_data->h = e.toObject()["h"].toDouble();
        block_data->s = e.toObject()["s"].toDouble();
        block_data->m_a = e.toObject()["m_a"].toDouble();
        block_data->m_b = e.toObject()["m_b"].toDouble();
        block_data->x_g = e.toObject()["x_g"].toDouble();
        block_data->z_g = e.toObject()["z_g"].toDouble();
        block_data->uxa = e.toObject()["uxa"].toDouble();
        block_data->uxf = e.toObject()["uxf"].toDouble();
        block_data->hb_h = e.toObject()["hb_h"].toInt();
        block_data->hb_l = e.toObject()["hb_l"].toInt();
        block_data->sb_h = e.toObject()["sb_h"].toString();
        block_data->sb_l = e.toObject()["sb_l"].toString();
        block_data->is_hull = e.toObject()["is_hull"].toBool();

        loadFromJsonOptimizeObject(&block_data->lrc, e.toObject()["lrc"].toObject());
        loadFromJsonOptimizeObject(&block_data->hrc, e.toObject()["hrc"].toObject());
        loadFromJsonOptimizeObject(&block_data->fwih, e.toObject()["fwih"].toObject());
        loadFromJsonOptimizeObject(&block_data->awih, e.toObject()["awih"].toObject());
        loadFromJsonOptimizeObject(&block_data->x, e.toObject()["x"].toObject());
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

QJsonObject JsonParserClass::addToJsonOptimizeObject(types_of_optimize_var *types)
{
    QJsonObject optimize_json;
    optimize_json["type"] = types->type;
    optimize_json["cons"] = types->cons;
    optimize_json["cont_min"] = types->cont_min;
    optimize_json["cont_max"] = types->cont_max;
    optimize_json["is_golden_section"] = types->is_golden_section;
    optimize_json["av"] = types->av;
    optimize_json["iv"] = types->iv;

    QJsonArray json_arr;
    foreach (auto e_arr, types->desc_not_gs)
    {
        json_arr.append(e_arr);
    }

    optimize_json["desc_not_gs"] = json_arr;

    return optimize_json;
}

void JsonParserClass::loadFromJsonOptimizeObject(types_of_optimize_var *types, QJsonObject object)
{
    types->type = object["type"].toInt();
    types->cons = object["cons"].toDouble();
    types->cont_min = object["cont_min"].toDouble();
    types->cont_max = object["cont_max"].toDouble();
    types->is_golden_section = object["is_golden_section"].toBool();
    types->av = object["av"].toDouble();
    types->iv = object["iv"].toDouble();

    QJsonArray object_arr = object["desc_not_gs"].toArray();
    types->desc_not_gs.clear();
    foreach (auto e_arr, object_arr)
    {
        types->desc_not_gs.push_back(e_arr.toDouble());
    }
}
