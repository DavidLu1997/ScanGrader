#include "ImageWidget.hpp"

//Constructor
ImageWidget::ImageWidget(QWidget *parent) {
	//Set layout to BoxLayout
	layout = new QGridLayout();
	setLayout(layout);

	fileLabel = new QLabel("Image Path");
	configLabel = new QLabel("Configuration File");
	answerLabel = new QLabel("Answer Key");
	layout->addWidget(fileLabel, 1, 0);
	layout->addWidget(configLabel, 1, 1);
	layout->addWidget(answerLabel, 1, 2);

	//Create menu bar
	createMenu();

	//Initialize selected
	selected = -1;

	//Add menu to layout
	layout->addWidget(menuBar, 0, 0);

	//Connect buttons
	connectButtons();

	//Refresh
	refresh();
}

//Destructor
ImageWidget::~ImageWidget() {
	delete layout;
	delete menuBar;
}

//**********Public Functions**********

//Refresh UI
void ImageWidget::refresh() {
	layout->update();
	update();
}

//**********Private Slots**********

//Add ScanFileWidget
void ImageWidget::addScanFileWidget() {
	scanFiles.push_back(new ScanFileWidget(layout, scanFiles.size() + 2));
	scanFiles.at(scanFiles.size() - 1)->updatePath("SAMPLE #" + std::to_string(scanFiles.size()));

	//Hide config file
	//scanFiles.at(scanFiles.size() - 1)->hideConfigFile(true);

	selected = scanFiles.size() - 1;
	
	refresh();
}

//**********Private Functions**********

//Create context menu
void ImageWidget::createMenu() {
	//Create buttons
	add = new QPushButton("Add Scan Sheet");

	//MenuBar and layout
	menuBar = new QWidget();
	menuLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	menuBar->setLayout(menuLayout);

	//Add buttons to layout
	menuLayout->addWidget(add);
}

//Connect button signals to slots
void ImageWidget::connectButtons() {
	QPushButton::connect(add, SIGNAL(released()), this, SLOT(addScanFileWidget()));
}