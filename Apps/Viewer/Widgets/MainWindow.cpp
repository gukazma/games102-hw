#include "MainWindow.h"
#include "HW01.h"
#include "ui_MainWindow.h"
#include <qt5advanceddocking/AutoHideDockContainer.h>
#include <qt5advanceddocking/DockAreaTitleBar.h>
#include <qt5advanceddocking/DockAreaWidget.h>
#include <qt5advanceddocking/DockManager.h>
#include <qt5advanceddocking/DockWidget.h>

#include "ProjectWidget.h"
#include <QComboBox>
#include <QMainWindow>
#include <QStackedWidget>
#include <QWidgetAction>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::XmlCompressionEnabled, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    ads::CDockManager::setAutoHideConfigFlags(ads::CDockManager::DefaultAutoHideConfig);
    m_dockManager = new ads::CDockManager(this);

    m_stackedWidget                     = new QStackedWidget(this);
    ads::CDockWidget* CentralDockWidget = new ads::CDockWidget("CentralWidget");
    m_HW01                              = new HW01(this);
    m_stackedWidget->addWidget(m_HW01);
    CentralDockWidget->setWidget(m_stackedWidget);
    auto* CentralDockArea = m_dockManager->setCentralWidget(CentralDockWidget);
    CentralDockArea->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

    // create other dock widgets
    m_projectWidget = new ProjectWidget(this);

    ads::CDockWidget* TableDockWidget = new ads::CDockWidget("Project");
    TableDockWidget->setWidget(m_projectWidget);
    TableDockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    TableDockWidget->setMinimumSize(200, 150);
    const auto autoHideContainer =
        m_dockManager->addAutoHideDockWidget(ads::SideBarLocation::SideBarRight, TableDockWidget);
    autoHideContainer->setSize(480);


    /*QTableWidget* propertiesTable = new QTableWidget();
    propertiesTable->setColumnCount(3);
    propertiesTable->setRowCount(10);
    ads::CDockWidget* PropertiesDockWidget = new ads::CDockWidget("Properties");
    PropertiesDockWidget->setWidget(propertiesTable);
    PropertiesDockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidget);
    PropertiesDockWidget->resize(250, 150);
    PropertiesDockWidget->setMinimumSize(200, 150);
    m_dockManager->addDockWidget(
        ads::DockWidgetArea::RightDockWidgetArea, PropertiesDockWidget, CentralDockArea);*/
}


MainWindow::~MainWindow()
{
    delete ui;
}
