#pragma once
#include "qcustomplot.h"
#include <Eigen/Dense>
#include <QWidget>
#include <vector>

class HW01 : public QCustomPlot
{
    Q_OBJECT
public:
    explicit HW01(QWidget* parent = nullptr);
    ~HW01();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    Eigen::VectorXd    powerBasisFitting(const std::vector<float>& xValues,
                                         const std::vector<float>& yValues, int degree);
    std::vector<float> m_xValues;
    std::vector<float> m_yValues;
};