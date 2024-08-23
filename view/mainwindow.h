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
#include "../view/modifysensor.h"

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
    ModifySensor *editWidget;
    QSplitter *vertSplit;
    QSplitter *horSplit;
    bool isSplitterGood = false;
    int threshold = 180;
    string prevName;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void newButton();

signals:
    void canEdit();

private slots:
    void printInfo(GenericSensor *);
    void onTryNew();
    void onNewAddable(GenericSensor *);
    void onRemovedSensor();
    void onClearedList();
    void onEditSensor();
    //void onClearSensor();
    void onChangeSensor();
    void onRefreshInfo(const GenericSensor *, const string &);
};

#endif
