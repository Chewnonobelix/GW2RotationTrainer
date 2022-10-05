#include "dataprovider.h"

DataProvider::DataProvider()
{
}

void DataProvider::onReadyState()
{
    auto reply = dynamic_cast<QNetworkReply*>(sender());
    reply->waitForReadyRead(5000);
    auto data = reply->readAll();
    auto doc = QJsonDocument::fromJson(data);

    if(doc.isArray())
        emit dataArrayReady(doc.array());
    else
        emit dataObjectReady(doc.object());
}

void DataProvider::request(QString req)
{
    auto reply = m_manager.get(QNetworkRequest(QUrl(req)));
    connect(reply, &QNetworkReply::finished, this, &DataProvider::onReadyState);
}
