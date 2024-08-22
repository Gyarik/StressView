#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSplitter>
#include "../model/sensorcontainer.h"
#include "../visitor/visitor.h"
#include "../view/sensorlistwidget.h"
#include "../view/addsensor.h"
#include "../view/errorwindow.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    static SensorContainer *list;
    static Visitor *visitor;
    SensorListWidget *listWidget;
    QSplitter *hor;
    QSplitter *vert;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void newButton();

private slots:
    void printInfo(GenericSensor *);
    void onTryNew();
    void onInfoExists(GenericSensor *);
};

#endif
