#include "MainWindow.h"
#include "HW01.h"
#include "ui_MainWindow.h"
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_show()));
}

void MainWindow::slot_show() {}


MainWindow::~MainWindow()
{
    delete ui;
}
