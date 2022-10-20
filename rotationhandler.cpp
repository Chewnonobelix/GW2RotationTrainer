#include "rotationhandler.h"
#include <QDebug>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>


RotationHandler::RotationHandler(QObject *parent)
    : QObject{parent}, m_db(DataBase::instance())
{
    m_mapping = m_db.mapping();
}

int RotationHandler::indexFromKey(QString key)
{
    auto it = std::find_if(m_mapping.begin(), m_mapping.end(), [key](auto it) {
       return it.toObject()["key"].toString() == key;
    });

    return std::distance(m_mapping.begin(), it);
}

QString RotationHandler::keyFromRole(QString role)
{
    auto it = std::find_if(m_mapping.begin(), m_mapping.end(), [role](auto it) {
       return it.toObject()["role"].toString() == role;
    });

    return it->toObject()["key"].toString();
}

void RotationHandler::validate(QString key)
{
    emit successChanged();
    if(key == m_currentDisplay) {
        m_color = "green";
        m_success++;
    }
    else
        m_color = "red";

    emit colorChanged();
//    randomKey();
    next();
}

void RotationHandler::next()
{
    m_isOpening ? m_currentOpening++ : (m_currentRot = (m_currentRot+1)%m_rotation["rotation"].toArray().count());
    m_isOpening = m_currentOpening < m_rotation["opening"].toArray().count();
    setting();
    m_total++;
    emit totalChanged();
}

void RotationHandler::randomKey()
{
    static QRandomGenerator gen;
    auto rnd = gen.bounded(0, m_mapping.count());

    m_currentRole = m_mapping[rnd].toObject()["role"].toString();
    m_currentDisplay = m_mapping[rnd].toObject()["key"].toString();

    emit currentDisplayChanged();
    emit currentRoleChanged();
    m_total++;
    emit totalChanged();

}

QJsonObject RotationHandler::rotation() const
{
    return m_rotation;
}

QJsonArray RotationHandler::mapping() const
{
    return m_mapping;
}

int RotationHandler::total() const
{
    return m_total;
}

int RotationHandler::success() const
{
    return m_success;
}
QString RotationHandler::currentDisplay() const
{
    return m_currentDisplay;
}

QString RotationHandler::currentRole() const
{
    return m_currentRole;
}

QString RotationHandler::color() const
{
    return m_color;
}

void RotationHandler::setMapping(QJsonArray mapping)
{
    m_mapping = mapping;
    emit mappingChanged();
}

void RotationHandler::save(QString name)
{
    m_rotation["name"] = name;
    m_db.addBuild(m_rotation);
}

void RotationHandler::load(int id)
{
    auto obj = m_db.build(id);
    m_rotation = obj;

    m_currentRot = 0;
    m_currentOpening = 0;

    emit rotationChanged();

    setting();
}

void RotationHandler::setting()
{
    auto l = [this](QJsonArray array, int index) {
        m_currentRole = array[index].toObject()["role"].toString();
        m_currentDisplay = keyFromRole(m_currentRole);
    };

    if(m_isOpening) {
        l(m_rotation["opening"].toArray(), m_currentOpening);
    }
    else {
        l(m_rotation["rotation"].toArray(), m_currentRot);
    }

    emit currentDisplayChanged();
    emit currentRoleChanged();
}

void RotationHandler::setRotation(QJsonObject rot)
{
    m_rotation["opening"] = rot["opening"];
    m_rotation["rotation"] = rot["rotation"];
}

void RotationHandler::append(QString key, QJsonObject map)
{
    auto array = m_rotation[key].toArray();
    array.append(map);
    m_rotation[key] = array;
}

QJsonArray RotationHandler::buildsList() const
{
    qDebug()<<m_db.builds();
    return m_db.builds();
}
