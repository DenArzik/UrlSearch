#pragma once

#include <QAbstractTableModel>

static struct UrlSearchStatus
{
	QString m_errorStr;
	bool m_downloaded;
	bool m_scanned;
	bool m_textFound;
};

class UrlSearchStatusModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	UrlSearchStatusModel(QObject *parent);
	
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex()) override;
	bool removeRows(int position, int rows, const QModelIndex& index = QModelIndex()) override;

private:
	std::map<QString, UrlSearchStatus> url_map;

	static QString formatStatus(const UrlSearchStatus &itm);

public:
	void insertUrl(const QString &url);
	void setUrlError(const QString &url, const QString &error);
	void setUrlDownloaded(const QString &url, bool downloaded);
	void setUrlScanned(const QString &url, bool scanned);
	void setUrlTextFound(const QString &url, bool found);
	void setUrl(const QString &url, const QString &error="", bool downloaded=false, bool scanned=false, bool found=false);

signals:
	void dataUpdated();

};
