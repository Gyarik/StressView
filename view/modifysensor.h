#ifndef MODIFYSENSOR_H
#define MODIFYSENSOR_H

#include <QDialog>

namespace Ui {
class ModifySensor;
}

class ModifySensor : public QDialog
{
    Q_OBJECT

public:
    explicit ModifySensor(QWidget *parent = nullptr);
    ~ModifySensor();

private:
    Ui::ModifySensor *ui;
};

#endif // MODIFYSENSOR_H
