#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ListItem.h>
#include <QListWidgetItem>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setStyleSheet(
        "QListWidget{"
        "   background-color: #23262e;"
        "   border: 1px;"
        "}"
        "QScrollBar:vertical {"
        "   border: none;"
        "   background: #0e141b;"
        "   width: 10px;"
        "   margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #606774;" // Цвет фона вертикальной полосы прокрутки
        "    width: 10px;" // Ширина вертикальной полосы прокрутки
        "}"
        "QLabel{"
        "   color: #d7d9da;"
        "}"
        );
    setupList();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupList()
{
    QString path = QCoreApplication::applicationDirPath() + "/source.json";
    QVector<QVector<QString>> data_vector = ListItem::LoadJsonData(path);

    for(int i = 0; i < data_vector.length();i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ListItem *listitem = new ListItem();
        listitem->SetItem(data_vector[i][0], data_vector[i][1]);
        item->setSizeHint(listitem->sizeHint());
        ui->listWidget->setItemWidget(item, listitem);
    }
}
