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

Weapon::Weapon(const QJsonObject &obj): QJsonObject(obj)
{
}

Weapon::Weapon(const Weapon& wp): QJsonObject(wp)
{
    skills = wp.skills;
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

void Weapon::addSkill(QJsonObject obj)
{
    skills<<Skill(obj);
}

Weapon& Weapon::operator= (const Weapon& wp)
{
    (QJsonObject&)(*this) = (QJsonObject&)(wp);
    skills = wp.skills;

    return *this;
}

bool Weapon::isAquatic() const {return hand().contains("Aquatic");}
bool Weapon::isTwoHand() const {return hand().contains("TwoHand");}
bool Weapon::isMainHand() const {return hand().contains("Mainhand");}
bool Weapon::isOffHand() const {return hand().contains("Offhand");}


Skill  Weapon::weapon1() const
{
    auto it = std::find_if(skills.begin(), skills.end(), [](auto i) {
        return i.slot() == "Weapon_1";
    });

    return *it;
}
Skill  Weapon::weapon2() const
{
    auto it = std::find_if(skills.begin(), skills.end(), [](auto i) {
        return i.slot() == "Weapon_2";
    });

    return *it;
}

Skill  Weapon::weapon3() const
{
    auto it = std::find_if(skills.begin(), skills.end(), [](auto i) {
        return i.slot() == "Weapon_3";
    });

    return *it;
}

Skill  Weapon::weapon4() const
{
    auto it = std::find_if(skills.begin(), skills.end(), [](auto i) {
        return i.slot() == "Weapon_4";
    });

    return *it;
}

Skill  Weapon::weapon5() const
{
    auto it = std::find_if(skills.begin(), skills.end(), [](auto i) {
        return i.slot() == "Weapon_5";
    });

    return *it;
}

Skill  Weapon::weaponX(int index) const
{
    auto it = std::find_if(skills.begin(), skills.end(), [index](auto i) {
        return i.slot() == QString("Weapon_%1").arg(index);
    });

    return *it;
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
    auto wps = value("weapons").toObject();
    for(auto it: wps.keys()) {
        m_weapons[it] = Weapon{wps[it].toObject()};

        for(auto it2: wps[it].toObject()["skills"].toArray()) {
            m_dp.requestSkill(it2.toObject()["id"].toInt());
        }
    }
    emit weaponsChanged();
}

void Profession::receiveSkill(QJsonObject obj)
{
    if(obj["type"] != "Weapon") {
        m_skills<<Skill(obj);
        emit skillsChanged();
    }
    else {
        m_weapons[obj["weapon_type"].toString()].addSkill(obj);
    }
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

QStringList Profession::weapons() const
{
    return m_weapons.keys();
}

QVariantList Profession::mainHand() const
{
    QVariantList ret;
    for(auto it: m_weapons) {
        if(!it.isAquatic() && (it.isMainHand() || it.isTwoHand())) {
            ret<<QVariantMap{{"twohanded", it.isTwoHand()}, {"name", m_weapons.key(it)}};
        }
    }
    return ret;
}

QStringList Profession::offHand() const
{
    QStringList ret;
    for(auto it: m_weapons) {
        if(it.isOffHand() || (it.isTwoHand() && !it.isAquatic())) {
            ret<<m_weapons.key(it);
        }
    }
    return ret;
}

QStringList Profession::aquatic() const
{
    QStringList ret;
    for(auto it: m_weapons) {
        if(it.isOffHand()) {
            ret<<m_weapons.key(it);
        }
    }
    return ret;
}
