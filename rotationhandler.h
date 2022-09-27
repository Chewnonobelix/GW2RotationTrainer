#pragma once
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QRandomGenerator>
#include <QNetworkAccessManager>

class RotationHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonObject rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(QJsonArray mapping READ mapping WRITE setMapping NOTIFY mappingChanged)

    Q_PROPERTY(int total READ total NOTIFY totalChanged)
    Q_PROPERTY(int success READ success NOTIFY successChanged)
    Q_PROPERTY(QString currentDisplay READ currentDisplay NOTIFY currentDisplayChanged)
    Q_PROPERTY(QString currentRole READ currentRole NOTIFY currentRoleChanged)
    Q_PROPERTY(QString color READ color NOTIFY colorChanged)

public:
    explicit RotationHandler(QObject *parent = nullptr);

    Q_INVOKABLE int indexFromKey(QString key);
    Q_INVOKABLE QString keyFromRole(QString role);
    Q_INVOKABLE void validate(QString key);
    Q_INVOKABLE void next();
    Q_INVOKABLE void randomKey();
    Q_INVOKABLE void save(QUrl);
    Q_INVOKABLE void load(QUrl);
    Q_INVOKABLE QUrl icon() const;

    QJsonObject rotation() const;
    QJsonArray mapping() const;
    int total() const;
    int success() const;
    QString currentDisplay() const;
    QString currentRole() const;
    QString color() const;

    void setMapping(QJsonArray);
    void setRotation(QJsonObject);
    Q_INVOKABLE void append(QString, QJsonObject);

signals:
    void rotationChanged();
    void mappingChanged();
    void totalChanged();
    void successChanged();
    void currentDisplayChanged();
    void currentRoleChanged();
    void colorChanged();

private:
    QJsonObject m_rotation;
    QJsonArray m_mapping;

    int m_success = 0;
    int m_total = 0;
    QString m_currentDisplay = "";
    QString m_currentRole = "";
    QString m_color = "white";
    int m_currentRot = 0;
    int m_currentOpening = 0;
    bool m_isOpening = false;

    void setting();
    QUrl m_icon;
    QNetworkAccessManager m_network;
};

