#ifndef SENSORINFOWIDGET_H
#define SENSORINFOWIDGET_H
#include <QWidget>
#include <QBoxLayout>

namespace Ui {
class SensorInfoWidget;
}

class SensorInfoWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::SensorInfoWidget *ui;

public:
    explicit SensorInfoWidget(QWidget *parent = nullptr);
    ~SensorInfoWidget();
    void setName(const QString &);
    void setDesc(const QString &);
    void setComponent(const QString &);
    void setBounds(const QString &, const QString &);
    QVBoxLayout *getChart();
    void clearWidget();

signals:
    void beginSim();
    void clearSensor();
    void editSensor();
};

#endif
