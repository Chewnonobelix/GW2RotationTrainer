#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("rotation");
    if(!m_db.open())
        qDebug()<<"Gw2 rotation database not found";
    else
        qDebug()<<"Gw2 rotation database open";
}

QJsonArray DataBase::mapping() const
{
    QJsonArray ret;
    auto query = m_db.exec("SELECT role, key FROM mapping");

    while(query.next()) {
        auto record = query.record();
        QJsonObject obj;
        obj["role"] = record.value("role").toString();
        obj["key"] = record.value("key").toString();
        ret<<obj;
    }
    return ret;
}

QJsonObject DataBase::build(int) const
{
    return QJsonObject();
}

QStringList DataBase::builds() const
{
    QStringList ret;

    auto query = m_db.exec("SELECT name FROM builds");
    while(query.next()) {
        auto record = query.record();
        ret<<record.value("name").toString();
    }

    return ret;
}

void DataBase::addBuild(QJsonObject build)
{
    qDebug()<<build;
    auto query = m_db.exec(QString("INSERT INTO builds (name) VALUES('%1')").arg(build["name"].toString()));
    qDebug()<<"Insert build"<<query.lastError();
}
