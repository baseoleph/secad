#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QWidget>
#include <QDir>
#include <QDebug>

#include "../core/smainclass.h"
#include "../core/loggingcategories.h"

namespace Ui {
class ProjectManager;
}

class ProjectManager : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectManager(QWidget *parent = nullptr, SMainClass *m = nullptr);
    ~ProjectManager();

signals:
    // Отправляет сигнал на открытие проекта из файла или нового
    void signalOpenProject(QString proj_name = "");

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_go_clicked();
    void on_pushButton_create_new_proj_clicked();

private:
    Ui::ProjectManager *ui;
    SGeneralData *general;

    QString project_name;

    // Проверяет наличие готовых проектов *.json
    void checkJsonsInDir();

    // Проверят пустоту combobox
    void checkCombobox();
};

#endif // PROJECTMANAGER_H
