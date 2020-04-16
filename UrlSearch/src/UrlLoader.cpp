#include "UrlLoader.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

UrlLoader::UrlLoader(QObject *parent)
	: QObject(parent)
{
	manager = new QNetworkAccessManager(this);

	connect(manager, &QNetworkAccessManager::finished, this, &UrlLoader::replyFinished);
}

UrlLoader::~UrlLoader()
{
}

void UrlLoader::loadURL(const QUrl &url)
{
	manager->get(QNetworkRequest(url));
}

void UrlLoader::loadUrl(const QString &str)
{
	QUrl url(str);
	loadURL(url);
}

void UrlLoader::replyFinished(QNetworkReply *nr)
{
	if (nr->error() != QNetworkReply::NoError)
	{
		emit errorString(nr->errorString());
		return;
	}

	QByteArray data = nr->readAll();
	emit urlContent(data);
}
