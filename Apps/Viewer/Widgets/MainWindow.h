#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace ads {
class CDockManager;
class CDockAreaWidget;
class CDockWidget;
}   // namespace ads

class QStackedWidget;
class ProjectWidget;
class HW01;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow*       ui;
    ads::CDockManager*    m_dockManager;
    ads::CDockAreaWidget* m_statusDockArea;
    ads::CDockWidget*     m_timelineDockWidget;
    QStackedWidget*       m_stackedWidget;
    HW01*                 m_HW01;
    ProjectWidget*        m_projectWidget;
};

#endif   // MAINWINDOW_H
