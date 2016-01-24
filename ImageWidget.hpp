//Images widget
//Contains Images for ZopperScan

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QButtonGroup>
#include <QtWidgets\QPushButton>
#include "headers\AnalyzeImage.hpp"

class ImageWidget : public QWidget
{
	Q_OBJECT

public:
	//Constructor
	ImageWidget();

	//Destructor
	~ImageWidget();

	//Refresh UI
	void refresh();

private:
	//Main button group
	QButtonGroup *buttongroup;

	//Add button
	QPushButton *add;

	//Remove button
	QPushButton *remove;

	//Up Arrow
	QPushButton *up;

	//Down arrow
	QPushButton *down;
};

#endif