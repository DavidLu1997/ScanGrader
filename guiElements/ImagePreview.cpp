//Imports
#include <string>
#include "ImagePreview.hpp"

//Constructor for window
ImagePreview::ImagePreview(const QUrl imagePath) {
	//Create label
	imageLabel = new QLabel;
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(true);

	//Scroll Area
	setBackgroundRole(QPalette::Dark);
	setWidget(imageLabel);

	//Call loadFile function, passes file path to function
	loadFile(imagePath.toLocalFile());
	//Allow window to be resizable
	setWidgetResizable(true);

	setAttribute(Qt::WA_DeleteOnClose);
	//Display
	show();
}

//Destructor
ImagePreview::~ImagePreview() {
	delete imageLabel;
}

//Load file
void ImagePreview::loadFile(const QString &name) {
	QImageReader reader(name);
	reader.setAutoTransform(true);
	const QImage image = reader.read();
	//Displays notification if image can't be loaded
	if (image.isNull()) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(), tr("Cannot load %1.").arg(QDir::toNativeSeparators(name)));
		setWindowFilePath(QString());
		imageLabel->setPixmap(QPixmap());
		imageLabel->adjustSize();
		return;
	}
	//Display image on label
	imageLabel->setPixmap(QPixmap::fromImage(image));
	imageLabel->resize(imageLabel->pixmap()->size());
	resize(imageLabel->pixmap()->size());
	setWindowFilePath(name);
	return;
}