//ScanFile Widget
//Displays a file to be scanned, its ID, the config file to use, and the answer key to use

#ifndef SCANFILEWIDGET_H
#define SCANFILEWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QLabel>
#include <QtWidgets\QGridLayout>
#include <QtWidgets\QPushButton>
#include <vector>
#include <string>

class ScanFileWidget : public QWidget  {
	Q_OBJECT

public:
	//Constructor
	ScanFileWidget(QGridLayout *layout, unsigned int r = 0, QWidget *parent = 0);

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

public slots:
	
private slots:
	
private:
	//Row
	unsigned int row;

	//File path
	QLabel *path;

	//Configuration file to use
	QComboBox *configFile;
	
	//Answer key to use
	QComboBox *answerKey;

	//Widget for buttons
	QWidget *buttons;

	//Layout for buttons
	QBoxLayout *buttonLayout;

	//Remove button
	QPushButton *removeButton;

	//Up Button
	QPushButton *upButton;

	//Down Button
	QPushButton *downButton;

	//Initialize buttons
	void initButtons();
};

#endif