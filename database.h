#pragma once
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlField>

class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject* = nullptr);

    QJsonArray mapping() const;
    QJsonObject build(int) const;
    QJsonArray builds() const;
    void addBuild(QJsonObject);

signals:
private:
    QSqlDatabase m_db;
};

