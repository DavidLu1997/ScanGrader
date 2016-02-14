#include "ExportWidget.hpp"

//Constructor
ExportWidget::ExportWidget(QWidget *parent) {
	QWidget();

	//Widgets
	fileWidget = new QWidget();
	fileLayout = new QGridLayout();

	//Text
	fileLabel = new QLabel("File Name: ");
	fileLayout->addWidget(fileLabel, 0, 0);
	fileName = new QLineEdit();
	fileName->setText("result");
	fileLayout->addWidget(fileName, 0, 1);
	fileTypeLabel = new QLabel("File Type: ");
	fileLayout->addWidget(fileTypeLabel, 1, 0);
	fileType = new QComboBox();
	fileType->addItem(".CSV");
	fileType->addItem(".TXT");
	fileLayout->addWidget(fileType, 1, 1);

	//Empties
	QWidget *empty1 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	fileLayout->addWidget(empty1, 999, 0);
	QWidget *empty2 = new QWidget();
	empty2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	fileLayout->addWidget(empty2, 999, 1);

	fileWidget->setLayout(fileLayout);

	//Main widget
	layout = new QGridLayout();

	intro = new QLabel("<h3>Export type:</h3>");
	intro->setTextFormat(Qt::RichText); 
	layout->addWidget(intro, 0, 0);
	layout->addWidget(fileWidget, 2, 0);
	QWidget *empty5 = new QWidget();
	empty5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty5, 999, 0);
	setLayout(layout);
}

//Destructor
ExportWidget::~ExportWidget() {
	delete layout;
}