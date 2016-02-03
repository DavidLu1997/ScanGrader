#include "AboutWidget.hpp"

//Constructor
AboutWidget::AboutWidget(QWidget *parent) {
	//Create layout
	layout = new QBoxLayout(QBoxLayout::TopToBottom);

	//Labels
	title = new QLabel("<h3>ScanGrader</h3>");
	title->setTextFormat(Qt::RichText);
	layout->addWidget(title);
	desc = new QLabel("An optical mark recognition program built to easily mark test/quizzes. See readme.txt for details.");
	layout->addWidget(desc);
	authors = new QLabel("<b>&copy; David Lu 2016</b>");
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

//Destructor
AboutWidget::~AboutWidget() {
	delete layout;
}

//Update version
void AboutWidget::updateVersion(double ver) {
	version->setText(tr("<i>Version %1</i>").arg(ver));
	update();
}