#include "ImageWidget.hpp"
//Constructor
ImageWidget::ImageWidget(QWidget *parent) {
	//Set layout to BoxLayout
	layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	setLayout(layout);

	//Create menu bar
	createMenu();

	//Initialize selected
	int selected = -1;

	//Add menu to layout
	layout->addWidget(menuBar);
}

//Destructor
ImageWidget::~ImageWidget() {
	delete layout;
	delete menuBar;
	delete buttonGroup;
	delete add;
	delete remove;
	delete up;
	delete down;
}

//**********Public Functions**********

//Refresh UI
void ImageWidget::refresh() {

}

//**********Private Slots**********

//Move selected up
void ImageWidget::selectedUp() {
	selected--;
	if (selected < 0) {
		selected = 0;
	}

	refresh();
}

//Move selected down
void ImageWidget::selectedDown() {
	selected++;
	if (selected >= scanFiles.size()) {
		selected = scanFiles.size() - 1;
	}

	refresh();
}

//**********Private Functions**********

//Create context menu
void ImageWidget::createMenu() {
	//Create buttongroup
	buttonGroup = new QButtonGroup();
	
	//Create buttons
	add = new QPushButton("Add Scan Sheet");
	buttonGroup->addButton(add);
	remove = new QPushButton("Remove Scan Sheet");
	buttonGroup->addButton(remove);
	up = new QPushButton("Move Up");
	buttonGroup->addButton(up);
	down = new QPushButton("Move Down");
	buttonGroup->addButton(down);

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