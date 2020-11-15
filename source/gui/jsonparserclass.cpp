#include "jsonparserclass.h"

JsonParserClass::JsonParserClass(QWidget *parent, SMainClass *m)
{
    this->parent = parent;
    this->m = m;
}

void JsonParserClass::saveToFile(SMainClass *m)
{
    Q_UNUSED(m)
}

void JsonParserClass::saveGeneralData()
{
    QJsonObject jsonobj;
    general = m->general;

    QJsonObject json_main;
    QJsonObject json_general_calc_data;
    QJsonObject json_general_user_data;
    json_general_user_data["project_name"] = QString::fromStdString(general->project_name);
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

    json_main["user"] = json_general_user_data;
    json_main["calc"] = json_general_calc_data;

    jsonobj["General Data"] = json_main;

    // С помощью диалогового окна получаем имя файла с абсолютным путём
#ifdef Q_OS_LINUX
    QString saveFileName = QFileDialog::getSaveFileName(parent,
                                                        QObject::tr("Save Json File"),
                                                        QString::fromStdString(general->project_name),
                                                        QObject::tr("*.json")) + ".json";
#else
    QString saveFileName = QFileDialog::getSaveFileName(parent,
                                                        QObject::tr("Save Json File"),
                                                        QString::fromStdString(general->project_name),
                                                        QObject::tr("*.json"));
#endif

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
    jsonFile.write(QJsonDocument(jsonobj).toJson(QJsonDocument::Indented));
    jsonFile.close();
}
