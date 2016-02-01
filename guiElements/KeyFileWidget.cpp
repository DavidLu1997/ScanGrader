#include "KeyFileWidget.hpp"	 

//Constructor
KeyFileWidget::KeyFileWidget(QUrl URL, QGridLayout *layout, unsigned int row, QWidget *parent) {
	url = new QUrl(URL);
	name = new QLabel(url->fileName());
	layout->addWidget(name, row, 0);
	path = new QLabel(url->toString());
	layout->addWidget(path, row, 1);
	configFile = new QComboBox();
	layout->addWidget(configFile, row, 2);
	remove = new QPushButton("Remove");
	layout->addWidget(remove, row, 3);
	connect(remove, SIGNAL(released()), this, SLOT(setDeleted()));
}

//Destructor
KeyFileWidget::~KeyFileWidget() {
	delete url;
	delete name;
	delete path;
	delete remove;
	delete configFile;
}

//Get URL
QUrl KeyFileWidget::getUrl() {
	return *url;
}

//Get name
QString KeyFileWidget::getName() {
	return url->fileName();
}

//Get url of config file
QUrl KeyFileWidget::getConfigUrl() {
	return configUrls.at(configFile->currentIndex());
}

//Deleted
void KeyFileWidget::setDeleted() {
	deleted = true;
	delete url;
	delete name;
	delete path;
	delete remove;
	delete configFile;
}

//Update config files
void KeyFileWidget::updateConfigFiles(const QList<QUrl> &urls) {
	configUrls = urls;

	configFile->clear();

	for (unsigned int i = 0; i < configUrls.size(); i++) {
		configFile->addItem(configUrls.at(i).fileName());
	}
}