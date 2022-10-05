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
    auto query = m_db.exec("SELECT role, key, id FROM mapping");

    while(query.next()) {
        auto record = query.record();
        QJsonObject obj;
        obj["role"] = record.value("role").toString();
        obj["key"] = record.value("key").toString();
        obj["id"] = record.value("id").toInt();

        ret<<obj;
    }
    return ret;
}

QJsonObject DataBase::build(int id) const
{
    auto buildQuery = m_db.exec(QString("SELECT name FROM builds WHERE id='%1'").arg(id));

    buildQuery.next();
    auto record = buildQuery.record();
    QJsonObject ret;
    ret["name"] = record.value("name").toString();
    auto rotationQuery = m_db.exec(QString("SELECT 'index', opening, role FROM rotation WHERE build='%1' ORDER BY opening, 'index'").arg(id));
    auto map = mapping();

    QJsonArray opening, rotation;
    while (rotationQuery.next())
    {
        auto recordRotation = rotationQuery.record();
        auto roleId = recordRotation.value("role").toInt();
        auto it = std::find_if(map.begin(), map.end(), [roleId](auto obj) {
            return obj.toObject()["id"].toInt() == roleId;
        });

        QJsonObject obj;
        obj["role"] = it->toObject()["role"].toString();

        (recordRotation.value("opening").toBool() ? opening : rotation) << obj;
    }

    ret["opening"] = opening;
    ret["rotation"] = rotation;
    return ret;
}

QJsonArray DataBase::builds() const
{
    QJsonArray ret;

    auto query = m_db.exec("SELECT name, id FROM builds ORDER BY name");
    while(query.next()) {
        auto record = query.record();
        QJsonObject obj;
        obj["name"] = record.value("name").toString();
        obj["id"] = record.value("id").toInt();
        ret<<obj;
    }

    return ret;
}

void DataBase::addBuild(QJsonObject build)
{
    auto query = m_db.exec(QString("INSERT INTO builds (name) VALUES('%1')").arg(build["name"].toString()));
    auto id = query.lastInsertId();

    auto opening = build["opening"].toArray();
    auto rotation = build["rotation"].toArray();

    auto inserter = [id, this](QJsonArray array, bool isOpening) {
        for(auto i = 0; i < array.count(); i++) {
            auto queryRole = m_db.exec(QString("SELECT id FROM mapping WHERE role='%1'").arg(array[i].toObject()["role"].toString()));
            queryRole.next();
            auto role = queryRole.record().value("id").toInt();
            auto queryRot = m_db.exec(QString("INSERT INTO rotation (build, role, opening, 'index') VALUES ('%1', '%2', '%3', '%4')")
                                      .arg(id.toInt()).arg(role).arg(isOpening).arg(i));
        }
    };

    inserter(opening, true);
    inserter(rotation, false);
}
