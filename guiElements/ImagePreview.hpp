//Defining ImagePreview window
#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QLabel>
#include <QtWidgets\QGridLayout>
#include <QtWidgets\QPushButton>
#include <QUrl>
#include <vector>
#include <string>

class ImagePreview : public QWidget {
	Q_OBJECT

public:

	//Constructor
	ImagePreview(const QUrl path);
	//Destructor
	~ImagePreview();

	//Label to hold image
	QLabel *imageLabel;

};

#endif