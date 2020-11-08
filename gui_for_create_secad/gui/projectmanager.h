#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QWidget>

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
};

#endif // PROJECTMANAGER_H
