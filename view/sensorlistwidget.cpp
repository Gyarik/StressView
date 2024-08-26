#include "sensorlistwidget.h"
#include "ui_sensorlistwidget.h"

vector<QPushButton *> SensorListWidget::buttons;

SensorListWidget::SensorListWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::SensorListWidget)
{
    curSensor = nullptr;
    ui->setupUi(this);
    ui->VLayout->setAlignment(Qt::AlignTop);
    ui->frame->setFrameStyle(QFrame::Box);
    connect(ui->SearchLine, &QLineEdit::textChanged, this, [this]() {searchBtn(ui->SearchLine->text());});
    connect(ui->NewButton, &QPushButton::clicked, this, &SensorListWidget::onNewClicked);
    connect(ui->RemoveButton, &QPushButton::clicked, this, &SensorListWidget::onRemoveClicked);
    connect(ui->ClearButton, &QPushButton::clicked, this, &SensorListWidget::onClearClicked);

    QRegularExpression regexp("[\\p{L}0-9]*");
    QRegularExpressionValidator *valid = new QRegularExpressionValidator(regexp, this);
    ui->SearchLine->setValidator(valid);
    ui->SearchLine->setMaxLength(32);
}

SensorListWidget::~SensorListWidget()
{
    delete ui;
}

void SensorListWidget::setCurrent(GenericSensor *sen)
{
    this->curSensor = sen;
    emit curSensorChange();
}

GenericSensor *SensorListWidget::getCurrent() const
{
    return this->curSensor;
}

void SensorListWidget::newButton(GenericSensor *sen, GenericVisitor *vis)
{
    sen->setupButton(vis);
    QPushButton *ret = vis->getButton();
    connect(ret, &QPushButton::clicked, this, [this, sen]() {emit nameCpy(sen);});
    connect(ret, &QPushButton::clicked, this, [this, sen]() {setCurrent(sen);});
    buttons.push_back(ret);
    ui->VLayout->addWidget(ret);
}

void SensorListWidget::changeButton(const string &curName, const string &prevName)
{
    for(auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        if((*it)->objectName().remove("&").toStdString() == prevName)
        {
            (*it)->setObjectName(QString::fromStdString(curName));
            delete (*it)->layout()->itemAt(0)->widget();
            QLabel *txt = new QLabel(QString::fromStdString(curName));
            txt->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            (*it)->layout()->addWidget(txt);
            return;
        }
    }
}

void SensorListWidget::fileClearList()
{
    for(auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete *it;
    }
    buttons.clear();

    emit clearedList();
}

// Slots

void SensorListWidget::searchBtn(const QString &s)
{
    if(s.isEmpty())
    {
        for(auto it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->show();
    }
    else
    {
        for(auto it = buttons.begin(); it != buttons.end(); ++it)
        {
            if(!(*it)->objectName().contains(s, Qt::CaseInsensitive))
                (*it)->hide();
            else
                (*it)->show();
        }
    }
}

void SensorListWidget::onNewClicked()
{
    emit tryNew();
}

void SensorListWidget::onRemoveClicked()
{
    if(curSensor != nullptr)
    {
        for(auto it = buttons.begin(); it != buttons.end(); ++it)
        {
            if((*it)->objectName().toStdString() == curSensor->getName())
            {
                ui->VLayout->removeWidget(*it);
                delete *it;
                buttons.erase(it);
                break;
            }
        }

        SensorContainer::removeSensor(curSensor);
        curSensor = nullptr;
        emit removedSensor();
    }
}

void SensorListWidget::onClearClicked()
{
    QMessageBox::StandardButton confirm;

    confirm = QMessageBox::question(this, "Clear", "Are you sure you want to clear the sensor list?",
                                    QMessageBox::Yes | QMessageBox::No);
    if(confirm == QMessageBox::Yes)
    {
        for(auto it = buttons.begin(); it != buttons.end(); ++it)
            delete *it;
        buttons.clear();
        emit clearedList();
    }
}
