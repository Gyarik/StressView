#include "errorwindow.h"
#include "ui_errorwindow.h"

ErrorWindow::ErrorWindow(QString msg, QWidget *parent)
    : QDialog(parent), ui(new Ui::ErrorWindow)
{
    ui->setupUi(this);
    ui->ErrorLabel->setText(msg);
    this->setWindowTitle(QString::fromStdString("Error"));
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

ErrorWindow::~ErrorWindow()
{
    delete ui;
}

void ErrorWindow::on_ErrorConfirm_clicked()
{
    close();
}

