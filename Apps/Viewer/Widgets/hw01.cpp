#include "HW01.h"
#include <iostream>
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
        double x = xAxis->pixelToCoord(event->pos().x());
        double y = yAxis->pixelToCoord(event->pos().y());
        m_xValues.push_back(x);
        m_yValues.push_back(y);
        auto point = this->addGraph();
        point->addData(x, y);
        point->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 8));
        auto c = powerBasisFitting(m_xValues, m_yValues);
        // generate some data:
        QVector<double> xs(101), ys(101);   // initialize with entries 0..100
        for (int i = 0; i < 101; ++i) {
            xs[i] = i / 50.0 - 1;           // x goes from -1 to 1
            for (size_t j = 0; j < c.size(); j++) {
                ys[i] += c[j] * std::pow(xs[i], j);
            }
        }
        this->graph(0)->setData(xs, ys);
        this->replot();
    }
    QCustomPlot::mousePressEvent(event);
}

Eigen::VectorXd HW01::powerBasisFitting(const std::vector<float>& xValues,
                                        const std::vector<float>& yValues)
{
    int numPoints = xValues.size();
    if (numPoints <= 1) {
        return Eigen::VectorXd();
    }
    // 构建矩阵A和向量b
    Eigen::MatrixXd A(numPoints, numPoints);
    Eigen::VectorXd b(numPoints);

    for (int i = 0; i < numPoints; i++) {
        double x = xValues[i];
        b(i)     = yValues[i];

        for (int j = 0; j < numPoints; j++) {
            A(i, j) = std::pow(x, j);
        }
    }
    auto inverse = A.inverse();
    // 使用最小二乘法求解系数向量c
    Eigen::VectorXd c = inverse * b;

    // 输出拟合结果
    std::cout << "Fitted coefficients (from c0 to cn): ";
    for (int i = 0; i < numPoints; i++) {
        std::cout << c(i) << " ";
    }
    std::cout << std::endl;
    return c;
}
