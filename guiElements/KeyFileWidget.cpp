//Include header file for function definitions
#include "KeyFileWidget.hpp"

//Constructor
KeyFileWidget::KeyFileWidget(QUrl URL, QGridLayout *layout, unsigned int row, QWidget *parent) {
	//Creating the various UI elements and adding them to the layout
	url = new QUrl(URL);
	name = new QLabel(url->fileName());
	layout->addWidget(name, row, 0);
	path = new QLabel(url->toLocalFile());
	layout->addWidget(path, row, 1);
	configFile = new QComboBox();
	layout->addWidget(configFile, row, 2);

	//Initialize view button
	view = new QPushButton("View");
	connect(view, SIGNAL(released()), this, SLOT(previewImage()));
	layout->addWidget(view, row, 3);

	//Remove button
	remove = new QPushButton("Remove");
	connect(remove, SIGNAL(released()), this, SLOT(setDeleted()));
	layout->addWidget(remove, row, 4);

	//Connecting remove button
	connect(remove, SIGNAL(released()), this, SLOT(setDeleted()));
}

//Destructor
KeyFileWidget::~KeyFileWidget() {
}

//**********Public Functions**********

//Get URL
QUrl KeyFileWidget::getUrl() {
	return *url;
}

//Get name
QString KeyFileWidget::getName() {
	return url->toLocalFile();
}

//Get url of config file
QUrl KeyFileWidget::getConfigUrl() {
	return configUrls.at(configFile->currentIndex());
}

//Update config files
void KeyFileWidget::updateConfigFiles(const QList<QUrl> &urls) {
	configUrls = urls;
	configFile->clear();

	for (unsigned int i = 0; i < configUrls.size(); i++) {
		configFile->addItem(configUrls.at(i).fileName());
	}
}

//**********Public Slots**********

//Deleted
void KeyFileWidget::setDeleted() {
	if (deleted)
		return;
	deleted = true;
	delete url;
	delete name;
	delete path;
	delete remove;
	delete view;
	delete configFile;
}

//Show preview
void KeyFileWidget::previewImage() {
	imagePreview = new ImagePreview(getUrl());
}