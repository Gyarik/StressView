#include "sensorchartwidget.h"
#include "ui_sensorchartwidget.h"

SensorChartWidget::SensorChartWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::SensorChartWidget)
{
    ui->setupUi(this);
    ui->frame->setFrameStyle(QFrame::Box);
    chart = new QChartView();
    this->showChart(nullptr);
    ui->chartLayout->addWidget(chart);
    chart->setRenderHint(QPainter::Antialiasing);
}

SensorChartWidget::~SensorChartWidget()
{
    delete ui;
}

void SensorChartWidget::showChart(const GenericSensor *sensor)
{
    chart->chart()->removeAllSeries();
    while(!chart->chart()->axes().isEmpty())
    {
        chart->chart()->removeAxis(chart->chart()->axes().takeFirst());
    }

    chart->chart()->setTitle(QString::fromStdString("Performance"));
    chart->chart()->legend()->hide();

    Visitor *visitor = new Visitor();

    if(sensor != nullptr)
    {
        QLineSeries *s = new QLineSeries();
        s->setPen(QPen(Qt::black, 2));
        s->setPointsVisible(true);
        s->setPointLabelsFormat("DROP");
        s->setPointLabelsColor(QColor(Qt::red));
        QHash<QXYSeries::PointConfiguration, QVariant> confBad;
        confBad[QXYSeries::PointConfiguration::Color] = QColor(Qt::red);
        confBad[QXYSeries::PointConfiguration::LabelVisibility] = true;
        QHash<QXYSeries::PointConfiguration, QVariant> confGood;
        confGood[QXYSeries::PointConfiguration::Color] = QColor(Qt::green);
        confGood[QXYSeries::PointConfiguration::LabelVisibility] = false;

        sensor->accept(visitor);
        QString unit = QString::fromStdString(visitor->getChartUnit());
        for(int i = 0; i < sensor->getCount(); ++i)
        {
            qDebug() << sensor->getData(i).isBad();
            s->append(sensor->getData(i).getTime(), sensor->getData(i).getVal());
            if(sensor->getData(i).isBad())
                s->setPointConfiguration(i, confBad);
            else
                s->setPointConfiguration(i, confGood);
        }

        auto X = new QValueAxis;
        X->setTickCount(21);
        X->setTitleText("(seconds)");
        X->setLabelFormat("%i");
        chart->chart()->addAxis(X, Qt::AlignBottom);
        chart->chart()->addSeries(s);
        X->setLinePenColor(Qt::black);

        auto Y = new QValueAxis;
        Y->setTitleText("(" + unit + ")");
        Y->setRange(0, sensor->getMax());
        Y->setLabelFormat("%i");
        Y->setLinePenColor(s->pen().color());
        chart->chart()->addAxis(Y, Qt::AlignLeft);
        Y->setLinePenColor(Qt::black);

        s->attachAxis(X);
        s->attachAxis(Y);
    }

    delete visitor;
}
