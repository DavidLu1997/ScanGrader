#include "OptionWidget.hpp"

//Constructor
OptionWidget::OptionWidget(QWidget *parent) {

	//Layout
	layout = new QGridLayout();

	//Title
	title = new QLabel("<h3>Options</h3>");
	title->setTextFormat(Qt::RichText);
	layout->addWidget(title, 0, 0);

	//Threshold
	thresholdLabel = new QLabel("Darkness Threshold (0-255): ");
	layout->addWidget(thresholdLabel, 1, 0);
	threshold = new QSlider(Qt::Horizontal);
	threshold->setTickInterval(16);
	threshold->setSingleStep(4);
	threshold->setMinimum(0);
	threshold->setMaximum(255);
	threshold->setSliderPosition(defaultThreshold);
	threshold->setTickPosition(QSlider::TicksBothSides);
	layout->addWidget(threshold, 1, 2);
	thresholdValue = new QSpinBox();
	thresholdValue->setMaximumWidth(100);
	thresholdValue->setRange(0, 255);
	thresholdValue->setSingleStep(1);
	thresholdValue->setValue(defaultThreshold);
	thresholdValue->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(thresholdValue, 1, 1);

	//Percent
	percentLabel = new QLabel("Darkness Percentage (0-100%): ");
	layout->addWidget(percentLabel, 2, 0);
	percent = new QSlider(Qt::Horizontal);
	percent->setTickInterval(10);
	percent->setSingleStep(1);
	percent->setMinimum(0);
	percent->setMaximum(100);
	percent->setSliderPosition(defaultPercent);
	percent->setTickPosition(QSlider::TicksBothSides);
	layout->addWidget(percent, 2, 2);
	percentValue = new QSpinBox();
	percentValue->setMaximumWidth(100);
	percentValue->setSingleStep(1);
	percentValue->setRange(0, 100);
	percentValue->setValue(defaultPercent);
	percentValue->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(percentValue, 2, 1);

	//Default
	defaultSettings = new QPushButton("Default");
	layout->addWidget(defaultSettings, 3, 0);
	newDefault = new QPushButton("Set Default");
	layout->addWidget(newDefault, 4, 0);

	//Empty
	QWidget *empty1 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty1, 999, 0);
	QWidget *empty2 = new QWidget();
	empty2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty2, 999, 1);
	QWidget *empty3 = new QWidget();
	empty3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty3, 999, 2);
	QWidget *empty4 = new QWidget();
	empty4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty4, 0, 3);
	QWidget *empty5 = new QWidget();
	empty5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty5, 1, 3);
	QWidget *empty6 = new QWidget();
	empty6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty6, 2, 3);

	//Connect
	connect(threshold, SIGNAL(valueChanged(int)), this, SLOT(thresholdChanged(int)));
	connect(percent, SIGNAL(valueChanged(int)), this, SLOT(percentChanged(int)));
	connect(thresholdValue, SIGNAL(valueChanged(int)), this, SLOT(thresholdChanged(int)));
	connect(percentValue, SIGNAL(valueChanged(int)), this, SLOT(percentChanged(int)));
	connect(defaultSettings, SIGNAL(released()), this, SLOT(revertDefault()));
	connect(newDefault, SIGNAL(released()), this, SLOT(setDefault()));

	//Set Layout
	layout->setColumnStretch(0, 0);
	layout->setColumnStretch(1, 0);
	layout->setColumnStretch(2, 100);
	layout->setColumnStretch(3, 100);
	setLayout(layout);
}

//Destructor
OptionWidget::~OptionWidget() {
	delete title;
	delete thresholdLabel;
	delete percentLabel;
	delete threshold;
	delete thresholdValue;
	delete percent;
	delete percentValue;
	delete layout;
}

//**********Public Functions**********

//Get percent
double OptionWidget::getPercent() {
	return percent->value() / 100.0;
}

//Get threshold
int OptionWidget::getThreshold() {
	return threshold->value();
}

//**********Public Slots**********

//Percent changed
void OptionWidget::percentChanged(int value) {
	percentValue->setValue(value);
	percent->setValue(value);
}

//Threshold changed
void OptionWidget::thresholdChanged(int value) {
	thresholdValue->setValue(value);
	threshold->setValue(value);
}

//Default
void OptionWidget::revertDefault() {
	percentChanged(defaultPercent);
	thresholdChanged(defaultThreshold);
}

//Set default
void OptionWidget::setDefault() {
	defaultPercent = percent->value();
	defaultThreshold = threshold->value();
}
