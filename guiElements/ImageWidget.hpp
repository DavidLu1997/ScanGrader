//Images widget
//Contains Images for ZopperScan

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QButtonGroup>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QSizePolicy>
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

	//Add button
	QPushButton *add;

	//Calculate button
	QPushButton *calculate;

	//Get scanfiles
	std::vector<ScanFileWidget *> getScanFiles();

public slots:

	//Refresh UI
	void refresh();

private slots:

	//Add ScanFileWidget
	void addScanFileWidget();

private:

	//Main layout
	QGridLayout *layout;

	//ScanFiles
	std::vector<ScanFileWidget *> scanFiles;

	//Menu labout
	QBoxLayout *menuLayout;

	//Initialize buttons
	void initButtons();

	//Header labels
	QLabel *fileLabel;
	QLabel *configLabel;
	QLabel *answerLabel;
	QLabel *status;

	//Widgets for buttons
	std::vector<QWidget*> buttons;

	//Layouts for buttons
	std::vector<QBoxLayout*> buttonLayout;

	//Remove buttons
	std::vector<QPushButton*> removeButton;
};

#endif