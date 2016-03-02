//Defining ImagePreview window
#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

//Imports needed
#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtGui/QImageReader>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QScrollArea>
#include <QtGui/QGuiApplication>
#include <QDir>
#include <QtGui>
#include <QUrl>
#include <vector>
#include <string>

class ImagePreview : public QScrollArea {
	Q_OBJECT

public:

	//Constructor
	ImagePreview(const QUrl path);
	//Destructor
	~ImagePreview();

	//Label to hold image
	QLabel *imageLabel;

private:
	//Load file
	void loadFile(const QString &name);
};

#endif
