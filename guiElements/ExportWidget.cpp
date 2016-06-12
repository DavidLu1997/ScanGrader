#include "ExportWidget.hpp"

//Constructor
ExportWidget::ExportWidget(QWidget *parent) {
	QWidget();

	//Widgets
	layout = new QGridLayout();

	//Text
	fileLabel = new QLabel("File Name: ");
	layout->addWidget(fileLabel, 1, 0);
	fileName = new QLineEdit();
	fileName->setText("result");
	layout->addWidget(fileName, 1, 1);
	fileTypeLabel = new QLabel("File Type: ");
	layout->addWidget(fileTypeLabel, 2, 0);
	fileType = new QComboBox();
	fileType->addItem(".CSV");
	fileType->addItem(".TXT");
	layout->addWidget(fileType, 2, 1);

	//Empties
	QWidget *empty1 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty1, 999, 0);
	QWidget *empty2 = new QWidget();
	empty2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty2, 999, 1);

	intro = new QLabel("<h3>Export type:</h3>");
	intro->setTextFormat(Qt::RichText);
	layout->addWidget(intro, 0, 0);
	QWidget *empty5 = new QWidget();
	empty5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty5, 999, 0);
	setLayout(layout);
}

//Destructor
ExportWidget::~ExportWidget() {
	delete layout;
}