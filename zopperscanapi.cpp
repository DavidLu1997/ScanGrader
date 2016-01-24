#include "zopperscanapi.hpp"

ZopperScanAPI::ZopperScanAPI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Add navbar to window
	navbar = new NavBar();
	setCentralWidget(navbar);

	//Hide toolbar
	ui.mainToolBar->hide();

	//Hide status bar
	statusBar()->hide();

	//Set Title
	setWindowTitle(tr("ScanGrader v%1").arg(version));
}

ZopperScanAPI::~ZopperScanAPI()
{
	delete navbar;
}

//**********Public Functions**********

//Refresh UI
void ZopperScanAPI::refresh() {

}


//Image get index from string
int ZopperScanAPI::getImage(std::string name) {
	return -1;
}

//Image get string from index
std::string ZopperScanAPI::getImage(unsigned int index) {
	return "";
}

//Key get index from string
int ZopperScanAPI::getKey(std::string name) {
	return -1;
}

//Key get string from index
std::string ZopperScanAPI::getKey(unsigned int index) {
	return "";
}

//Config get index from string
int ZopperScanAPI::getConfig(std::string name) {
	return -1;
}

//Config get string from index
std::string ZopperScanAPI::getConfig(unsigned int index) {
	return "";
}

//**********Public Slots************

//Add image
void ZopperScanAPI::addImage(std::string name) {

}

//Remove image by name
void ZopperScanAPI::removeImage(std::string name) {

}

//Remove image by index
void ZopperScanAPI::removeImage(unsigned int index) {

}

//Swap image, swaps two indexes of images
void ZopperScanAPI::swapImage(unsigned int a, unsigned int b) {

}

//Add answer key
void ZopperScanAPI::addKey(std::string name) {

}

//Remove answer key
void ZopperScanAPI::removeKey(std::string name) {

}

//Remove answer key by index
void ZopperScanAPI::removeKey(unsigned int index) {

}

//Add configuration file
void ZopperScanAPI::addConfig(std::string name) {

}

//Remove configuration file
void ZopperScanAPI::removeConfig(std::string name) {

}

//Remove configuration file by index
void ZopperScanAPI::removeConfig(unsigned int index) {

}

//Calculate results based on current settings
void ZopperScanAPI::calculate() {

}