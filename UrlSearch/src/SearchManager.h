#pragma once

#include <QObject>
#include <QMutex>
#include <optional>

class SearchWorker;
class UrlSearchStatusModel;
class Application;
class QThread;
class QNetworkReply;
class UrlLoader;

class SearchManager : public QObject
{
	Q_OBJECT

public:
	SearchManager(const Application *mainWindow, UrlSearchStatusModel *urlModel, 
		UrlLoader *urlLoader, QObject *parent);
	~SearchManager();

private:
	const Application *m_mainWindow;
	UrlSearchStatusModel *m_urlModel;

	void init();
	void initThreads();

	typedef std::pair<QThread *, SearchWorker *> ThreadWorker;
	std::vector<ThreadWorker> threadWorkerList;

	//to protect [popUrl]
	QMutex m_mutex;

public:
	//returning reference is acceptable untill there is deletion 
	//possibility from model during serch
	//need race protection
	const QString &popUrl();

	UrlSearchStatusModel *getUrlSearchStatusModel();

private:
	UrlLoader *m_urlLoader;

	//to identify responce with worker who sent it
	std::map<const SearchWorker *const, QNetworkReply *> workerRequestMap;
	//to check whether reply allready came from [urlLoader]
	std::map<QNetworkReply *, bool> replyArrivalMap;

private slots:
	void responceHandler(QNetworkReply *reply);

public:
	void sendDownloadRequest(const SearchWorker *worker, const QString &url);

	std::optional<QNetworkReply *> tryGetResponce(const SearchWorker *worker);

	QString getSearchText() const;

};
