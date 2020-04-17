#include "SearchManager.h"

#include <QThread>
#include <QMutex>
#include <QNetworkReply>

#include "Application.h"
#include "SearchWorker.h"
#include "UrlSearchStatusModel.h"
#include "UrlLoader.h"

SearchManager::SearchManager(const Application *mainWindow, UrlSearchStatusModel *urlModel, 
	UrlLoader* urlLoader, QObject *parent)
	: QObject(parent)
	, m_mainWindow(mainWindow)
	, m_urlModel(urlModel)
	, m_urlLoader(urlLoader)
{
	init();
}

SearchManager::~SearchManager()
{
}

void SearchManager::init()
{
	initThreads();

	connect(m_urlLoader, &UrlLoader::responce, this, &SearchManager::responceHandler);
}

void SearchManager::initThreads()
{
	const int threaCount = m_mainWindow->getThreadCount();
	threadWorkerList.resize(threaCount);

	for (auto &it : threadWorkerList)
	{
		it.first = new QThread;
		it.second = new SearchWorker(this, nullptr);

		workerRequestMap[it.second] = nullptr;
	}
}

const QString &SearchManager::popUrl()
{
	QMutexLocker locker(&m_mutex);

	auto map = m_urlModel->getUrlMap();
	for (auto &itm : map)
	{
		if (itm.second.m_picked == false)
		{
			itm.second.m_picked = true;
			return itm.first;
		}
	}
	return "";
}

UrlSearchStatusModel* SearchManager::getUrlSearchStatusModel()
{
	return m_urlModel;
}

void SearchManager::sendDownloadRequest(const SearchWorker *worker, const QString &url)
{
	QNetworkReply *reply = m_urlLoader->sendLoadRequest(url);
	workerRequestMap[worker] = reply;
	replyArrivalMap[reply] = false;
}

std::optional<QNetworkReply *> SearchManager::tryGetResponce(const SearchWorker *worker)
{
	QNetworkReply *reply = workerRequestMap[worker];
	if (replyArrivalMap[reply] == true)
	{
		return reply;
	}
	return {};
}

QString SearchManager::getSearchText() const
{
	return m_mainWindow->getSearchText();
}

void SearchManager::responceHandler(QNetworkReply *reply)
{
	replyArrivalMap[reply] = true;
}