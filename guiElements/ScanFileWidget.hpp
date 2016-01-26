//ScanFile Widget
//Displays a file to be scanned, its ID, the config file to use, and the answer key to use

#ifndef SCANFILEWIDGET_H
#define SCANFILEWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QLabel>
#include <QtWidgets\QGridLayout>
#include <vector>
#include <string>

class ScanFileWidget : public QWidget  {
	Q_OBJECT

public:
	//Constructor
	ScanFileWidget(unsigned int r = 0, QWidget *parent = 0);

	//Destructor
	~ScanFileWidget();

	//Update path
	void updatePath(std::string str);

	//Update config file list
	void updateConfigFile(std::vector<std::string> configFiles);

	//Update answer keys list
	void updateAnswerKeys(std::vector<std::string> answerKeys);

	//Get path
	std::string getPath();

	//Get selected config file
	std::string getConfigFile();

	//Get selected answer key
	std::string getAnswerKey();

	//Hide config file
	void hideConfigFile(bool b);

	//Hide answer key
	void hideAnswerKey(bool b);

	//Select (highlights)
	void selectThis(bool b);

public slots:
	
private slots:
	
private:
	//Layout
	QGridLayout *layout;

	//Row
	unsigned int row;

	//Header labels
	QLabel *fileLabel;
	QLabel *configLabel;
	QLabel *answerLabel;

	//File path
	QLabel *path;

	//Configuration file to use
	QComboBox *configFile;
	
	//Answer key to use
	QComboBox *answerKey;
};

#endif