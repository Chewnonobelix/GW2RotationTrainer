#include "profession.h"

Skill::Skill(QJsonObject obj): QJsonObject(obj)
{}

int Skill::id() const
{
    return value("id").toInt();
}

QUrl Skill::icon() const
{
    return value("icon").toString();
}

QString Skill::slot() const
{
    return value("icon").toString();
}

QString Skill::description() const
{
    return value("description").toString();
}

QString Skill::name() const
{
    return value("name").toString();
}


int Skill::cooldown() const
{
    auto facts = value("facts").toArray();
    auto it = std::find_if(facts.begin(), facts.end(), [](auto value) {
       return value.toObject()["type"].toString() == "Recharge";
    });
    return it != facts.end() ? it->toObject()["value"].toInt() : 0;
}

Weapon::Weapon(QJsonObject obj): QJsonObject(obj)
{
    QObject::connect(&dp, &DataProvider::dataObjectReady, [this](auto obj) {
         skills<<Skill(obj);
    });
}

int Weapon::id() const
{
    return value("id").toInt();
}

QUrl Weapon::icon() const
{
    return value("icon").toString();
}

QString Weapon::name() const
{
    return value("name").toString();
}
QStringList Weapon::hand() const
{
    QStringList ret;
    for(auto it: value("flags").toArray())
        ret<<it.toString();
    return ret;
}

Profession::Profession()
{

}

void Profession::setName(QString name)
{
    m_name = name;

    m_dp.request(QString("https://api.guildwars2.com/v2/professions/%1").arg(name));
}
