#ifndef ADDSENSOR_H
#define ADDSENSOR_H
#include <QDialog>
#include <QRegularExpressionValidator>
#include "../model/genericsensor.h"
#include "../model/cpusensor.h"
#include "../model/gpusensor.h"
#include "../model/ramsensor.h"
#include "../view/errorwindow.h"

namespace Ui
{
    class AddSensor;
}

class AddSensor : public QDialog
{
    Q_OBJECT

private:
    Ui::AddSensor *ui;
    int r_min, r_max, r_tempmin, r_tempmax;
    QString s_maxrange, s_temprange;

public:
    explicit AddSensor(QWidget *parent = nullptr);
    ~AddSensor();
    void setRanges(int, int, int, int);
    bool isInRange() const;

signals:
    void infoExists(GenericSensor *);

private slots:
    void on_CPUButton_toggled(bool checked);
    void on_GPUButton_toggled(bool checked);
    void on_RAMButton_toggled(bool checked);
    void on_NewSensorButton_clicked();
};

#endif
