#include "NavBar.hpp"

//Constructor for NavBar
NavBar::NavBar() {
	//Initialize all widgets
	image = new ImageWidget();
	key = new KeyWidget();
	config = new ConfigWidget();
	result = new ResultWidget();
	option = new OptionWidget();

	//Add all widgets to navbar
	addTab(image, "Images");
	addTab(key, "Answer Keys");
	addTab(config, "Configuration Files");
	addTab(result, "Results");
	addTab(option, "Options");
}

//Destructor for NavBar
NavBar::~NavBar() {
	delete image;
	delete key;
	delete config;
	delete result;
	delete option;
}