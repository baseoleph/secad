#include "projectmanager.h"
#include "ui_projectmanager.h"

ProjectManager::ProjectManager(QWidget *parent, SMainClass *m) :
    QWidget(parent),
    ui(new Ui::ProjectManager)
{
    ui->setupUi(this);
    general = m->general;

    loadJsonFromFile();
}

ProjectManager::~ProjectManager()
{
    delete ui;
}

void ProjectManager::loadJsonFromFile()
{
    // Выбираем файл
        QString openFileName = QFileDialog::getOpenFileName(this,
                                                            tr("Open Json File"),
                                                            QString(),
                                                            tr("JSON (*.json)"));
        QFileInfo fileInfo(openFileName);   // С помощью QFileInfo
        QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл
        // Создаём объект файла и открываем его на чтение
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
        general->project_name = general_obj.value("project_name").toString().toStdString();
        general->wind_pressure = general_obj.value("wind_pressure").toDouble();
        general->wha = general_obj.value("wha").toDouble();
        general->length = general_obj.value("length").toDouble();
        general->deam = general_obj.value("deam").toDouble();
        general->depths = general_obj.value("depths").toDouble();
        general->height = general_obj.value("height").toDouble();
        general->cb = general_obj.value("cb").toDouble();
        general->csd = general_obj.value("csd").toDouble();
        general->gm = general_obj.value("gm").toDouble();
        general->sef_mea = general_obj.value("sef_mea").toDouble();
        general->sef_mro = general_obj.value("sef_mro").toDouble();
        general->sef_apra = general_obj.value("sef_apra").toDouble();
        general->visibility_zone = general_obj.value("visibility_zone").toDouble();
        general->freeboard = general_obj.value("freeboard").toDouble();
        general->sef_ma = general_obj.value("sef_ma").toDouble();
        general->sef_mo = general_obj.value("sef_mo").toDouble();
        general->sef_apa = general_obj.value("sef_apa").toDouble();

    // Золотое сечение по длине
    // Golden Section by Leight
    // proportions
        general->wind_pressure = general_obj.value("wind_pressure").toDouble();
    d_vector gsl;

    // Золотое сечение по высоте
    // Golden Section by Height
    // proportions
        general->wind_pressure = general_obj.value("wind_pressure").toDouble();
    d_vector gsh;


    // Коэффициенты в фукнции полинома
    // SEF coefficients
    // coefficients
        general->wind_pressure = general_obj.value("wind_pressure").toDouble();
    d_vector sef_coef;
}
