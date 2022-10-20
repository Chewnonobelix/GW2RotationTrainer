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

    QJsonArray mapping() const;
    QJsonObject build(int) const;
    QJsonArray builds() const;
    void addBuild(QJsonObject);

    static DataBase& instance();
signals:
private:
    explicit DataBase(QObject* = nullptr);

    QSqlDatabase m_db;

};

