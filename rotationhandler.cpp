#include "rotationhandler.h"
#include <QDebug>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>


RotationHandler::RotationHandler(QObject *parent)
    : QObject{parent}
{
    connect(&m_network, &QNetworkAccessManager::finished, [this](auto reply) {
        auto json = QJsonDocument::fromJson(reply->readAll()).array();
        qDebug()<<json<<json[0].toObject()["icon"]<<json[0].toObject()["icon"].toString()<<QUrl(json[0].toObject()["icon"].toString());
        m_icon = QUrl(json[0].toObject()["icon"].toString());
    } );
    m_network.get(QNetworkRequest(QUrl("https://api.guildwars2.com/v2/skills?ids=21762")));
}

int RotationHandler::indexFromKey(QString key)
{
    for(auto i = 0; i < 17; i++) {
        if(m_mapping[i].toObject()["key"].toString() == key) {
            return i;
        }
    }
}

QString RotationHandler::keyFromRole(QString role)
{
    for(auto i = 0; i < 17; i++) {
        if(m_mapping[i].toObject()["role"].toString() == role) {
            return m_mapping[i].toObject()["key"].toString();
        }
    }
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
    qDebug()<<m_mapping;
}

void RotationHandler::save(QUrl url)
{
    auto fileName = url.path().remove(0,1);
    QJsonDocument doc(m_rotation);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}

void RotationHandler::load(QUrl url)
{
    auto fileName = url.path().remove(0, 1);

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    auto json = file.readAll();
    file.close();

    m_currentRot = 0;
    m_currentOpening = 0;
    m_rotation = QJsonDocument::fromJson(json).object();

    emit rotationChanged();
    qDebug()<<m_rotation;
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
    m_rotation = rot;
}

void RotationHandler::append(QString key, QJsonObject map)
{
    auto array = m_rotation[key].toArray();
    array.append(map);
    m_rotation[key] = array;
}

QUrl RotationHandler::icon() const
{
    qDebug()<<m_icon;
    return m_icon;
}
