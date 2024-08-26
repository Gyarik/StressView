#ifndef SENSORLISTWIDGET_H
#define SENSORLISTWIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QLabel>
#include <vector>
#include "../model/genericsensor.h"
#include "../visitor/genericvisitor.h"
#include "../model/sensorcontainer.h"

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
    GenericSensor *curSensor;

public:
    explicit SensorListWidget(QWidget *parent = nullptr);
    ~SensorListWidget();
    void setCurrent(GenericSensor *);
    GenericSensor *getCurrent() const;
    void newButton(GenericSensor *, GenericVisitor *);
    void changeButton(const string &, const string &);
    void fileClearList();

signals:
    void curSensorChange();
    void tryNew();
    void removedSensor();
    void clearedList();
    void nameCpy(GenericSensor *);

private slots:
    void searchBtn(const QString &);
    void onNewClicked();
    void onRemoveClicked();

public slots:
    void onClearClicked();
};

#endif
