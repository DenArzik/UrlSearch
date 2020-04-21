#include "SearchProgress.h"
#include "ui_ScanProgress.h"

#include "UrlSearchStatusModel.h"
#include "Application.h"
#include "SearchManager.h"

SearchProgress::SearchProgress(const Application *main_window, QWidget *parent)
	: QWidget(parent)
	, m_mainWindow(main_window)
{
	ui = new Ui::ScanProgress();
	ui->setupUi(this);

	init();
}

SearchProgress::~SearchProgress()
{
	delete ui;
}

void SearchProgress::init()
{
	setAttribute(Qt::WA_DeleteOnClose);

	initTable();

	mgr = new SearchManager(m_mainWindow, model, this);
}

void SearchProgress::initTable()
{
	model = new UrlSearchStatusModel(this);
	ui->tableView->setModel(model);
}
