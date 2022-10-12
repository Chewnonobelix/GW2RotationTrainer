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
    QString category() const;
    int cooldown() const;

    Q_GADGET

    Q_PROPERTY(QUrl url READ icon)
    Q_PROPERTY(QString slot READ slot)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString category READ category)
    Q_PROPERTY(int cooldown READ cooldown)

};

class Weapon: public QJsonObject {
    QList<Skill> skills;

public:
    Weapon() = default;
    Weapon(const Weapon&);
    Weapon(const QJsonObject&);
    int id() const;
    QUrl icon() const;
    QString name() const;
    QStringList hand() const;

    bool isAquatic() const;
    bool isTwoHand() const;
    bool isMainHand() const;
    bool isOffHand() const;

    void addSkill(QJsonObject);

    Weapon& operator= (const Weapon&);
};

class Profession: public QObject,  public QJsonObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList utilities READ utilities NOTIFY skillsChanged)
    Q_PROPERTY(QVariantList heal READ heal NOTIFY skillsChanged)
    Q_PROPERTY(QVariantList elite READ elite NOTIFY skillsChanged)
    Q_PROPERTY(QVariantList profession READ professionsSkill NOTIFY skillsChanged)
    Q_PROPERTY(QStringList weapons READ weapons NOTIFY weaponsChanged)
    Q_PROPERTY(QVariantList mainHand READ mainHand NOTIFY weaponsChanged)
    Q_PROPERTY(QStringList offHand READ offHand NOTIFY weaponsChanged)
    Q_PROPERTY(QStringList aquatic READ aquatic NOTIFY weaponsChanged)

private:
    QString m_name;
    QMap<QString, Weapon> m_weapons;
    QList<Skill> m_skills;
    DataProvider m_dp;

    QVariantList skills(QString) const;

public:
    Profession();
    Profession(const Profession&);
    Profession(const QJsonObject&);
    ~Profession() = default;

    Profession& operator= (const QJsonObject&);
    Profession& operator= (const Profession&);
    Q_INVOKABLE void setName(QString);

    QVariantList utilities() const;
    QVariantList heal() const;
    QVariantList elite() const;
    QVariantList professionsSkill() const;
    QStringList weapons() const;
    QVariantList mainHand() const;
    QStringList offHand() const;
    QStringList aquatic() const;

signals:
    void skillsChanged();
    void weaponsChanged();

private slots:
    void receiveProfession(QJsonObject);
    void receiveSkill(QJsonObject);
};

