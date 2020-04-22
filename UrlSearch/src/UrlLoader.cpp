#include "UrlLoader.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
//wait for reply
#include <QEventLoop>

UrlLoader::UrlLoader(QObject *parent)
	: QObject(parent)
	, manager(new QNetworkAccessManager(this))
{
	connect(manager, &QNetworkAccessManager::finished, this, &UrlLoader::replyFinished);
}

UrlLoader::~UrlLoader()
{
}

QNetworkReply *UrlLoader::sendLoadRequest(const QUrl &url)
{
	return manager->get(QNetworkRequest(url));
}

UrlLoader *UrlLoader::get()
{
	static UrlLoader instance(nullptr);
	return &instance;
}

QNetworkReply *UrlLoader::sendLoadRequest(const QString &str)
{
	QUrl url(str);
	return sendLoadRequest(url);
}

void UrlLoader::replyFinished(QNetworkReply *nr)
{
	emit responce(nr);
}
