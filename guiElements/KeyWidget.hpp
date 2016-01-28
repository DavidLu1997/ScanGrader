//Keys widget
//Contains Keys for ZopperScan

#ifndef KEYWIDGET_H
#define KEYWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QGridLayout>
#include <QtWidgets\QLabel>
#include <QtWidgets\QPushButton>
#include "headers\ImageTemplate.hpp"
#include "KeyFileWidget.hpp"

class KeyWidget : public QWidget
{
	Q_OBJECT

public:
	//Constructor
	KeyWidget(QWidget *parent = 0);

	//Destructor
	~KeyWidget();

	//Get file names
	std::vector<std::string> getFileNames();

	//Get file URLs
	QList<QUrl> getFileUrls();

	//Get file URL from file name
	QUrl getFileUrl(std::string name);

	//Update config files
	void updateConfig(const QList<QUrl> &urls);

	//Push button
	QPushButton *addKey;

	//Refresh button
	QPushButton *refreshButton;

public slots:

	//Add answer key files
	void addFiles();

	//Refresh
	void refresh();

private slots:
	
private:

	//Main Layout
	QGridLayout *layout;

	//Header Labels
	QLabel *name;
	QLabel *path;
	QLabel *config;

	//QWidgets for each file
	std::vector<KeyFileWidget *> keyFiles;

};

#endif