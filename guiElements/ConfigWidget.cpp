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

	//Initialize push button
	addConfig = new QPushButton("Add Configuration File");
	layout->addWidget(addConfig, 1000, 0);
	connect(addConfig, SIGNAL(released()), this, SLOT(addFiles()));

	setLayout(layout);
}

ConfigWidget::~ConfigWidget() {
	delete layout;
	delete name;
	delete path;
	delete addConfig;
}

void ConfigWidget::addFiles() {
	QList<QUrl> files = QFileDialog::getOpenFileUrls(this, "Open Configuration File", QUrl("/"), "Configuration Files (*.ini)");

	for (unsigned int i = 0; i < files.size(); i++) {
		configFiles.push_back(new ConfigFileWidget(files.at(i), layout, configFiles.size() + 1));
		connect(configFiles.at(configFiles.size() - 1)->remove, SIGNAL(released()), this, SLOT(refresh()));
	}
}

void ConfigWidget::refresh() {
	update();
}

std::vector<std::string> ConfigWidget::getFileNames() {
	std::vector<std::string> fileNames;

	for (unsigned int i = 0; i < configFiles.size(); i++) {
		fileNames.push_back(configFiles.at(i)->getName().toStdString());
	}

	return fileNames;
}

QList<QUrl> ConfigWidget::getFileUrls() {
	QList<QUrl> urls;

	for (unsigned int i = 0; i < configFiles.size(); i++) {
		urls.push_back(configFiles.at(i)->getUrl());
	}
	return urls;
}

QUrl ConfigWidget::getFileUrl(std::string name) {
	//Simple search
	//TODO: Optimize
	for (unsigned int i = 0; i < configFiles.size(); i++) {
		if (configFiles.at(i)->getName().toStdString() == name) {
			return configFiles.at(i)->getUrl();
		}
	}

	return QUrl();
}