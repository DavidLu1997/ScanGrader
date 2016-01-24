#include "NavBar.hpp"

//Constructor for NavBar
NavBar::NavBar() {
	//Initialize all widgets and add to sidebar

	//Images widget
	image = new ImageWidget();
	addTab(image, "Images");

	//Answer keys widget
	key = new KeyWidget();
	addTab(key, "Answer Keys");

	//Config file widget
	config = new ConfigWidget();
	addTab(config, "Configuration Files");

	//Results widget
	result = new ResultWidget();
	addTab(result, "Results");

	//Export widget
	exportW = new ExportWidget();
	addTab(exportW, "Export");

	//Options Widget
	option = new OptionWidget();
	addTab(option, "Options");
}

//Destructor for NavBar
NavBar::~NavBar() {
	delete image;
	delete key;
	delete config;
	delete result;
	delete exportW;
	delete option;
}