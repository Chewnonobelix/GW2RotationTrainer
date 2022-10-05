#pragma once

#include <QString>
#include <QJsonObject>

class Profession
{
    struct Skill: private QJsonObject {

    };

    struct Weapon {
        QString name;
        QString hand;
        QList<Skill> skills;
    };

private:
    QString m_name;
    QList<Weapon> m_weapons;
    QList<Skill> m_skills;

public:
    Profession();

};

