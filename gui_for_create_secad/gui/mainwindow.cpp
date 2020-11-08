#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (not QDir("projects").exists())
    {
        QDir().mkdir("projects");
    }
    QDir::setCurrent(QDir::currentPath() + "/projects");

    m = new SMainClass();

    proj_man = new ProjectManager(this, m);
    gen_data = new GeneralData(this, m);
    ent_blocks = new EnteringBlocks(this, m);

    ui->tabWidget->addTab(proj_man, "Project Manager");
    ui->tabWidget->addTab(gen_data, "General Data");
    ui->tabWidget->addTab(ent_blocks, "Entering Data");
    ui->tabWidget->addTab(new RenamedForm(this), "Form 4");

    connect(proj_man, &ProjectManager::signalOpenProject,
            this, &MainWindow::slotOpenProject);
}

MainWindow::~MainWindow()
{
    delete m;
    delete proj_man;
    delete gen_data;
    delete ent_blocks;
    delete ui;
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
        QJsonObject general_obj = general_from_json.toObject();
        m->general->project_name = general_obj.value("project_name").toString().toStdString();
        m->general->wind_pressure = general_obj.value("wind_pressure").toDouble();
        m->general->wha = general_obj.value("wha").toDouble();
        m->general->length = general_obj.value("length").toDouble();
        m->general->deam = general_obj.value("deam").toDouble();
        m->general->depths = general_obj.value("depths").toDouble();
        m->general->height = general_obj.value("height").toDouble();
        m->general->cb = general_obj.value("cb").toDouble();
        m->general->csd = general_obj.value("csd").toDouble();
        m->general->gm = general_obj.value("gm").toDouble();
        m->general->sef_mea = general_obj.value("sef_mea").toDouble();
        m->general->sef_mro = general_obj.value("sef_mro").toDouble();
        m->general->sef_apra = general_obj.value("sef_apra").toDouble();
        m->general->visibility_zone = general_obj.value("visibility_zone").toDouble();
        m->general->freeboard = general_obj.value("freeboard").toDouble();
        m->general->sef_ma = general_obj.value("sef_ma").toDouble();
        m->general->sef_mo = general_obj.value("sef_mo").toDouble();
        m->general->sef_apa = general_obj.value("sef_apa").toDouble();

    // Золотое сечение по длине
    // Golden Section by Leight
    // proportions
        m->general->wind_pressure = general_obj.value("wind_pressure").toDouble();
    d_vector gsl;

    // Золотое сечение по высоте
    // Golden Section by Height
    // proportions
        m->general->wind_pressure = general_obj.value("wind_pressure").toDouble();
    d_vector gsh;


    // Коэффициенты в фукнции полинома
    // SEF coefficients
    // coefficients
        m->general->wind_pressure = general_obj.value("wind_pressure").toDouble();
        d_vector sef_coef;
}

