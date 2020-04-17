#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Application.h"

class Application : public QMainWindow
{
	Q_OBJECT

public:
	Application(QWidget *parent = Q_NULLPTR);

private:
	Ui::ApplicationClass ui;

	void init();

	void initForm();

	int getIdealThreadCount() const;
	int getMaxThreadCount() const;

private slots:
	void go_pressed();

public:
	QString getUrl() const;
	QString getSearchText() const;
	int getThreadCount() const;
	int getMaxUrlCount() const;


};
