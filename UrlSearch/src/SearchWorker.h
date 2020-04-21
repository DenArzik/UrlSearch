#pragma once

#include <QObject>

class SearchManager;
class QNetworkReply;

class SearchWorker : public QObject
{
	Q_OBJECT

public:
	SearchWorker(SearchManager *mgr, QObject *parent);
	~SearchWorker();

private:
	static SearchManager *s_mgr;

public slots:
	void doWork();

signals:
	void finished();

private:
	void search(const QString &url, const QString &urlContent);

	QNetworkReply *download(const QString &url);

	struct ScanResult
	{
		bool textFound;
		QStringList urlList;
	};

	ScanResult scan(const QString &arr);

};
