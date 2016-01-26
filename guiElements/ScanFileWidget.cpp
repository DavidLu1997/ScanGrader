#include "ScanFileWidget.hpp"

//Constructor
ScanFileWidget::ScanFileWidget(unsigned int r, QWidget *parent) {
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

	//Initialize layout
	layout = new QGridLayout();

	//Always initialize
	//TODO Refactor
	fileLabel = new QLabel("Image Path");
	configLabel = new QLabel("Configuration File");
	answerLabel = new QLabel("Answer Key");

	//Add headers if row is 0
	if (row == 0) {
		layout->addWidget(fileLabel, 0, 0);
		layout->addWidget(configLabel, 0, 1);
		layout->addWidget(answerLabel, 0, 2);
		row++;
	}

	layout->addWidget(path, row, 0);
	layout->addWidget(answerKey, row, 1);
	layout->addWidget(configFile, row, 2);

	setLayout(layout);
}

//Destructor
ScanFileWidget::~ScanFileWidget() {

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

//Hide config file
void ScanFileWidget::hideConfigFile(bool b) {
	if (b) {
		configFile->hide();
		if (row == 1) {
			configLabel->hide();
		}
	}
	else {
		configFile->show();
		if (row == 1) {
			configLabel->show();
		}
	}
}

//Hide answer key
void ScanFileWidget::hideAnswerKey(bool b) {
	if (b) {
		answerKey->hide();
		if (row == 1) {
			answerLabel->show();
		}
	}
	else {
		answerKey->show();
		if (row == 1) {
			answerLabel->hide();
		}
	}
}

//Select this
void ScanFileWidget::selectThis(bool b) {
	if (b) {
		//TODO: Highlight
	}
	else {
		//TODO: Return to normal
	}
}