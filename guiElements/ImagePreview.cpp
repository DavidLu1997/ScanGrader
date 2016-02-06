#include <string>
#include "ImagePreview.hpp"

//Constructor for window
ImagePreview::ImagePreview(const QUrl imagePath) {
	//Create label
	imageLabel = new QLabel;
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(true);
	//Need to figure out how to set image of the label to the image path

	resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}