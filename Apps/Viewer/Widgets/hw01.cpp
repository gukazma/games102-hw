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
        this->replot();
        powerBasisFitting(m_yValues, m_yValues, 10);
    }
    QCustomPlot::mousePressEvent(event);
}

Eigen::VectorXd HW01::powerBasisFitting(const std::vector<float>& xValues,
                                        const std::vector<float>& yValues, int degree)
{
    int numPoints = xValues.size();

    if (numPoints < degree + 1) {
        std::cout << "Error: Insufficient number of points for fitting." << std::endl;
        return Eigen::VectorXd();
    }

    // 构建矩阵A和向量b
    Eigen::MatrixXd A(numPoints, degree + 1);
    Eigen::VectorXd b(numPoints);

    for (int i = 0; i < numPoints; i++) {
        double x = xValues[i];
        b(i)     = yValues[i];

        for (int j = 0; j <= degree; j++) {
            A(i, j) = std::pow(x, j);
        }
    }

    // 使用最小二乘法求解系数向量c
    Eigen::VectorXd c = A.fullPivLu().solve(b);

    // 输出拟合结果
    std::cout << "Fitted coefficients (from c0 to cn): ";
    for (int i = 0; i <= degree; i++) {
        std::cout << c(i) << " ";
    }
    std::cout << std::endl;
    return c;
}
