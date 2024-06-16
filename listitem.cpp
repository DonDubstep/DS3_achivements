#include "listitem.h"

ListItem::ListItem(QWidget *parent)
    : QWidget{parent}
{
}

// Создание элемента списка
void ListItem::SetItem(QString title_str, QString description_str, QString status)
{
    QLabel *title = new QLabel(title_str);
    title->setStyleSheet(
        "font: 16pt;"
        "Segoe UI;"
        );

    QLabel *description = new QLabel(description_str);
    description->setStyleSheet(
        "font: 10pt;"
        "Segoe UI;"
        );
    if(status == "done")
    {
        description->setStyleSheet(
            "font: 10pt;"
            "Segoe UI;"
            "color: red;"
            );
        title->setStyleSheet(
            "font: 16pt;"
            "Segoe UI;"
            "color: red;"
            );
    }
    QCheckBox *checkbox = new QCheckBox();
    QVBoxLayout *textLayout = new QVBoxLayout();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    textLayout->addWidget(title);
    textLayout->addWidget(description);
    mainLayout->addLayout(textLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(checkbox);
    setLayout(mainLayout);
}
