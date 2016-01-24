//Images widget
//Contains Images for ZopperScan

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QButtonGroup>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QLayout>
#include <vector>
#include "headers\AnalyzeImage.hpp"
#include "ScanFileWidget.hpp"

class ImageWidget : public QWidget {
	Q_OBJECT

public:
	//Constructor
	ImageWidget(QWidget *parent = 0);

	//Destructor
	~ImageWidget();

	//Refresh UI
	void refresh();

	//Add button
	QPushButton *add;

	//Remove button
	QPushButton *remove;

	//Up Arrow
	QPushButton *up;

	//Down arrow
	QPushButton *down;

	//Selected image
	int selected;

private slots:
	//Move selected up
	void selectedUp();

	//Move selected down
	void selectedDown();
private:
	//Create context menu
	void createMenu();

	//ScanFiles
	std::vector<ScanFileWidget *> scanFiles;

	//Main layout
	QBoxLayout *layout;

	//Context menubar
	//Add, remove, up, down, etc.
	QWidget *menuBar;

	//Menu labout
	QBoxLayout *menuLayout;

	//Main button group
	QButtonGroup *buttonGroup;
};

#endif