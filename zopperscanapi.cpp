#include "zopperscanapi.hpp"

ZopperScanAPI::ZopperScanAPI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

ZopperScanAPI::~ZopperScanAPI()
{
	//Delete answer key
	free(key);

	//Clear images
	images.clear();
}
