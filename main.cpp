#include "zopperscanapi.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ZopperScanAPI w;
	w.show();
	return a.exec();
}
