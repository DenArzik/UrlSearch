#include "ScanProgress.h"
#include "ui_ScanProgress.h"

#include "UrlSearchStatusModel.h"
#include "Application.h"

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
}

void SearchProgress::initTable()
{
	model = new UrlSearchStatusModel(this);
	ui->tableView->setModel(model);
}
