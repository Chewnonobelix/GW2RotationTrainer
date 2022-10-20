#pragma once

#include <QObject>
#include <QMap>
#include "database.h"

class Build : public QObject, public QJsonObject
{
    Q_OBJECT

    Q_PROPERTY(QString mainHand1 READ mainHand1 WRITE setMainHand1 NOTIFY mainHand1Changed)
    Q_PROPERTY(QString offHand1 READ offHand1 WRITE   setOffHand1  NOTIFY  offHand1Changed )
    Q_PROPERTY(QString offHand2 READ offHand2 WRITE   setOffHand2  NOTIFY  offHand2Changed )
    Q_PROPERTY(QString mainHand2 READ mainHand2 WRITE setMainHand2 NOTIFY mainHand2Changed)
    Q_PROPERTY(int heal READ heal WRITE           setHeal      NOTIFY      healChanged     )
    Q_PROPERTY(int utility1 READ utility1 WRITE   setUtility1  NOTIFY  utilityChanged )
    Q_PROPERTY(int utility2 READ utility2 WRITE   setUtility2  NOTIFY  utilityChanged )
    Q_PROPERTY(int utility3 READ utility3 WRITE   setUtility3  NOTIFY  utilityChanged )
    Q_PROPERTY(int elite READ elite WRITE         setElite     NOTIFY     eliteChanged    )
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QString profession READ profession WRITE setProfession NOTIFY professionChanged);

private:
//    QMap<QString, int> m_build;
//    QMap<QString, QString> m_weapons;
//    QString m_name;
//    QString m_profession;
    DataBase& m_db;

    void swap(QString, QString);
    void setSkill(QString, int, bool = false);
public:
    explicit Build(QObject *parent = nullptr);
    ~Build() = default;

    int id () const;
    QString mainHand1 () const;
    QString offHand1 () const;
    QString offHand2 () const;
    QString mainHand2 () const;
    int heal () const;
    int utility1 () const;
    int utility2 () const;
    int utility3 () const;
    int elite () const;
    QString name() const;
    QString profession() const;

    void setId (int);
    void setMainHand1 (QString);
    void setOffHand1 (QString);
    void setOffHand2 (QString);
    void setMainHand2 (QString);
    void setHeal (int);
    void setUtility1 (int);
    void setUtility2 (int);
    void setUtility3 (int);
    void setElite (int);
    void setName(QString);
    void setProfession(QString);

    Q_INVOKABLE void save();
    Q_INVOKABLE void load(int);

signals:
    void mainHand1Changed ();
    void offHand1Changed ();
    void offHand2Changed ();
    void mainHand2Changed ();
    void healChanged ();
    void utilityChanged ();
    void eliteChanged ();
    void nameChanged();
    void professionChanged();
};

