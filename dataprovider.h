#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class DataProvider: public QObject
{
    Q_OBJECT

private:
public:
    DataProvider();
    ~DataProvider() = default;
    void request(QString);

private:
    QNetworkAccessManager m_manager;

    void onReadyState();

signals:
    void dataObjectReady(QJsonObject);
    void dataArrayReady(QJsonArray);
};

