#include "HW01.h"

HW01::HW01(QWidget* parent)
    : QCustomPlot(parent)
{
    // generate some data:
    QVector<double> x(101), y(101);   // initialize with entries 0..100
    for (int i = 0; i < 101; ++i) {
        x[i] = i / 50.0 - 1;          // x goes from -1 to 1
        y[i] = x[i] * x[i];           // let's plot a quadratic function
    }
    // create graph and assign data to it:
    this->addGraph();
    this->graph(0)->setData(x, y);
    // give the axes some labels:
    this->xAxis->setLabel("x");
    this->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    this->xAxis->setRange(-1, 1);
    this->yAxis->setRange(0, 1);
    this->replot();
}

HW01::~HW01() {}

void HW01::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        // ��ȡ�����λ�õ�����
        double x     = xAxis->pixelToCoord(event->pos().x());
        double y     = yAxis->pixelToCoord(event->pos().y());
        auto   point = this->addGraph();
        point->addData(x, y);
        point->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 8));
        // �����ﴦ��ѡ�����߼�
        // ��������������Ӵ�������¼��ʹ��ѡ���ĵ�����
        this->replot();
    }

    // ������¼����ݸ����ദ��
    QCustomPlot::mousePressEvent(event);
}
