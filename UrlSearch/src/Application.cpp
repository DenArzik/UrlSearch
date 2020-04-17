#include "Application.h"

#include <QThreadPool>
#include <QRegularExpressionValidator>

#include <QUrl>
#include <QDebug>

#include "SearchProgress.h"

Application::Application(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	init();
}

void Application::init()
{
	connect(ui.bt_go, &QPushButton::clicked, this, &Application::go_pressed);

	initForm();
}

void Application::initForm()
{
	ui.sb_max_threads->setValue(getIdealThreadCount());
	ui.sb_max_threads->setMaximum(getMaxThreadCount());
}

int Application::getIdealThreadCount() const
{
	return QThread::idealThreadCount();
}

int Application::getMaxThreadCount() const
{
	return QThreadPool::globalInstance()->maxThreadCount();
}

QString Application::getUrl() const
{
	return ui.l_url->text();
}

QString Application::getSearchText() const
{
	return ui.l_search_text->text();
}

int Application::getThreadCount() const
{
	return ui.sb_max_threads->value();
}

int Application::getMaxUrlCount() const
{
	return ui.sb_max_url_count->value();
}


void Application::go_pressed()
{
	this->setEnabled(false);

	SearchProgress *scanProgress = new SearchProgress(this, nullptr);
	scanProgress->show();
	connect(scanProgress, &SearchProgress::destroyed, this, [this]() { this->setEnabled(true); });
}