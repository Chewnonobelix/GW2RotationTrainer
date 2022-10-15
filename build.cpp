#include "build.h"

Build::Build(QObject *parent)
    : QObject{parent}
{

}

int Build::id () const
{
    return m_build["id"];
}

QString Build::mainHand1 () const
{
    return m_weapons["mainHand1"];
}

QString Build::offHand1 () const
{
    return m_weapons["offHand1"];
}

QString Build::offHand2 () const
{
    return m_weapons["offHand2"];
}

QString Build::mainHand2 () const
{
    return m_weapons["mainHand2"];
}

int Build::heal () const
{
    return m_build["heal"];
}

int Build::utility1 () const
{
    return m_build["utility1"];
}

int Build::utility2 () const
{
    return m_build["utility2"];
}

int Build::utility3 () const
{
    return m_build["utility3"];
}

int Build::elite () const
{
    return m_build["elite"];
}

QString Build::name() const
{
    return m_name;
}

QString Build::profession() const
{
    return m_profession;
}

void Build::setId (int id)
{
    m_build["id"] = id;
}

void Build::setMainHand1 (QString id)
{
    m_weapons["mainHand1"] = id;
    emit mainHand1Changed();
    qDebug()<<m_weapons<<m_build;
}

void Build::setOffHand1 (QString id)
{
    m_weapons["offHand1"] = id;
    emit offHand1Changed();
    qDebug()<<m_weapons<<m_build;
}

void Build::setOffHand2 (QString id)
{
    m_weapons["offHand2"] = id;
    emit offHand2Changed();
    qDebug()<<m_weapons<<m_build;
}

void Build::setMainHand2 (QString id)
{
    m_weapons["mainHand2"] = id;
    emit mainHand2Changed();
    qDebug()<<m_weapons<<m_build;
}

void Build::setHeal (int id)
{
    m_build["heal"] = id;
    emit healChanged();
    qDebug()<<m_weapons<<m_build;
}

void Build::setUtility1 (int id)
{
    auto other = m_build.key(id);

    if(other.isEmpty()) {
        m_build["utility1"] = id;
        emit utility3Changed();
    }
    else {
        swap(other, "utility1");
    }
    qDebug()<<m_weapons<<m_build;
}

void Build::setUtility2 (int id)
{
    auto other = m_build.key(id);

    if(other.isEmpty()) {
        m_build["utility2"] = id;
        emit utility3Changed();
    }
    else {
        swap(other, "utility2");
    }
    qDebug()<<m_weapons<<m_build;
}

void Build::setUtility3 (int id)
{
    auto other = m_build.key(id);

    if(other.isEmpty()) {
        m_build["utility3"] = id;
        emit utility3Changed();
    }
    else {
        swap(other, "utility3");
    }

    qDebug()<<m_weapons<<m_build;
}

void Build::setElite (int id)
{
    m_build["elite"] = id;
    emit eliteChanged();
    qDebug()<<m_weapons<<m_build;
}

void Build::setName(QString name)
{
    m_name = name;
    emit nameChanged();
}

void Build::setProfession(QString profession)
{
    m_profession = profession;
    emit professionChanged();
}

void Build::swap(QString v1, QString v2)
{
    auto temp = m_build[v1];
    m_build[v1] = m_build[v2];
    m_build[v2] = temp;

    emit utility1Changed();
    emit utility2Changed();
    emit utility3Changed();
}
