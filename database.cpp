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
    auto id = query.lastInsertId();
    qDebug()<<"Insert build"<<query.lastError()<<id;

    auto opening = build["opening"].toArray();
    auto rotation = build["rotation"].toArray();

    auto inserter = [id, this](QJsonArray array, bool isOpening) {
        for(auto i = 0; i < array.count(); i++) {
            auto queryRole = m_db.exec(QString("SELECT id FROM mapping WHERE role='%1'").arg(array[i].toObject()["role"].toString()));
            queryRole.next();
            auto role = queryRole.record().value("id").toInt();
            auto queryRot = m_db.exec(QString("INSERT INTO rotation (build, role, opening, 'index') VALUES ('%1', '%2', '%3', '%4')")
                                      .arg(id.toInt()).arg(role).arg(isOpening).arg(i));

            qDebug()<<"Rot insert"<<queryRot.lastQuery()<<queryRot.lastError();
        }
    };

    inserter(opening, true);
    inserter(rotation, false);
}
