#pragma once

#include <QWidget>
namespace Ui { class ScanProgress; };

class UrlSearchStatusModel;

class ScanProgress : public QWidget
{
	Q_OBJECT

public:
	ScanProgress(QWidget *parent = Q_NULLPTR);
	~ScanProgress();

private:
	Ui::ScanProgress *ui;

	void init();
	void initTable();

	UrlSearchStatusModel *model;
};

