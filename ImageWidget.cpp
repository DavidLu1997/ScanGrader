#include "ImageWidget.hpp"

//TODO: Make SIGNALs for buttons
//Signal outputs must match slot inputs

//Constructor
ImageWidget::ImageWidget(QWidget *parent) {
	//Set layout to BoxLayout
	layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	setLayout(layout);

	//Create image list
	createImageList();

	//Add imageList to layout
	layout->addWidget(imageList);

	//Create menu bar
	createMenu();

	//Initialize selected
	selected = -1;

	//Add menu to layout
	layout->addWidget(menuBar);

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
	if (scanFiles.size() == 0) {
		up->setEnabled(false);
		down->setEnabled(false);
	}

	if (selected == 0) {
		up->setEnabled(false);
	}

	else if (selected == scanFiles.size() - 1) {
		down->setEnabled(false);
	}
	else if (selected > 0 && selected < scanFiles.size() - 1) {
		up->setEnabled(true);
		down->setEnabled(true);
	}

	update();
}

//**********Private Slots**********

//Move selected up
void ImageWidget::selectedUp() {
	scanFiles.at(selected)->selectThis(false);
	selected--;
	if (selected < 0) {
		selected = 0;
	}
	scanFiles.at(selected)->selectThis(true);
	refresh();
}

//Move selected down
void ImageWidget::selectedDown() {
	scanFiles.at(selected)->selectThis(false);
	selected++;
	if (selected >= scanFiles.size()) {
		selected = scanFiles.size() - 1;
	}
	scanFiles.at(selected)->selectThis(true);
	refresh();
}

//Add ScanFileWidget
//TODO: Fill out
void ImageWidget::addScanFileWidget() {
	scanFiles.push_back(new ScanFileWidget(scanFiles.size()));
	scanFiles.at(scanFiles.size() - 1)->updatePath("SAMPLE #" + std::to_string(scanFiles.size()));
	imageListLayout->addWidget(scanFiles.at(scanFiles.size() - 1));

	//TODO: FILL OUT

	//Hide config file
	//scanFiles.at(scanFiles.size() - 1)->hideConfigFile(true);

	selected = scanFiles.size() - 1;
	
	refresh();
}

//Remove ScanFileWidget
void ImageWidget::removeScanFileWidget() {
	/*
	imageListLayout->removeWidget(scanFiles.at(index));
	scanFiles.erase(scanFiles.begin() + index);
	refresh();
	*/
}

//**********Private Functions**********

//Create context menu
void ImageWidget::createMenu() {
	//Create buttons
	add = new QPushButton("Add Scan Sheet");
	remove = new QPushButton("Remove Scan Sheet");
	up = new QPushButton("Move Up");
	down = new QPushButton("Move Down");

	//MenuBar and layout
	menuBar = new QWidget();
	menuLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	menuBar->setLayout(menuLayout);

	//Add buttons to layout
	menuLayout->addWidget(add);
	menuLayout->addWidget(remove);
	menuLayout->addWidget(up);
	menuLayout->addWidget(down);
}

//Create image list
void ImageWidget::createImageList() {
	//Initialize layout
	imageListLayout = new QBoxLayout(QBoxLayout::TopToBottom);

	//Initialize widget
	imageList = new QWidget();

	//Set layout
	imageList->setLayout(imageListLayout);

}

//Connect button signals to slots
void ImageWidget::connectButtons() {
	QPushButton::connect(add, SIGNAL(released()), this, SLOT(addScanFileWidget()));
	QPushButton::connect(remove, SIGNAL(released()), this, SLOT(removeScanFileWidget()));
	QPushButton::connect(up, SIGNAL(released()), this, SLOT(selectedUp()));
	QPushButton::connect(down, SIGNAL(released()), this, SLOT(selectedDown()));
}