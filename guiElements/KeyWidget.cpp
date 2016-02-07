//Files that need to be included
#include "KeyWidget.hpp"
#include <QtWidgets\QFileDialog>

KeyWidget::KeyWidget(QWidget *parent) {
	QWidget();

	//Initialize layout
	layout = new QGridLayout();

	//Initialize labels
	name = new QLabel("<h3>Name</h3>");
	name->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	name->setTextFormat(Qt::RichText);
	path = new QLabel("<h3>Path</h3>");
	path->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	path->setTextFormat(Qt::RichText);
	config = new QLabel("<h3>Configuration File</h3>");
	config->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	config->setTextFormat(Qt::RichText);

	//Add labels to layout
	layout->addWidget(name, 0, 0);
	layout->addWidget(path, 0, 1);
	layout->addWidget(config, 0, 2);

	//Add empty widget to take up size
	QWidget *empty1 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty1, 999, 0);
	QWidget *empty2 = new QWidget();
	empty2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty2, 999, 1);
	QWidget *empty3 = new QWidget();
	empty3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty3, 999, 2);
	QWidget *empty4 = new QWidget();
	empty4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty4, 999, 3);
	layout->addWidget(empty4, 999, 4);
	QWidget *empty5 = new QWidget();
	empty5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty5, 0, 5);
	QWidget *empty6 = new QWidget();
	empty6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty6, 1, 5);
	QWidget *empty7 = new QWidget();
	empty7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty7, 2, 5);
	QWidget *empty8 = new QWidget();
	empty8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty8, 3, 5);

	layout->setColumnStretch(0, 10);
	layout->setColumnStretch(1, 10);
	layout->setColumnStretch(2, 10);
	layout->setColumnStretch(3, 10);
	layout->setColumnStretch(4, 10);
	layout->setColumnStretch(5, 100);

	//Initialize push button and add it to layout
	addKey = new QPushButton("Add Answer Key");
	addKey->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(addKey, 1000, 0);
	//Connect add button
	connect(addKey, SIGNAL(released()), this, SLOT(addFiles()));

	//Initialize refresh button and add it to layout
	refreshButton = new QPushButton("Refresh");
	refreshButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(refreshButton, 1000, 1);
	//Connect refresh button
	connect(refreshButton, SIGNAL(released()), this, SLOT(refresh()));

	//Create removeAll button
	removeAll = new QPushButton("Remove All");
	removeAll->setEnabled(false);
	removeAll->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//Connect removeAll button
	QPushButton::connect(removeAll, SIGNAL(released()), this, SLOT(removeAllEntries()));
	//Add removeAll button to layout
	layout->addWidget(removeAll, 1000, 2);

	setLayout(layout);
}

//Destructor
KeyWidget::~KeyWidget() {
	delete layout;
	delete name;
	delete path;
	delete addKey;
	keyFiles.clear();
}

void KeyWidget::addFiles() {
	//Opens file dialog for user to pick file
	QList<QUrl> files = QFileDialog::getOpenFileUrls(this, "Open Answer Key", QUrl("/"), "Image Files (*.bmp)");

	for (unsigned int i = 0; i < files.size(); i++) {
		keyFiles.push_back(new KeyFileWidget(files.at(i), layout, keyFiles.size() + 1));
		connect(keyFiles.at(keyFiles.size() - 1)->remove, SIGNAL(released()), this, SLOT(refresh()));
	}
	//When at least one file is added, removeAll button becomes enabled
	removeAll->setEnabled(true);
}

void KeyWidget::removeAllEntries() {
	//Calls delete function of each keyFile entry
	for (int i = 0; i < keyFiles.size(); i++) {
		keyFiles.at(i)->setDeleted();
		delete keyFiles.at(i);
	}
	//Disable removeAll button, clear vector
	removeAll->setEnabled(false);
	keyFiles.clear();
}

void KeyWidget::refresh() {
	//Calls update method to refresh UI
	update();
}

void KeyWidget::updateConfig(const QList<QUrl> &urls) {
	//Loops through keyFiles
	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		//If keyFile at i is null, erase it from the vector
		if (keyFiles.at(i)->deleted) {
			keyFiles.erase(keyFiles.begin() + i);
			i--;
			continue;
		}
		//Call update method 
		keyFiles.at(i)->updateConfigFiles(urls);
	}
}

std::vector<std::string> KeyWidget::getFileNames() {
	std::vector<std::string> fileNames;
	//Loops through keyFiles
	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		//If keyFile at i is null, erase it from the vector
		if (keyFiles.at(i)->deleted) {
			keyFiles.erase(keyFiles.begin() + i);
			i--;
			continue;
		}
		//Gets its name and adds it to the fileName vector
		fileNames.push_back(keyFiles.at(i)->getName().toStdString());
	}
	//Return vector of fileNames
	return fileNames;
}

QList<QUrl> KeyWidget::getKeyUrls() {
	QList<QUrl> urls;
	//Loops though keyFiles
	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		//If keyFile at i is null, erase it from the vector
		if (keyFiles.at(i)->deleted) {
			keyFiles.erase(keyFiles.begin() + i);
			i--;
			continue;
		}
		//Gets the URL from keyFiles and adds it to the QList vector
		urls.push_back(keyFiles.at(i)->getUrl());
	}
	//Return Qlist of urls
	return urls;
}

QList<QUrl> KeyWidget::getConfigUrls() {
	QList<QUrl> urls;
	//Loops through keyFiles
	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		//If keyFile at i is null, erase it from the vector
		if (keyFiles.at(i)->deleted) {
			keyFiles.erase(keyFiles.begin() + i);
			i--;
			continue;
		}
		//Gets ConfigUrl from keyFiles and adds it to the QList vector
		urls.push_back(keyFiles.at(i)->getConfigUrl());
	}
	//Return QList vector
	return urls;
}

QUrl KeyWidget::getFileUrl(std::string name) {
	//Simple search
	//TODO: Optimize
	//Loop through keyFiles
	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		//If keyFile at i is null, erase it from the vector
		if (keyFiles.at(i)->deleted) {
			keyFiles.erase(keyFiles.begin() + i);
			i--;
			continue;
		}
		//If name of keyFiles at i matches search name, then return
		if (keyFiles.at(i)->getName().toStdString() == name) {
			return keyFiles.at(i)->getUrl();
		}
	}
	//Return QUrl
	return QUrl();
}