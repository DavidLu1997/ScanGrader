#include "AboutWidget.hpp"

//Constructor
AboutWidget::AboutWidget(QWidget *parent) {
	//Create layout
	layout = new QBoxLayout(QBoxLayout::TopToBottom);

	//Labels
	title = new QLabel("<h3>ScanGrader</h3>");
	title->setTextFormat(Qt::RichText);
	layout->addWidget(title);
	desc = new QLabel("Lorem ipsum I don't know how this goes.");
	layout->addWidget(desc);
	authors = new QLabel("<b>David Lu</b>");
	authors->setTextFormat(Qt::RichText);
	layout->addWidget(authors);
	version = new QLabel();
	version->setTextFormat(Qt::RichText);
	layout->addWidget(version);
	QWidget *empty1 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty1);
	
	setLayout(layout);

}

//Desctructor
AboutWidget::~AboutWidget() {
	delete layout;
}

//Update version
void AboutWidget::updateVersion(double ver) {
	version->setText(tr("<i>Version %1</i>").arg(ver));
	update();
}