#include "ImageWidget.hpp"

//Constructor
ImageWidget::ImageWidget(QWidget *parent) {
	//Set layout to GridLayout
	layout = new QGridLayout();
	layout->setVerticalSpacing(0);
	setLayout(layout);

	fileLabel = new QLabel("<h3>Image</h3>");
	fileLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	fileLabel->setTextFormat(Qt::RichText);
	answerLabel = new QLabel("<h3>Answer Key</h3>");
	answerLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	answerLabel->setTextFormat(Qt::RichText);
	layout->addWidget(fileLabel, 1, 0);
	layout->addWidget(answerLabel, 1, 1);

	//Create add button
	add = new QPushButton("Add Scan Image(s)");
	add->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//Connect add button
	QPushButton::connect(add, SIGNAL(released()), this, SLOT(addFiles()));
	//Add add button to layout
	layout->addWidget(add, 1000, 0);

	//Create calculate button
	calculate = new QPushButton("Calculate Score(s)");
	calculate->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//Add calculate button to layout
	layout->addWidget(calculate, 1000, 1);

	//Create refresh button
	refreshButton = new QPushButton("Refresh");
	refreshButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//Add refresh button to layout
	layout->addWidget(refreshButton, 1000, 2);

	//Create removeAll button
	removeAll = new QPushButton("Remove All");
	removeAll->setEnabled(false);
	removeAll->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//Connect removeAll button
	QPushButton::connect(removeAll, SIGNAL(released()), this, SLOT(removeAllEntries()));
	//Add removeAll button to layout
	layout->addWidget(removeAll, 1000, 2);


	//Connect calculate
	//connect(calculate, SIGNAL(released()), parent, SLOT(calculate()));

	//Create status label
	//statusLabel = new QLabel("Status: ");
	//statusLabel->setAlignment(Qt::AlignRight);
	//statusLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	//Add status label to layout
	//layout->addWidget(statusLabel, 1000, 2);

	//Create status
	//status = new QLabel("Idle");
	////status->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	//Add status to layout
	//layout->addWidget(status, 1000, 2);

	//Add empty widget to take up size
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
	empty4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty4, 999, 3);
	QWidget *empty5 = new QWidget();
	empty5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty5, 1, 4);
	QWidget *empty6 = new QWidget();
	empty6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty6, 2, 4);
	QWidget *empty7 = new QWidget();
	empty7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	layout->addWidget(empty7, 3, 4);

	layout->setColumnStretch(0, 10);
	layout->setColumnStretch(1, 10);
	layout->setColumnStretch(2, 0);
	layout->setColumnStretch(3, 10);
	layout->setColumnStretch(4, 100);

	//Refresh
	refresh();
}

//Destructor
ImageWidget::~ImageWidget() {
	delete layout;
	delete add;
	delete calculate;
	delete refreshButton;
	delete fileLabel;
	delete removeAll;
	scanFiles.clear();
}

//Get image files
QList<QUrl> ImageWidget::getImageUrls() {
	QList<QUrl> urls;
	for (unsigned int i = 0; i < scanFiles.size(); i++) {
		if (scanFiles.at(i)->deleted) {
			scanFiles.erase(scanFiles.begin() + i);
			i--;
			continue;
		}
		urls.push_back(scanFiles.at(i)->getPath());
	}
	return urls;
}

//Get key indexes
std::vector<int> ImageWidget::getKeyIndexes() {
	std::vector<int> keys;
	for (unsigned int i = 0; i < scanFiles.size(); i++) {
		if (scanFiles.at(i)->deleted) {
			scanFiles.erase(scanFiles.begin() + i);
			i--;
			continue;
		}
		keys.push_back(scanFiles.at(i)->answerKey->currentIndex());
	}
	return keys;
}
//Update keys
void ImageWidget::updateKeys(const QList<QUrl> &urls) {
	for (unsigned int i = 0; i < scanFiles.size(); i++) {
		if (scanFiles.at(i)->deleted) {
			scanFiles.erase(scanFiles.begin() + i);
			i--;
			continue;
		}
		scanFiles.at(i)->updateAnswerKeys(urls);
	}
}

//**********Public Slots**********

//Refresh UI
void ImageWidget::refresh() {
	if (scanFiles.size() < 1) {
		calculate->setEnabled(false);
		removeAll->setEnabled(false);
	}
	else {
		calculate->setEnabled(true);
		removeAll->setEnabled(true);
	}
	layout->update();
	update();
}

//**********Private Slots**********

//Add File Dialog
void ImageWidget::addFiles() {
	directory = QFileDialog::getOpenFileUrls(this, "Open Image File", QUrl("/"), "Image Files (*.bmp; *.jpg; *.png; *.pbm; *.pgm; *.ppm; *.xbm; *.xpm)");
	
	for (unsigned int i = 0; i < directory.size(); i++) {
		addScanFileWidget(directory.at(i));
	}
}

//Remove all entries
void ImageWidget::removeAllEntries() {
	//Call delete function of each scanFileWidget
	for (int i = 0; i < scanFiles.size(); i++) {
		scanFiles[i]->setDeleted();
		delete scanFiles[i];
	}
	//Clear vector and update UI
	scanFiles.clear();
	update();
	refresh();
}

//**********Private Functions**********

//Add ScanFileWidget
void ImageWidget::addScanFileWidget(const QUrl &url) {
	scanFiles.push_back(new ScanFileWidget(layout, scanFiles.size() + 2));
	scanFiles.at(scanFiles.size() - 1)->updatePath(url);
	connect(scanFiles.at(scanFiles.size() - 1)->remove, SIGNAL(released()), this, SLOT(refresh()));
	refresh();
}