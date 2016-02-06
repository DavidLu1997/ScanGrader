//ScanFile Widget
//Displays a file to be scanned, its ID, the config file to use, and the answer key to use

#ifndef SCANFILEWIDGET_H
#define SCANFILEWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QLabel>
#include <QtWidgets\QGridLayout>
#include <QtWidgets\QPushButton>
#include <QUrl>
#include <vector>
#include <string>

//#include "ImagePreview.hpp"


class ScanFileWidget : public QWidget  {
	Q_OBJECT

public:
	//Constructor
	ScanFileWidget(QGridLayout *layout, unsigned int r = 0, QWidget *parent = 0);

	//Destructor
	~ScanFileWidget();

	//Update path
	void updatePath(const QUrl &url);

	//Update answer keys list
	void updateAnswerKeys(const QList<QUrl> &urls);

	//Get path
	const QUrl getPath();

	//Get selected answer key
	std::string getAnswerKey();

	//View button
	QPushButton *view;

	//Remove
	QPushButton *remove;

	//Deleted
	bool deleted = false;

	//Answer key to use
	QComboBox *answerKey;

public slots:
	//Delete
	void setDeleted();

	//Preview image
	void previewImage();
private slots :

	
private:
	//Row
	unsigned int row;

	//Image preview window
	//ImagePreview *imagePreview;

	//File path
	QUrl *path;
	QLabel *file;
};

#endif