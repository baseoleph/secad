#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QFile>
#include <QDir>

#include "../core/smainclass.h"
namespace Ui {
class ProjectManager;
}

class ProjectManager : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectManager(QWidget *parent = nullptr, SMainClass *m = nullptr);
    ~ProjectManager();

private:
    Ui::ProjectManager *ui;
    SGeneralData *general;

    void loadJsonFromFile();
};

#endif // PROJECTMANAGER_H
