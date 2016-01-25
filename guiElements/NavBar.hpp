//NavBar Class, builds the main navbar
//Is a QTabWidget, stores a list of QWidgets

#ifndef NAVBAR_H
#define NAVBAR_H

#include <QtWidgets\QTabWidget>
#include <QtWidgets\QWidget>
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
	
};

#endif // NAVBAR_H