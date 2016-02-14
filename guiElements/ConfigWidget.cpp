#include "ConfigWidget.hpp"
#include <QtWidgets\QFileDialog>

ConfigWidget::ConfigWidget(QWidget *parent) {
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

	//Add labels to layout
	layout->addWidget(name, 0, 0);
	layout->addWidget(path, 0, 1);

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
	empty4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty4, 0, 3);
	QWidget *empty5 = new QWidget();
	empty5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty5, 1, 3);
	QWidget *empty6 = new QWidget();
	empty6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty6, 2, 3);

	layout->setColumnStretch(0, 10);
	layout->setColumnStretch(1, 10);
	layout->setColumnStretch(2, 0);
	layout->setColumnStretch(3, 100);

	//Initialize push button
	addConfig = new QPushButton("Add Configuration File");
	addConfig->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(addConfig, 1000, 0);
	connect(addConfig, SIGNAL(released()), this, SLOT(addFiles()));

	//Create removeAll button
	removeAll = new QPushButton("Remove All");
	removeAll->setEnabled(false);
	removeAll->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//Connect removeAll button
	QPushButton::connect(removeAll, SIGNAL(released()), this, SLOT(removeAllEntries()));
	//Add removeAll button to layout
	layout->addWidget(removeAll, 1000, 1);

	setLayout(layout);
}

//Destructor
ConfigWidget::~ConfigWidget() {
	delete layout;
	delete name;
	delete path;
	delete addConfig;
	configFiles.clear();
}

//**********Public Functions**********

//Get all file names
std::vector<std::string> ConfigWidget::getFileNames() {
	std::vector<std::string> fileNames;

	for (unsigned int i = 0; i < configFiles.size(); i++) {
		fileNames.push_back(configFiles.at(i)->getName().toStdString());
	}

	return fileNames;
}

//Get all file URLs
QList<QUrl> ConfigWidget::getFileUrls() {
	QList<QUrl> urls;

	for (unsigned int i = 0; i < configFiles.size(); i++) {
		if (configFiles.at(i)->deleted) {
			configFiles.erase(configFiles.begin() + i);
			i--;
			continue;
		}
		urls.push_back(configFiles.at(i)->getUrl());
	}
	return urls;
}

//**********Public Slots**********

//Update display
void ConfigWidget::refresh() {
	update();
}

//**********Private Slots**********
//Add files
void ConfigWidget::addFiles() {
	//New file dialog, taking ini files
	QList<QUrl> files = QFileDialog::getOpenFileUrls(this, "Open Configuration File", QUrl("/"), "Configuration Files (*.ini)");

	//Add to configFiles
	for (unsigned int i = 0; i < files.size(); i++) {
		configFiles.push_back(new ConfigFileWidget(files.at(i), layout, configFiles.size() + 1));
		connect(configFiles.at(configFiles.size() - 1)->remove, SIGNAL(released()), this, SLOT(refresh()));
	}

	//Enable removing
	removeAll->setEnabled(true);
}

//Remove all entries
void ConfigWidget::removeAllEntries() {
	//Call delete function of each configFileWidget
	for (int i = 0; i < configFiles.size(); i++) {
		configFiles.at(i)->setDeleted();
		delete configFiles.at(i);
	}
	//Clear vector and disable button
	configFiles.clear();
	removeAll->setEnabled(false);
}
