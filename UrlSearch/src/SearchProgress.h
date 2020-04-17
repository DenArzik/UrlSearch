#pragma once

#include <QWidget>
namespace Ui { class ScanProgress; };

class UrlSearchStatusModel;
class Application;

class SearchProgress : public QWidget
{
	Q_OBJECT

public:
	SearchProgress(const Application* mainWindow, QWidget *parent = Q_NULLPTR);
	~SearchProgress();

private:
	Ui::ScanProgress *ui;

	const Application *m_mainWindow;

	void init();
	void initTable();

	UrlSearchStatusModel *model;
};

