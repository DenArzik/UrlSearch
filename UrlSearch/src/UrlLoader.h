#pragma once

#include <QObject>

class QNetworkReply;
class QNetworkAccessManager;

class UrlLoader : public QObject
{
	Q_OBJECT

private:
	UrlLoader(QObject *parent);
	~UrlLoader();

	UrlLoader(const QObject &obj) = delete;
	UrlLoader &operator=(const QObject &obj) = delete;

public:
	static UrlLoader *get();

	QNetworkReply *sendLoadRequest(const QString &str);
	QNetworkReply *sendLoadRequest(const QUrl &url);

private:
	QNetworkAccessManager *manager;

private slots:
	void replyFinished(QNetworkReply *nr);

signals:
	void responce(QNetworkReply *str);

};
