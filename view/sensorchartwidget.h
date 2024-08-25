#ifndef SENSORCHARTWIDGET_H
#define SENSORCHARTWIDGET_H
#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include "../model/genericsensor.h"
#include "../visitor/visitor.h"

namespace Ui
{
    class SensorChartWidget;
}

class SensorChartWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::SensorChartWidget *ui;
    QChartView *chart;

public:
    explicit SensorChartWidget(QWidget *parent = nullptr);
    ~SensorChartWidget();
    void showChart(const GenericSensor *);
    void resetChart();
};

#endif
