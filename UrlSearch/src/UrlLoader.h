#pragma once

#include <QObject>

class QNetworkReply;
class QNetworkAccessManager;

class UrlLoader : public QObject
{
	Q_OBJECT

public:
	UrlLoader(QObject *parent);
	~UrlLoader();

	QNetworkReply *sendLoadRequest(const QString &str);
	QNetworkReply *sendLoadRequest(const QUrl &url);

private:
	QNetworkAccessManager *manager;

private slots:
	void replyFinished(QNetworkReply *nr);

signals:
	void responce(QNetworkReply *str);

};
