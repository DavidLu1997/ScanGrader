//Images widget
//Contains Images for ZopperScan

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QButtonGroup>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QSizePolicy>
#include <QtWidgets\QLayout>
#include <QtWidgets\QFileDialog>
#include <vector>
#include "ScanAPI\AnalyzeImage.hpp"
#include "ScanFileWidget.hpp"

class ImageWidget : public QWidget {
	Q_OBJECT

public:
	//Constructor
	ImageWidget(QWidget *parent = 0);

	//Destructor
	~ImageWidget();

	//Add button
	QPushButton *add;

	//Calculate button
	QPushButton *calculate;

	//Refresh button
	QPushButton *refreshButton;

	//Remove All button
	QPushButton *removeAll;

	//Status label
	//QLabel *status;

	//Get image urls
	QList<QUrl> getImageUrls();

	//Get key indexes
	std::vector<int> getKeyIndexes();

	//Update keys
	void updateKeys(const QList<QUrl> &urls);

public slots:

	//Refresh UI
	void refresh();

private slots:
	//Get single path from file dialog
	void addFiles();
	//Remove all the added files
	void removeAllEntries();

private:

	//Add ScanFileWidget
	void addScanFileWidget(const QUrl &url);

	//Main layout
	QGridLayout *layout;

	//ScanFiles
	std::vector<ScanFileWidget *> scanFiles;

	//File Dialog
	QList<QUrl> directory;

	//Menu labout
	QBoxLayout *menuLayout;

	//Header labels
	QLabel *fileLabel;
	QLabel *configLabel;
	QLabel *answerLabel;
	//QLabel *statusLabel;
};

#endif