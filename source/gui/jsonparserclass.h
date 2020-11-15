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
    void loadData(QString proj_name);

    QWidget *parent;
    SMainClass *m;
    SGeneralData *general;
    std::vector<SBlockData *> block_data;

private:
    QJsonObject json_main;
};

#endif // JSONPARSERCLASS_H
