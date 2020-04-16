#include "ScanProgress.h"
#include "ui_ScanProgress.h"

ScanProgress::ScanProgress(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::ScanProgress();
	ui->setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);
}

ScanProgress::~ScanProgress()
{
	delete ui;
}
