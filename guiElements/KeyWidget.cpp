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
	empty3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty4, 999, 3);

	//Initialize push button
	addKey = new QPushButton("Add Answer Key");
	layout->addWidget(addKey, 1000, 0);
	connect(addKey, SIGNAL(released()), this, SLOT(addFiles()));

	setLayout(layout);
}

KeyWidget::~KeyWidget() {
	delete layout;
	delete name;
	delete path;
	delete addKey;
}

void KeyWidget::addFiles() {
	QList<QUrl> files = QFileDialog::getOpenFileUrls(this, "Open Answer Key", QUrl("/"), "Image Files (*.bmp)");

	for (unsigned int i = 0; i < files.size(); i++) {
		keyFiles.push_back(new KeyFileWidget(files.at(i), layout, keyFiles.size() + 1));
		connect(keyFiles.at(keyFiles.size() - 1)->remove, SIGNAL(released()), this, SLOT(refresh()));
	}
}

void KeyWidget::refresh() {
	update();
}

void KeyWidget::updateConfig(const QList<QUrl> &urls) {
	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		keyFiles.at(i)->updateConfigFiles(urls);
	}
}

std::vector<std::string> KeyWidget::getFileNames() {
	std::vector<std::string> fileNames;

	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		fileNames.push_back(keyFiles.at(i)->getName().toStdString());
	}

	return fileNames;
}

QList<QUrl> KeyWidget::getFileUrls() {
	QList<QUrl> urls;

	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		urls.push_back(keyFiles.at(i)->getUrl());
	}
	return urls;
}

QUrl KeyWidget::getFileUrl(std::string name) {
	//Simple search
	//TODO: Optimize
	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		if (keyFiles.at(i)->getName().toStdString() == name) {
			return keyFiles.at(i)->getUrl();
		}
	}

	return QUrl();
}