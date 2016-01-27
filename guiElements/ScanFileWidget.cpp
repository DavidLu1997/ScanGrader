#include "ScanFileWidget.hpp"

//Constructor
ScanFileWidget::ScanFileWidget(QGridLayout *layout, unsigned int r, QWidget *parent) {
	//Initialize path
	path = new QUrl();
	file = new QLabel();

	//Initialize answer key
	answerKey = new QComboBox();

	//Initialize config file
	configFile = new QComboBox();

	//Initialize row
	row = r;

	//Add widgets to header
	layout->addWidget(file, row, 0);
	layout->addWidget(answerKey, row, 1);
	layout->addWidget(configFile, row, 2);
}

//Destructor
ScanFileWidget::~ScanFileWidget() {
	delete file;
	delete configFile;
	delete answerKey;
}

//**********Public Functions**********

//Update path
void ScanFileWidget::updatePath(const QUrl &url) {
	*path = url;
	file->setText(path->fileName());
}

//Update config file list
void ScanFileWidget::updateConfigFile(const std::vector<std::string> &configFiles) {
	configFile->clear();

	for (unsigned int i = 0; i < configFiles.size(); i++) {
		configFile->addItem(QString(configFiles[i].c_str()));
	}
}

//Update answer keys list
void ScanFileWidget::updateAnswerKeys(const std::vector<std::string> &answerKeys) {
	answerKey->clear();

	for (unsigned int i = 0; i < answerKeys.size(); i++) {
		answerKey->addItem(QString(answerKeys[i].c_str()));
	}
}

//Get path
QUrl ScanFileWidget::getPath() {
	return *path;
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