#include "NavBar.hpp"

//Constructor for NavBar
NavBar::NavBar(QWidget *parent) {
	//Initialize all widgets and add to sidebar

	//Images widget
	image = new ImageWidget(this);
	imageScroll = new QScrollArea;
	imageScroll->setWidgetResizable(true);
	imageScroll->setWidget(image);
	addTab(imageScroll, "Images");

	//Answer keys widget
	key = new KeyWidget(this);
	keyScroll = new QScrollArea;
	keyScroll->setWidgetResizable(true);
	keyScroll->setWidget(key);
	addTab(keyScroll, "Answer Keys");

	//Config file widget
	config = new ConfigWidget(this);
	configScroll = new QScrollArea;
	configScroll->setWidgetResizable(true);
	configScroll->setWidget(config);
	addTab(configScroll, "Configuration Files");

	//Results widget
	result = new ResultWidget(this);
	resultScroll = new QScrollArea;
	resultScroll->setWidgetResizable(true);
	resultScroll->setWidget(result);
	addTab(resultScroll, "Results");

	//Export widget
	exportW = new ExportWidget(this);
	exportWScroll = new QScrollArea;
	exportWScroll->setWidgetResizable(true);
	exportWScroll->setWidget(exportW);
	addTab(exportWScroll, "Export");

	//Options Widget
	option = new OptionWidget(this);
	optionScroll = new QScrollArea;
	optionScroll->setWidgetResizable(true);
	optionScroll->setWidget(option);
	addTab(optionScroll, "Options");

	//About Widget
	about = new AboutWidget(this);
	aboutScroll = new QScrollArea;
	aboutScroll->setWidgetResizable(true);
	aboutScroll->setWidget(about);
	addTab(aboutScroll, "About");

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

//Destructor for NavBar
NavBar::~NavBar() {

}