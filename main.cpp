#include "scangrader.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ScanGrader w;
	w.show();
	return a.exec();
}
