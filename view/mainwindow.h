#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSplitter>
#include "../model/sensorcontainer.h"
#include "../view/sensorlistwidget.h"

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
};

#endif
