#ifndef GENERALDATA_H
#define GENERALDATA_H

#include <QWidget>

namespace Ui {
class GeneralData;
}

class GeneralData : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralData(QWidget *parent = nullptr);
    ~GeneralData();

private:
    Ui::GeneralData *ui;
};

#endif // FORM3_H
