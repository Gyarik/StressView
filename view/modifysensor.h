#ifndef MODIFYSENSOR_H
#define MODIFYSENSOR_H
#include <QDialog>
#include <QRegularExpressionValidator>
#include "../model/genericsensor.h"
#include "../view/errorwindow.h"

namespace Ui
{
    class ModifySensor;
}

class ModifySensor : public QDialog
{
    Q_OBJECT

private:
    Ui::ModifySensor *ui;
    GenericSensor *sensor;

public:
    explicit ModifySensor(GenericSensor *sen, QWidget *parent = nullptr);
    ~ModifySensor();
    string getName() const;

private slots:
    void on_CancelButton_clicked();
    void on_ConfirmButton_clicked();

public slots:
    void onCanEdit();

signals:
    void changeSensor();
    void refreshInfo(GenericSensor *, const string &);
};

#endif
