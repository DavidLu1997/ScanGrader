#include "zopperscanapi.hpp"
#include <Algorithm>

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
	//Go through vector
	for (unsigned int i = 0; i < imagePaths->size(); i++) {
		if (imagePaths->at(i) == name) {
			return i;
		}
	}

	return -1;
}

//Image get string from index
std::string ZopperScanAPI::getImage(unsigned int index) {
	if (index >= 0 && index < imagePaths->size()) {
		return imagePaths->at(i);
	}
	else {
		return "";
	}
}

//Key get index from string
int ZopperScanAPI::getKey(std::string name) {
	//Go through vector
	for (unsigned int i = 0; i <keyPaths->size(); i++) {
		if (keyPaths->at(i) == name) {
			return i;
		}
	}
	return -1;
}

//Key get string from index
std::string ZopperScanAPI::getKey(unsigned int index) {
	if (index >= 0 && index < keyPaths->size()) {
		return keyPaths->at(i);
	}
	else {
		return "";
	}
}

//Config get index from string
int ZopperScanAPI::getConfig(std::string name) {
	//Go through vector
	for (unsigned int i = 0; i < configPaths->size(); i++) {
		if (configPaths->at(i) == name) {
			return i;
		}
	}
	return -1;
}

//Config get string from index
std::string ZopperScanAPI::getConfig(unsigned int index) {
	if (index >= 0 && index < keyPaths->size()) {
		return configPaths->at(i);
	}
	else {
		return "";
	}
}

//**********Public Slots************

//Calculate results based on current settings
void ZopperScanAPI::calculate() {

}

//Add image
void ZopperScanAPI::addImage(std::string name) {
	//If the name is not blank
	//Assume proper validation
	if (name != "") {
		imagePaths->push_back(name);
	}
}

//Remove image by name
void ZopperScanAPI::removeImage(std::string name) {
	//Get index of name
	int index = getImage(name);
	//Erase
	removeImage(index);
}

//Remove image by index
void ZopperScanAPI::removeImage(unsigned int index) {
	imagePaths->erase(imagePaths->begin() + index);
}

//Swap image, swaps two indexes of images
void ZopperScanAPI::swapImage(unsigned int a, unsigned int b) {
	//Error check
	if ((a >= 0 && a < imagePaths->size()) && (b >= 0 && b < imagePaths->size()) && a != b) {
		//Swap images
		iter_swap(imagePaths->begin() + a, imagePaths->begin() + b);
		//Swap useFile
		iter_swap(useFile->begin() + a, useFile->begin() + b);
		//Swap useKey
		iter_swap(useKey->begin() + a, useKey->begin() + b);
	}
}

//Add answer key
void ZopperScanAPI::addKey(std::string name) {
	//If the name is not blank
	//Assume proper validation
	if (name != "") {
		keyPaths->push_back(name);
	}
}

//Remove answer key
void ZopperScanAPI::removeKey(std::string name) {
	//Get index of name
	int index = getKey(name);
	//Erase
	removeKey(index);
}

//Remove answer key by index
void ZopperScanAPI::removeKey(unsigned int index) {
	keyPaths->erase(keyPaths->begin() + index);
}

//Add configuration file
void ZopperScanAPI::addConfig(std::string name) {
	//If the name is not blank
	//Assume proper validation
	if (name != "") {
		configPaths->push_back(name);
	}
}

//Remove configuration file
void ZopperScanAPI::removeConfig(std::string name) {
	//Get index of name
	int index = getConfig(name);
	//Erase
	removeConfig(index);
}

//Remove configuration file by index
void ZopperScanAPI::removeConfig(unsigned int index) {
	configPaths->erase(keyPaths->begin() + index);
}