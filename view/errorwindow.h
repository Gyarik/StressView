#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QDialog>

namespace Ui
{
    class ErrorWindow;
}

class ErrorWindow : public QDialog
{
    Q_OBJECT

private:
    Ui::ErrorWindow *ui;

public:
    explicit ErrorWindow(QString msg = "error", QWidget *parent = nullptr);
    ~ErrorWindow();
private slots:
    void on_ErrorConfirm_clicked();
};

#endif // ERRORWINDOW_H
