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

    void saveToFile(SMainClass *m);
    void saveGeneralData();

    QWidget *parent;
    SMainClass *m;
    SGeneralData *general;
    SBlockData *block_data;
};

#endif // JSONPARSERCLASS_H
