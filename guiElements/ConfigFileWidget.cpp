#include "ConfigFileWidget.hpp"	 

//Constructor
ConfigFileWidget::ConfigFileWidget(QUrl URL, QGridLayout *layout, unsigned int row, QWidget *parent) {
	url = URL;
	name = new QLabel(url.fileName());
	layout->addWidget(name, row, 0);
	path = new QLabel(url.toString());
	layout->addWidget(path, row, 1);
	remove = new QPushButton("Remove");
	layout->addWidget(remove, row, 2);
	connect(remove, SIGNAL(released()), this, SLOT(setDeleted()));
}

//Destructor
ConfigFileWidget::~ConfigFileWidget() {
	delete name;
	delete path;
	delete remove;
}

void ConfigFileWidget::setDeleted() {
	delete name;
	delete path;
	delete remove;
	deleted = true;
}

//Get URL
QUrl ConfigFileWidget::getUrl() {
	return url;
}

//Get name
QString ConfigFileWidget::getName() {
	return url.fileName();
}