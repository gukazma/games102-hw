#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"
#include <QDebug>
#include <QFile>
#include <QTreeWidgetItem>
#include <QXmlStreamReader>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
ProjectWidget::ProjectWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ProjectWidget)
{
    ui->setupUi(this);
    slot_update();
}
void ProjectWidget::slot_update()
{
    ui->treeWidget->setHeaderHidden(true);
    ui->treeWidget->setIndentation(15);
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(ui->treeWidget);
    rootItem->setText(0, "Root");
    QFile file(":/Project.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QByteArray data = file.readAll();
    QString    xmlData(data);
    file.close();
    boost::property_tree::ptree pt;
    std::istringstream          iss(xmlData.toStdString());
    boost::property_tree::read_xml(iss, pt);
    auto homeworks = pt.get_child("homeworks");
    // ±éÀúÔªËØ
    for (auto&& hw : homeworks) {
        std::cout << hw.first << std::endl;
        auto&&           title = hw.second.get_child("title");
        QTreeWidgetItem* item1 = new QTreeWidgetItem(rootItem);
        item1->setText(0, title.data().c_str());
        rootItem->addChild(item1);
    }
    ui->treeWidget->expandItem(rootItem);
}

ProjectWidget::~ProjectWidget()
{
    delete ui;
}
