#pragma once

#include <QObject>

class SearchManager;

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
	bool search(const QString &url);

	bool download(const QString &url);

	//bool scan();

};
