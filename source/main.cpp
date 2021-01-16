// Ship Exterior CAD
// Copyright (C) 2020 baseoleph@gmail.com,
//					  github.com/RoninHikami

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "gui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

////     Устанавливаем файл логирования,
////     внимательно сверьтесь с тем, какой используете путь для файла
//    m_logFile.reset(new QFile("logFile.txt"));
//    // Открываем файл логирования
//    m_logFile.data()->open(QFile::Append | QFile::Text);
//    // Устанавливаем обработчик
//    qInstallMessageHandler(messageHandler);
    MainWindow w;
    w.show();

    return a.exec();
}

//// Реализация обработчика
//void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    Q_UNUSED(type)
//    if (QString(context.category) == "info")
//    {
//        // Открываем поток записи в файл
//        QTextStream out(m_logFile.data());
//        // Записываем дату записи
//        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
//        // Записываем в вывод категорию сообщения и само сообщение
//        out << ": " << msg << Qt::endl;
//        out.flush();    // Очищаем буферизированные данные
//    }
//    else
//    {
//        qDebug() << msg;
//    }
//}
