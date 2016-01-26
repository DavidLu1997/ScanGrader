#include "NavBar.hpp"

//Constructor for NavBar
NavBar::NavBar(QWidget *parent) {
	//Initialize all widgets and add to sidebar

	//Images widget
	image = new ImageWidget();
	imageScroll = new QScrollArea;
	imageScroll->setWidgetResizable(true);
	imageScroll->setWidget(image);
	addTab(imageScroll, "Images");

	//Answer keys widget
	key = new KeyWidget();
	keyScroll = new QScrollArea;
	keyScroll->setWidgetResizable(true);
	keyScroll->setWidget(key);
	addTab(keyScroll, "Answer Keys");

	//Config file widget
	config = new ConfigWidget();
	configScroll = new QScrollArea;
	configScroll->setWidgetResizable(true);
	configScroll->setWidget(config);
	addTab(configScroll, "Configuration Files");

	//Results widget
	result = new ResultWidget();
	resultScroll = new QScrollArea;
	resultScroll->setWidgetResizable(true);
	resultScroll->setWidget(result);
	addTab(resultScroll, "Results");

	//Export widget
	exportW = new ExportWidget();
	exportWScroll = new QScrollArea;
	exportWScroll->setWidgetResizable(true);
	exportWScroll->setWidget(exportW);
	addTab(exportWScroll, "Export");

	//Options Widget
	option = new OptionWidget();
	optionScroll = new QScrollArea;
	optionScroll->setWidgetResizable(true);
	optionScroll->setWidget(option);
	addTab(optionScroll, "Options");
}

//Destructor for NavBar
NavBar::~NavBar() {
	delete image;
	delete imageScroll;
	delete key;
	delete keyScroll;
	delete config;
	delete configScroll;
	delete result;
	delete resultScroll;
	delete exportW;
	delete exportWScroll;
	delete option;
	delete optionScroll;
}