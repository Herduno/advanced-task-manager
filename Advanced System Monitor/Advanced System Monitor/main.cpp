#include "advancedsystemmonitor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AdvancedSystemMonitor w;
	w.show();
	return a.exec();
}
