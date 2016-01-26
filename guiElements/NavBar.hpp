//NavBar Class, builds the main navbar
//Is a QTabWidget, stores a list of QWidgets

#ifndef NAVBAR_H
#define NAVBAR_H

#include <QtWidgets\QTabWidget>
#include <QtWidgets\QWidget>
#include <QtWidgets\QScrollArea>
#include "ZopperScanGuiIncludes.hpp"

class NavBar : public QTabWidget
{
	Q_OBJECT

public:
	//Constructor
	NavBar(QWidget *parent = 0);

	//Destructor
	~NavBar();

	//Image widget
	ImageWidget *image;

	//Answer key widget
	KeyWidget *key;

	//Configuration widget
	ConfigWidget *config;

	//Results widget
	ResultWidget *result;

	//Options widget
	OptionWidget *option;

	//Export widget
	ExportWidget *exportW; //Not named export due to keyword

private:
	
	//ScrollAreas
	QScrollArea *imageScroll;
	QScrollArea *keyScroll;
	QScrollArea *configScroll;
	QScrollArea *resultScroll;
	QScrollArea *optionScroll;
	QScrollArea *exportWScroll;
};

#endif // NAVBAR_H