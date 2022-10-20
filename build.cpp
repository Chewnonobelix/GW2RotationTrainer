#include "build.h"

Build::Build(QObject *parent)
    : QObject{parent}, m_db(DataBase::instance())
{
    (*this)["utility1"] = -1;
    (*this)["utility2"] = -1;
    (*this)["utility3"] = -1;
}

int Build::id () const
{
    return (*this)["id"].toInt();
}

QString Build::mainHand1 () const
{
    return (*this)["weapons"].toObject()["mainHand1"].toString();
}

QString Build::offHand1 () const
{
    return (*this)["weapons"].toObject()["offHand1"].toString();
}

QString Build::offHand2 () const
{
    return (*this)["weapons"].toObject()["offHand2"].toString();
}

QString Build::mainHand2 () const
{
    return (*this)["weapons"].toObject()["mainHand2"].toString();
}

int Build::heal () const
{
    return (*this)["skills"].toObject()["heal"].toInt();
}

int Build::utility1 () const
{
    return (*this)["skills"].toObject()["utility1"].toInt();
}

int Build::utility2 () const
{
    return (*this)["skills"].toObject()["utility2"].toInt();
}

int Build::utility3 () const
{
    return (*this)["skills"].toObject()["utility3"].toInt();
}

int Build::elite () const
{
    return (*this)["skills"].toObject()["elite"].toInt();
}

QString Build::name() const
{
    return (*this)["name"].toString();
}

QString Build::profession() const
{
    return (*this)["profession"].toString();
}

void Build::setId (int id)
{
    (*this)["id"] = id;
}

void Build::setMainHand1 (QString id)
{
    auto weapons = (*this)["weapons"].toObject();
    weapons["mainHand1"] = id;
    (*this)["weapons"] = weapons;

    emit mainHand1Changed();
}

void Build::setOffHand1 (QString id)
{
    auto weapons = (*this)["weapons"].toObject();
    qDebug()<<weapons;
    weapons["offHand1"] = id;
    (*this)["weapons"] = weapons;
    qDebug()<<weapons;
    emit offHand1Changed();
}

void Build::setOffHand2 (QString id)
{
    auto weapons = (*this)["weapons"].toObject();
    weapons["offHand2"] = id;
    (*this)["weapons"] = weapons;

    emit offHand2Changed();
}

void Build::setMainHand2 (QString id)
{
    auto weapons = (*this)["weapons"].toObject();
    weapons["mainHand2"] = id;
    (*this)["weapons"] = weapons;

    emit mainHand2Changed();
}

void Build::setSkill(QString name, int id, bool swapable)
{
    auto skills = (*this)["skills"].toObject();

    auto other = swapable ? std::find_if(skills.begin(), skills.end(), [id](auto it) {
        return id != -1 && it.toInt() == id ;
    }): skills.end();

    if(!swapable || other == skills.end()) {
        skills[name] = id;
        (*this)["skills"] = skills;

        emit utilityChanged();
    }
    else {
        swap(other.key(), name);
    }
}

void Build::setHeal (int id)
{
    setSkill("heal", id);

    emit healChanged();
}

void Build::setUtility1 (int id)
{
    setSkill("utility1", id, true);
    emit utilityChanged();
}

void Build::setUtility2 (int id)
{
    setSkill("utility2", id, true);
    emit utilityChanged();
}

void Build::setUtility3 (int id)
{
    setSkill("utility3", id, true);
    emit utilityChanged();
}

void Build::setElite (int id)
{
    setSkill("elite", id);

    emit eliteChanged();
}

void Build::setName(QString name)
{
    (*this)["name"] = name;
    emit nameChanged();
}

void Build::setProfession(QString profession)
{
    (*this)["profession"] = profession;
    emit professionChanged();
}

void Build::swap(QString v1, QString v2)
{

    auto skills = (*this)["skills"].toObject();

    auto temp = skills[v1].toInt();
    skills[v1] = skills[v2];
    skills[v2] = temp;
    (*this)["skills"] = skills;
}

void Build::save()
{
    m_db.addBuild(*this);
}

void Build::load(int id)
{
    auto json = m_db.build(id);
    (QJsonObject&)(*this) = json;

    emit nameChanged();
    emit professionChanged();
    emit healChanged();
    emit utilityChanged();
    emit eliteChanged();
}
