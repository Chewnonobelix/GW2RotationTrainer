#include "dataprovider.h"

DataProvider::DataProvider()
{
}

void DataProvider::requestSkill(int skillId)
{
    auto url = QString("https://api.guildwars2.com/v2/skills/%1").arg(skillId);
    auto reply = m_manager.get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, [reply, this]() {
       auto data = reply->readAll();
       auto doc = QJsonDocument::fromJson(data);
       emit skillEmited(doc.object());
    });
}

void DataProvider::requestProfession(QString name)
{
    auto url = QString("https://api.guildwars2.com/v2/professions/%1").arg(name);
    auto reply = m_manager.get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, [reply, this]() {
       auto data = reply->readAll();
       auto doc = QJsonDocument::fromJson(data);
       emit professionEmited(doc.object());

    });
}

void DataProvider::requestProfessions()
{
    auto reply = m_manager.get(QNetworkRequest(QUrl("https://api.guildwars2.com/v2/professions")));
    connect(reply, &QNetworkReply::finished, [reply, this]() {
       auto data = reply->readAll();
       auto doc = QJsonDocument::fromJson(data);
       QStringList ret;
       for(auto it: doc.array())
           ret<<it.toString();
       emit professionsEmited(ret);
    });
}

