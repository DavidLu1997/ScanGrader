#ifndef ZOPPERSCANAPI_H
#define ZOPPERSCANAPI_H

#include <QtWidgets/QMainWindow>
#include "ui_zopperscanapi.h"

class ZopperScanAPI : public QMainWindow
{
	Q_OBJECT

public:
	ZopperScanAPI(QWidget *parent = 0);
	~ZopperScanAPI();

private:
	Ui::ZopperScanAPIClass ui;
};

#endif // ZOPPERSCANAPI_H
