#include "ScanFileWidget.hpp"

//Constructor
ScanFileWidget::ScanFileWidget(QGridLayout *layout, unsigned int r, QWidget *parent) {
	//Initialize label
	path = new QLabel("");

	//Initialize answer key
	answerKey = new QComboBox();

	//Initialize config file
	configFile = new QComboBox();

	//Initialize row
	row = r;

	//TESTING ONLY
	answerKey->addItem("Answer1");
	answerKey->addItem("Answer2");
	configFile->addItem("Config1");
	configFile->addItem("Config2");

	//Add widgets to header
	layout->addWidget(path, row, 0);
	layout->addWidget(answerKey, row, 1);
	layout->addWidget(configFile, row, 2);
}

//Destructor
ScanFileWidget::~ScanFileWidget() {
	delete path;
	delete configFile;
	delete answerKey;
}

//**********Public Functions**********

//Update path
void ScanFileWidget::updatePath(std::string str) {
	path->setText(QString(str.c_str()));
}

//Update config file list
void ScanFileWidget::updateConfigFile(std::vector<std::string> configFiles) {
	configFile->clear();

	for (unsigned int i = 0; i < configFiles.size(); i++) {
		configFile->addItem(QString(configFiles[i].c_str()));
	}
}

//Update answer keys list
void ScanFileWidget::updateAnswerKeys(std::vector<std::string> answerKeys) {
	answerKey->clear();

	for (unsigned int i = 0; i < answerKeys.size(); i++) {
		answerKey->addItem(QString(answerKeys[i].c_str()));
	}
}

//Get path
std::string ScanFileWidget::getPath() {
	return path->text().toStdString();
}

//Get selected config file
std::string ScanFileWidget::getConfigFile() {
	return configFile->currentText().toStdString();
}

//Get selected answer key
std::string ScanFileWidget::getAnswerKey() {
	return answerKey->currentText().toStdString();
}

//**********Private Functions**********