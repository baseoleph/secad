#include "projectmanager.h"
#include "ui_projectmanager.h"

ProjectManager::ProjectManager(QWidget *parent, SMainClass *m) :
    QWidget(parent),
    ui(new Ui::ProjectManager)
{
    ui->setupUi(this);
    Q_UNUSED(m)
}

ProjectManager::~ProjectManager()
{
    delete ui;
}
