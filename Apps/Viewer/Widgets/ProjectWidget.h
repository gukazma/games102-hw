#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>

namespace Ui {
class ProjectWidget;
}

class ProjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectWidget(QWidget* parent = nullptr);
    ~ProjectWidget();

public slots:
    void slot_update();

private:
    Ui::ProjectWidget* ui;
};

#endif   // PROJECTWIDGET_H
