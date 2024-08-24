#ifndef SENSORCHARTWIDGET_H
#define SENSORCHARTWIDGET_H

#include <QWidget>

namespace Ui {
class SensorChartWidget;
}

class SensorChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SensorChartWidget(QWidget *parent = nullptr);
    ~SensorChartWidget();

private:
    Ui::SensorChartWidget *ui;
};

#endif // SENSORCHARTWIDGET_H
