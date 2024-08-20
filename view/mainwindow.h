#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "../model/genericsensor.h"
#include "../model/sensorcontainer.h"

QT_BEGIN_NAMESPACE
namespace View
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:

public:
    explicit MainWindow(QWidget *parent = nullptr);
    GenericSensor *newSensor(const string &, const string &, const string &, int, int) const;

signals:
};

#endif
