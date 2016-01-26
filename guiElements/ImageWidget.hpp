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

	//Selected image
	int selected;

private slots:

	//Add ScanFileWidget
	void addScanFileWidget();

private:

	//Main layout
	QGridLayout *layout;

	//ScanFiles
	std::vector<ScanFileWidget *> scanFiles;

	//Create context menu
	void createMenu();

	//Context menubar
	//Add, remove, up, down, etc.
	QWidget *menuBar;

	//Menu labout
	QBoxLayout *menuLayout;

	//Connect button signals to slots
	void connectButtons();

	//Header labels
	QLabel *fileLabel;
	QLabel *configLabel;
	QLabel *answerLabel;
};

#endif