#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_advancedsystemmonitor.h"

class AdvancedSystemMonitor : public QMainWindow
{
	Q_OBJECT

public:
	AdvancedSystemMonitor(QWidget *parent = Q_NULLPTR);

private:
	Ui::AdvancedSystemMonitorClass ui;
};
