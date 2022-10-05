#pragma once

#include <QString>
#include <QJsonObject>

#include "dataprovider.h"

struct Skill: private QJsonObject {
    Skill(QJsonObject);

    int id() const;
    QUrl icon() const;
    QString slot() const;
    QString description() const;
    QString name() const;
    int cooldown() const;
};

class Weapon: private QJsonObject {
    QList<Skill> skills;

    DataProvider dp;

public:
    Weapon(QJsonObject);
    int id() const;
    QUrl icon() const;
    QString name() const;
    QStringList hand() const;

};

class Profession
{

private:
    QString m_name;
    QList<Weapon> m_weapons;
    QList<Skill> m_skills;
    DataProvider m_dp;

public:
    Profession();
    void setName(QString);

};

