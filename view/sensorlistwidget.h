#ifndef SENSORLISTWIDGET_H
#define SENSORLISTWIDGET_H
#include <QWidget>
#include <QPushButton>
#include <vector>
#include "../model/genericsensor.h"
#include "../visitor/genericvisitor.h"

using std::vector;

namespace Ui
{
    class SensorListWidget;
}

class SensorListWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::SensorListWidget *ui;
    static vector<QPushButton *> buttons;


public:
    explicit SensorListWidget(QWidget *parent = nullptr);
    ~SensorListWidget();
};

#endif
