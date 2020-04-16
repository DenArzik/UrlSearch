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

	void loadUrl(const QString &str);
	void loadURL(const QUrl &url);

private:
	QNetworkAccessManager *manager;

private slots:
	void replyFinished(QNetworkReply *nr);

signals:
	void errorString(const QString &str);
	void urlContent(const QByteArray &str);

};
