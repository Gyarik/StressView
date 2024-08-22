#ifndef SENSORINFOWIDGET_H
#define SENSORINFOWIDGET_H

#include <QWidget>

namespace Ui {
class SensorInfoWidget;
}

class SensorInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SensorInfoWidget(QWidget *parent = nullptr);
    ~SensorInfoWidget();

private:
    Ui::SensorInfoWidget *ui;
};

#endif // SENSORINFOWIDGET_H
