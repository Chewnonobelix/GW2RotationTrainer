#include "profession.h"

Skill::Skill(QJsonObject obj): QJsonObject(obj)
{}

int Skill::id() const
{
    return value("id").toInt();
}

QUrl Skill::icon() const
{
    return QUrl(value("icon").toString());
}

QString Skill::slot() const
{
    return value("slot").toString();
}

QString Skill::description() const
{
    return value("description").toString();
}

QString Skill::name() const
{
    return value("name").toString();
}

QString Skill::category() const
{
    QStringList ret;
    for(auto it: value("categories").toArray()) {
        ret<<it.toString();
    }
    return value("categories").toArray().isEmpty() ? "" : value("categories").toArray().first().toString();
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
}

int Weapon::id() const
{
    return value("id").toInt();
}

QUrl Weapon::icon() const
{
    return QUrl(value("icon").toString());
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
    QObject::connect(&m_dp, &DataProvider::professionEmited, this, &Profession::receiveProfession);
    QObject::connect(&m_dp, &DataProvider::skillEmited, this, &Profession::receiveSkill);
}

Profession::Profession(const Profession& p): QJsonObject(p)
{
    QObject::connect(&m_dp, &DataProvider::professionEmited, this, &Profession::receiveProfession);
    QObject::connect(&m_dp, &DataProvider::skillEmited, this, &Profession::receiveSkill);
}

Profession::Profession(const QJsonObject& p): QJsonObject(p)
{
    QObject::connect(&m_dp, &DataProvider::professionEmited, this, &Profession::receiveProfession);
    QObject::connect(&m_dp, &DataProvider::skillEmited, this, &Profession::receiveSkill);
}

void Profession::setName(QString name)
{
    m_name = name;
    m_skills.clear();
    m_weapons.clear();
    m_dp.requestProfession(name);
}

Profession& Profession::operator= (const QJsonObject& obj)
{
    (QJsonObject&)(*this) = obj;

    for(auto it: value("skills").toArray())
        m_dp.requestSkill(it.toObject()["id"].toInt());

    return *this;
}

Profession& Profession::operator= (const Profession& obj)
{
    (*this) = (QJsonObject)obj;

    return *this;
}
void Profession::receiveProfession(QJsonObject obj)
{
    (*this) = obj;
}

void Profession::receiveSkill(QJsonObject obj)
{
    m_skills<<Skill(obj);
    auto& last = m_skills.last();
    qDebug()<<m_skills.size()<<last.name()<<last.id()<<last.description()<<last.slot();
    emit skillsChanged();
}

QVariantList Profession::skills(QString slot) const
{
    QVariantList ret;
    for(auto it: m_skills) {
        if(it.slot().contains(slot))
         ret<<QVariant::fromValue(it);
    }
    return ret;
}


QVariantList Profession::utilities() const
{
    return skills("Utility");
}

QVariantList Profession::heal() const
{
    return skills("Heal");
}

QVariantList Profession::elite() const
{
    return skills("Elite");
}

QVariantList Profession::professionsSkill() const
{
    return skills("Profession");
}
