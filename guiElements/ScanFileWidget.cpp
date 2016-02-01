#include "ScanFileWidget.hpp"

//Constructor
ScanFileWidget::ScanFileWidget(QGridLayout *layout, unsigned int r, QWidget *parent) {
	//Initialize path
	path = new QUrl();
	file = new QLabel();

	//Initialize answer key
	answerKey = new QComboBox();
	
	//Initialize remove
	remove = new QPushButton("Remove");
	connect(remove, SIGNAL(released()), this, SLOT(setDeleted()));

	//Initialize row
	row = r;

	//Add widgets to header
	layout->addWidget(file, row, 0);
	layout->addWidget(answerKey, row, 1);
	layout->addWidget(remove, row, 2);
}

//Destructor
ScanFileWidget::~ScanFileWidget() {
	delete remove;
	delete path;
	delete file;
	delete answerKey;
}

void ScanFileWidget::setDeleted() {
	delete file;
	delete answerKey;
	delete remove;
	deleted = true;
}

//**********Public Functions**********

//Update path
void ScanFileWidget::updatePath(const QUrl &url) {
	*path = url;
	file->setText(path->fileName());
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