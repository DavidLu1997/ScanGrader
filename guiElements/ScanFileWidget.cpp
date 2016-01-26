#include "ScanFileWidget.hpp"

//Constructor
ScanFileWidget::ScanFileWidget(QGridLayout *layout, unsigned int r, QWidget *parent) {
	//Initialize label
	path = new QLabel("");

	//Initialize answer key
	answerKey = new QComboBox();

	//Initialize config file
	configFile = new QComboBox();

	//Initialize buttons
	initButtons();

	//Initialize row
	row = r;

	//TESTING ONLY
	answerKey->addItem("Answer1");
	answerKey->addItem("Answer2");
	configFile->addItem("Config1");
	configFile->addItem("Config2");

	//Add headers if row is 0
	
	layout->setRowMinimumHeight(row, 5);

	layout->addWidget(path, row, 0);
	layout->addWidget(answerKey, row, 1);
	layout->addWidget(configFile, row, 2);
	layout->addWidget(buttons, row, 3);
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

//**********Private Functions**********

//Initialize Buttons
void ScanFileWidget::initButtons() {
	//Initialize button widget
	buttons = new QWidget();

	//Initialize button layout
	buttonLayout = new QBoxLayout(QBoxLayout::LeftToRight);

	//Initialize remove button
	removeButton = new QPushButton("Remove");

	//Initialize up button
	upButton = new QPushButton("Up");

	//Initialize down button
	downButton = new QPushButton("Down");

	//Add buttons to layout
	buttonLayout->addWidget(upButton);
	buttonLayout->addWidget(downButton);
	buttonLayout->addWidget(removeButton);

	//Set Layout
	buttons->setLayout(buttonLayout);
}
