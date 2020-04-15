#include "Application.h"

#include <QThreadPool>
#include <QRegularExpressionValidator>

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


void Application::go_pressed()
{

}