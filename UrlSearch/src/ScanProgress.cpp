#include "ScanProgress.h"
#include "ui_ScanProgress.h"



#include "UrlSearchStatusModel.h"

ScanProgress::ScanProgress(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::ScanProgress();
	ui->setupUi(this);

	init();
}

ScanProgress::~ScanProgress()
{
	delete ui;
}

void ScanProgress::init()
{
	setAttribute(Qt::WA_DeleteOnClose);

	initTable();
}

void ScanProgress::initTable()
{
	model = new UrlSearchStatusModel(this);
	ui->tableView->setModel(model);
}
