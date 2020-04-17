#include "SearchWorker.h"

#include "SearchManager.h"
#include "UrlSearchStatusModel.h"

#include <optional>

#include <QThread>
#include <QNetworkReply>

SearchManager *SearchWorker::s_mgr = nullptr;

SearchWorker::SearchWorker(SearchManager *mgr, QObject *parent)
	: QObject(parent)
{
	if (s_mgr == nullptr)
	{
		s_mgr = mgr;
	}
}

SearchWorker::~SearchWorker()
{
}

void SearchWorker::doWork()
{

	while (true)
	{
		const QString &url = s_mgr->popUrl();
		search(url);
		//clean up networkreply
	}

	emit finished();
}

bool SearchWorker::search(const QString &url)
{
	//divide into functions
	download(url);

	s_mgr->getUrlSearchStatusModel()->setUrlDownloaded(url, true);

	//scan();


	return false;
}

bool SearchWorker::download(const QString &url)
{
	s_mgr->sendDownloadRequest(this, url);

	QNetworkReply* reply = nullptr;
	{
		std::optional<QNetworkReply*> optReply;
		while (!(optReply = s_mgr->tryGetResponce(this)))
		{
			QThread::msleep(10);
		}
		reply = optReply.value();
	}

	if (reply->error() != QNetworkReply::NoError)
	{
		s_mgr->getUrlSearchStatusModel()->setUrlError(url, reply->errorString());
		return false;
	}

	return true;
}
