#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    changeCurrentDir();

    m = new SMainClass();
    jpc = JsonParserClass(this, m);

    proj_man = new ProjectManager(this, m);
    gen_data = new GeneralData(this, m);
    ent_blocks = new EnteringBlocks(this, m);

    ui->tabWidget->addTab(proj_man, "Project Manager");
    ui->tabWidget->addTab(gen_data, "General Data");
    ui->tabWidget->addTab(ent_blocks, "Entering Data");
    ui->tabWidget->addTab(new RenamedForm(this), "Form 4");

    connect(proj_man, &ProjectManager::signalOpenProject,
            this, &MainWindow::slotOpenProject);
    connect(gen_data, &GeneralData::signalSaveGeneralData,
            this, &MainWindow::slotSaveGeneralData);
}


MainWindow::~MainWindow()
{
    delete m;
    delete proj_man;
    delete gen_data;
    delete ent_blocks;
    delete ui;
}

void MainWindow::changeCurrentDir()
{
    if (not QDir(dir_to_projects).exists())
    {
        QDir().mkdir(dir_to_projects);
    }
    QDir::setCurrent(QDir::currentPath() + "/" + dir_to_projects);
}

void MainWindow::slotOpenProject(QString proj_name)
{
    if (proj_name != "")
    {
        fillGeneralData(proj_name);
        gen_data->fillForms();
    }
    else
    {
        m->restoreSGeneralData();
        gen_data->unFillForms();
    }
    ui->tabWidget->setCurrentWidget(gen_data);
}

void MainWindow::slotSaveGeneralData()
{
    jpc.saveGeneralData();
}

void MainWindow::fillGeneralData(QString proj_name)
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
        QJsonValue general_from_json = json.value("General Data");
        QJsonObject general_obj = general_from_json.toObject().value("user").toObject();
        m->general->project_name = general_obj.value("project_name").toString().toStdString();
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

        general_obj = general_from_json.toObject().value("calc").toObject();

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

