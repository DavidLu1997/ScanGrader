#include "ScanFileWidget.hpp"

//Constructor
ScanFileWidget::ScanFileWidget(QGridLayout *layout, unsigned int r, QWidget *parent) {
	//Initialize path
	path = new QUrl();
	file = new QLabel();

	//Initialize answer key
	answerKey = new QComboBox();

	//Initialize view button
	view = new QPushButton("View");
	connect(view, SIGNAL(released()), this, SLOT(previewImage()));
	
	//Initialize remove
	remove = new QPushButton("Remove");
	connect(remove, SIGNAL(released()), this, SLOT(setDeleted()));

	//Initialize row
	row = r;

	//Add widgets to header
	layout->addWidget(file, row, 0);
	layout->addWidget(answerKey, row, 1);
	layout->addWidget(view, row, 2);
	layout->addWidget(remove, row, 3);
}

//Destructor
ScanFileWidget::~ScanFileWidget() {

}

void ScanFileWidget::setDeleted() {
	if (deleted)
		return;
	delete file;
	delete answerKey;
	delete remove;
	delete path;
	delete view;
	deleted = true;
}

//**********Public Functions**********

//Preview image
void ScanFileWidget::previewImage() {
	//Create new window
	//imagePreview = new ImagePreview(getPath());
}

//Update path
void ScanFileWidget::updatePath(const QUrl &url) {
	*path = url;
	file->setText(path->toLocalFile());
}

//Update answer keys list
void ScanFileWidget::updateAnswerKeys(const QList<QUrl> &urls) {
	answerKey->clear();

	for (unsigned int i = 0; i < urls.size(); i++) {
		answerKey->addItem(urls.at(i).fileName());
	}
}

//Get path
const QUrl ScanFileWidget::getPath() {
	return *path;
}

//Get selected answer key
std::string ScanFileWidget::getAnswerKey() {
	return answerKey->currentText().toStdString();
}

//**********Private Functions**********