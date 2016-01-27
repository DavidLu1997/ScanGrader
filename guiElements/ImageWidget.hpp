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
#include "headers\AnalyzeImage.hpp"
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

	//Status label
	QLabel *status;

	//Get scanfiles
	const std::vector<ScanFileWidget *>* getScanFiles();

	//Update keys
	void updateKeys(const QList<QUrl> &urls);

public slots:

	//Refresh UI
	void refresh();

private slots:
	//Get single path from file dialog
	void addFiles();

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

	//Initialize buttons
	void initButtons();

	//Header labels
	QLabel *fileLabel;
	QLabel *configLabel;
	QLabel *answerLabel;
	QLabel *statusLabel;

	//Widgets for buttons
	std::vector<QWidget*> buttons;

	//Layouts for buttons
	std::vector<QBoxLayout*> buttonLayout;

	//Remove buttons
	std::vector<QPushButton*> removeButton;
};

#endif