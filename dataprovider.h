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
    void requestSkill(int);
    Q_INVOKABLE void requestProfession(QString);
    Q_INVOKABLE void requestProfessions();

private:
    QNetworkAccessManager m_manager;

signals:
    void skillEmited(QJsonObject);
    void professionEmited(QJsonObject);
    void professionsEmited(QStringList);
};

