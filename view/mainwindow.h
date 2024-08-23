#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSplitter>
#include "../model/sensorcontainer.h"
#include "../visitor/visitor.h"
#include "../view/sensorlistwidget.h"
#include "../view/addsensor.h"
#include "../view/errorwindow.h"
#include "../view/sensorinfowidget.h"

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
    SensorInfoWidget *infoWidget;
    QSplitter *hor;
    QSplitter *vert;
    bool isSplitterGood = false;
    int threshold = 180;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void newButton();

private slots:
    void printInfo(GenericSensor *);
    void onTryNew();
    void onNewAddable(GenericSensor *);
};

#endif
