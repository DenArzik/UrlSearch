#pragma once

#include <QWidget>
namespace Ui { class ScanProgress; };

class ScanProgress : public QWidget
{
	Q_OBJECT

public:
	ScanProgress(QWidget *parent = Q_NULLPTR);
	~ScanProgress();

private:
	Ui::ScanProgress *ui;
};
