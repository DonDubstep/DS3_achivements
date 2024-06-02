#ifndef LISTITEM_H
#define LISTITEM_H

#include <QWidget>
#include <QRect>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QJsonObject>

class ListItem : public QWidget, QRect
{
    Q_OBJECT
public:
    explicit ListItem(QWidget *parent = nullptr);
    void SetItem(QString title_str, QString description_str);

    static QVector<QVector<QString>> LoadJsonData(QString path)
    {
        QVector<QVector<QString>> result;
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning("Couldn't open file.");
            return result;
        }
        QByteArray json_data = file.readAll();
        QJsonDocument document = QJsonDocument::fromJson(json_data);
        QJsonArray jsonarray = document.array();
        if (!document.isArray()) {
            qWarning("JSON is not an array.");
            return result;
        }
        for(const QJsonValue &val : jsonarray)
        {
            QJsonObject jsonObject = val.toObject();
            QVector<QString> elem_of_vec;
            elem_of_vec.append(jsonObject["title"].toString());
            elem_of_vec.append(jsonObject["description"].toString());
            result.append(elem_of_vec);
        }
        return result;
    }
signals:

};

#endif // LISTITEM_H
