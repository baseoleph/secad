#include "gui/mainwindow.h"

#include <QApplication>


// Умный указатель на файл логирования
QScopedPointer<QFile>   m_logFile;

// Объявляение обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем файл логирования,
    // внимательно сверьтесь с тем, какой используете путь для файла
    m_logFile.reset(new QFile("logFile.txt"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);
    MainWindow w;
    w.show();

    return a.exec();
}

// Реализация обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(type)
    if (QString(context.category) == "info")
    {
        // Открываем поток записи в файл
        QTextStream out(m_logFile.data());
        // Записываем дату записи
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
        // Записываем в вывод категорию сообщения и само сообщение
        out << ": " << msg << Qt::endl;
        out.flush();    // Очищаем буферизированные данные
    }
}
