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
    // Стили CSS
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

// Сортировка списка по статусу выполнения ачивки
QVector<QVector<QString>> MainWindow::SortList(QVector<QVector<QString>> data_vector)
{
    QVector<QString> temp;
    int last_not_done = -1;
    for(int i = data_vector.length() - 1; i >= 0; i--)
    {
        if(last_not_done == -1)
        {
            if(data_vector[i][2] == "not done")
                last_not_done = i;
            continue;
        }
        if(data_vector[i][2] == "done")
        {
            temp = data_vector[last_not_done];
            data_vector[last_not_done] = data_vector[i];
            data_vector[i] = temp;
            last_not_done = last_not_done - 1;
        }
    }
    return data_vector;
}


// Создание списка
void MainWindow::setupList()
{
    // Подтягиваем данные из Json
    QString path = QCoreApplication::applicationDirPath() + "/source.json";
    QVector<QVector<QString>> data_vector = ListItem::LoadJsonData(path);
    data_vector = SortList(data_vector);

    for(int i = 0; i < data_vector.length();i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        ListItem *listitem = new ListItem();
        listitem->SetItem(data_vector[i][0], data_vector[i][1], data_vector[i][2]);
        item->setSizeHint(listitem->sizeHint());
        ui->listWidget->setItemWidget(item, listitem);
    }
}
