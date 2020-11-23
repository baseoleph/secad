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

    QJsonObject addToJsonOptimizeObject(types_of_optimize_var* types);
    QWidget *parent;

    SMainClass *m;
    SGeneralData *general;
    std::vector<SBlockData *> blocks;

    void loadFromJsonOptimizeObject(types_of_optimize_var *types, QJsonObject object);
private:
    QJsonObject json_main;

    QString GENERAL = "General";
    QString BLOCKS = "Blocks";
};

#endif // JSONPARSERCLASS_H
