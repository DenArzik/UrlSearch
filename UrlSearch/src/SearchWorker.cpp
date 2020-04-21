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

	while ( !s_mgr->jobFinished() )
	{
		const QString url = s_mgr->popUrl();

		if (url == "")
		{
			s_mgr->incrementIterations();
			return;
		}

		QNetworkReply *reply = download(url);
		if (reply == nullptr)
		{
			continue;
		}

		search( url, QString( reply->readAll().data() ) );
		
		s_mgr->removeNetworkReply(this);

		s_mgr->incrementIterations();
	}

	emit finished();
}

void SearchWorker::search(const QString &url, const QString &urlContent)
{
	const ScanResult result = scan(urlContent);

	for (const QString &itm: result.urlList)
	{
		s_mgr->getUrlSearchStatusModel()->insertUrl(itm);
	}

	//to avoid accessing mutex more than necessary
	if (result.textFound == true)
	{
		s_mgr->getUrlSearchStatusModel()->setUrlTextFound(url, result.textFound);
	}
}

QNetworkReply *SearchWorker::download(const QString &url)
{
	s_mgr->sendDownloadRequest(this, url);

	QNetworkReply *reply = nullptr;
	{
		std::optional<QNetworkReply *> optReply;
		while (!(optReply = s_mgr->tryGetResponce(this)))
		{
			QThread::msleep(10);
		}
		reply = optReply.value();
	}

	if (reply->error() != QNetworkReply::NoError)
	{
		s_mgr->getUrlSearchStatusModel()->setUrlError(url, reply->errorString());
		return nullptr;
	}

	s_mgr->getUrlSearchStatusModel()->setUrlDownloaded(url, true);
	return reply;
}

SearchWorker::ScanResult SearchWorker::scan(const QString &urlContent)
{
	ScanResult result;
	const QString searchText = s_mgr->getSearchText();

	QRegExp textAndUrl( QString("(%1|HTTPS:\/\/.*\")").arg(searchText) );
	textAndUrl.setCaseSensitivity(Qt::CaseInsensitive);
	QRegExp justUrl("HTTPS:\/\/.*\")");
	justUrl.setCaseSensitivity(Qt::CaseInsensitive);

	int pos = 0;
	while ((pos = textAndUrl.indexIn(urlContent, pos)) != -1) {
		qDebug() << textAndUrl.cap(1);
		pos += textAndUrl.matchedLength();
	}


	return {};
}
