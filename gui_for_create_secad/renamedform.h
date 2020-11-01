#ifndef RENAMEDFORM_H
#define RENAMEDFORM_H

#include <QWidget>

namespace Ui {
class RenamedForm;
}

class RenamedForm : public QWidget
{
    Q_OBJECT

public:
    explicit RenamedForm(QWidget *parent = nullptr);
    ~RenamedForm();

private:
    Ui::RenamedForm *ui;
};

#endif
