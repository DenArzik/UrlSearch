#include "UrlSearchStatusModel.h"

#include <QMutex>

UrlSearchStatusModel::UrlSearchStatusModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	//url_map["pornhub.com"].m_errorStr = "Scanned and approved";

	mutex = new QMutex;
}


int UrlSearchStatusModel::rowCount(const QModelIndex &parent) const
{
	return url_map.size();
}

int UrlSearchStatusModel::columnCount(const QModelIndex &parent) const
{
	//cause 2 columns
	return 2;
}

QString UrlSearchStatusModel::formatStatus(const UrlSearchStatus &itm)
{
	if (!itm.m_errorStr.isEmpty())
	{
		return itm.m_errorStr;
	}
	if (!itm.m_downloaded)
	{
		return "Downloading";
	}

	QString result("");
	if (!itm.m_scanned)
	{
		return "Scanning";
	}
	else
	{
		result += "Scanned. ";
	}

	result += itm.m_textFound ? "Text found!" : "Text not found.";
	return result;
}

const std::map<QString, UrlSearchStatus> UrlSearchStatusModel::getUrlMap() const
{
	return url_map;
}

void UrlSearchStatusModel::insertUrl(const QString &url)
{
	url_map[url]; 
	emit dataUpdated();
}

void UrlSearchStatusModel::setUrlPicked(const QString& url)
{
	url_map[url].m_picked = true;
	//data updated signal not required because this is not output variable
}

void UrlSearchStatusModel::setUrlError(const QString &url, const QString &error)
{
	url_map[url].m_errorStr = error;
	emit dataUpdated();
}

void UrlSearchStatusModel::setUrlDownloaded(const QString &url, bool downloaded)
{
	url_map[url].m_downloaded = downloaded;
	emit dataUpdated();
}

void UrlSearchStatusModel::setUrlScanned(const QString &url, bool scanned)
{
	url_map[url].m_scanned;
	emit dataUpdated();
}

void UrlSearchStatusModel::setUrlTextFound(const QString &url, bool found)
{
	url_map[url].m_textFound = found;
	emit dataUpdated();
}

void UrlSearchStatusModel::setUrl(const QString &url, const QString &error, bool downloaded, bool scanned, bool found)
{
	auto itm = url_map[url];
	itm.m_errorStr = error;
	itm.m_downloaded = downloaded;
	itm.m_scanned = scanned;
	itm.m_textFound = found;
	emit dataUpdated();
}



QVariant UrlSearchStatusModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	if (index.row() >= url_map.size())
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		auto it = url_map.cbegin();
		std::advance(it, index.row());
		if (index.column() == 0)
		{
			return it->first;
		}
		else
		{
			return formatStatus(it->second);
		}
	}
	else
	{
		return QVariant();
	}
}

QVariant UrlSearchStatusModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
	{
		return section == 0 ? "Url" : "Status";
	}
	else
	{
		return QStringLiteral("%1").arg(section + 1);
	}
}

Qt::ItemFlags UrlSearchStatusModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return Qt::ItemIsEnabled;
	}

	return QAbstractItemModel::flags(index);
}

bool UrlSearchStatusModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	return false;
}

bool UrlSearchStatusModel::insertRows(int position, int rows, const QModelIndex &index)
{
	return false;
}

bool UrlSearchStatusModel::removeRows(int position, int rows, const QModelIndex &index)
{
	return false;
}
