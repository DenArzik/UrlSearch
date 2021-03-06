#include "SearchManager.h"

#include <QThread>
#include <QMutex>
#include <QNetworkReply>

#include "Application.h"
#include "SearchWorker.h"
#include "UrlSearchStatusModel.h"
#include "UrlLoader.h"

SearchManager::SearchManager(const Application *mainWindow, UrlSearchStatusModel *urlModel, QObject *parent)
	: QObject(parent)
	, m_mainWindow(mainWindow)
	, m_urlModel(urlModel)
	, workersIterationCount(0)
{
	init();

	m_urlModel->insertUrl(m_mainWindow->getUrl());
}

SearchManager::~SearchManager()
{
	for (auto &itm : threadWorkerList)
	{
		itm.first->deleteLater();
	}
}

void SearchManager::init()
{
	initThreads();

	connect(UrlLoader::get(), &UrlLoader::responce, this, &SearchManager::responceHandler);
}

void SearchManager::initThreads()
{
	const int threaCount = m_mainWindow->getThreadCount();
	threadWorkerList.resize(threaCount);

	for (auto &it : threadWorkerList)
	{
		it.first = new QThread;
		it.second = new SearchWorker(this, nullptr);
		it.second->moveToThread(it.first);
		connect(it.first, &QThread::finished, it.second, &QObject::deleteLater);
		connect(it.first, &QThread::started, it.second, &SearchWorker::doWork);
		it.first->start();

		workerRequestMap[it.second] = nullptr;
	}
}

QString SearchManager::popUrl()
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

UrlSearchStatusModel *SearchManager::getUrlSearchStatusModel()
{
	return m_urlModel;
}

void SearchManager::removeNetworkReply(const SearchWorker *worker)
{
	replyArrivalMap.erase(workerRequestMap[worker]);
	workerRequestMap[worker]->deleteLater();
}

void SearchManager::sendDownloadRequest(const SearchWorker *worker, const QString &url)
{
	QNetworkReply *reply = UrlLoader::get()->sendLoadRequest(url);
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

void SearchManager::incrementIterations()
{
	++workersIterationCount;
}

bool SearchManager::jobFinished() const
{
	return m_mainWindow->getMaxUrlCount() < workersIterationCount;
}


void SearchManager::responceHandler(QNetworkReply *reply)
{
	replyArrivalMap[reply] = true;
}