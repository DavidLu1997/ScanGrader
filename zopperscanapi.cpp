#include "zopperscanapi.hpp"
#include <Algorithm>
#include <QDesktopWidget>

//TODO: Redo for ScanFileWidget

ZopperScanAPI::ZopperScanAPI(QWidget *parent)
	: QMainWindow(parent)
{
	//Set up UI
	ui.setupUi(this);

	//Initialize variables
	initVariables();

	//Add navbar to window
	navbar = new NavBar(this);
	navbar->adjustSize();
	setCentralWidget(navbar);

	//Set Size
	QDesktopWidget dw;
	setMinimumSize(dw.width() * 0.5, dw.height() * 0.5);

	//Hide toolbar
	ui.mainToolBar->hide();

	//Hide status bar
	statusBar()->hide();

	//Set Title
	setWindowTitle(tr("ScanGrader v%1").arg(version));
	adjustSize();
}

ZopperScanAPI::~ZopperScanAPI()
{
	delete navbar;
}

//**********Public Functions**********

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
		return imagePaths->at(index);
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
		return keyPaths->at(index);
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
		return configPaths->at(index);
	}
	else {
		return "";
	}
}

//**********Public Slots************

//Refresh UI
void ZopperScanAPI::refresh() {
	adjustSize();
	update();
}

//Calculate results based on current settings
void ZopperScanAPI::calculate() {
	//Configure answer keys
	keys->clear();
	for (unsigned int i = 0; i < keyPaths->size(); i++) {
		keys->push_back(AnalyzeImage(keyPaths->at(i), configPaths->at(useFile->at(i))));
	}

	//Get solutions
	solutions.clear();
	for (unsigned int i = 0; i < keyPaths->size(); i++) {
		solutions.push_back(keys->at(i).getAnswers());
	}

	//Configure images
	images->clear();
	for (unsigned int i = 0; i < imagePaths->size(); i++) {
		images->push_back(AnalyzeImage(imagePaths->at(i), configPaths->at(useFile->at(useKey->at(i)))));
	}

	//Get answers
	answers.clear();
	for (unsigned int i = 0; i < imagePaths->size(); i++) {
		answers.push_back(images->at(i).getAnswers());
	}

	//Get score and percentage score
	score.clear();
	percentScore.clear();
	for (unsigned int i = 0; i < answers.size(); i++) {
		score.push_back(compare(answers[i], solutions[useKey->at(i)]));
		percentScore.push_back((double)score[i] / answers[i].size());
	}
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

//Clear variables
void ZopperScanAPI::clearVariables() {
	images->clear();
	imagePaths->clear();
	useKey->clear();
	configPaths->clear();
	keys->clear();
	keyPaths->clear();
	useFile->clear();
	score.clear();
	percentScore.clear();
	answers.clear();
	solutions.clear();
}

//**********Private Functions**********

//Initialize variables
void ZopperScanAPI::initVariables() {
	images = new std::vector<AnalyzeImage>;
	imagePaths = new std::vector<std::string>;
	useKey = new std::vector<unsigned int>;
	configPaths = new std::vector<std::string>;
	keys = new std::vector<AnalyzeImage>;
	keyPaths = new std::vector<std::string>;
	useFile = new std::vector<unsigned int>;
}

//Connect Image
void ZopperScanAPI::connectImage() {
	//connect(navbar->image->add, SIGNAL(released()), this, SLOT(refresh()));
	
}

//Connect Keys
void ZopperScanAPI::connectKeys() {

}

//Connect Config
void ZopperScanAPI::connectConfig() {

}

//Connect Results
void ZopperScanAPI::connectResults() {

}

//Connect Export
void ZopperScanAPI::connectExport() {

}

//Connect Options
void ZopperScanAPI::connectOptions() {

}


//Compare two int vectors, returns number of equalities
//TODO Rewrite as template
int ZopperScanAPI::compare(std::vector<int> a, std::vector<int> b) {
	//Size equality check
	if (a.size() != b.size()) {
		return -1;
	}
	int result = 0;
	for (unsigned int i = 0; i < a.size(); i++) {
		if (a[i] == b[i]) {
			result++;
		}
	}
	return result;
}