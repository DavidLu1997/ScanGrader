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

class ScanFileWidget : public QWidget  {
	Q_OBJECT

public:
	//Constructor
	ScanFileWidget(QGridLayout *layout, unsigned int r = 0, QWidget *parent = 0);

	//Destructor
	~ScanFileWidget();

	//Update path
	void updatePath(const QUrl &url);

	//Update config file list
	void updateConfigFile(const std::vector<std::string> &configFiles);

	//Update answer keys list
	void updateAnswerKeys(const std::vector<std::string> &answerKeys);

	//Get path
	const QUrl getPath();

	//Get selected config file
	std::string getConfigFile();

	//Get selected answer key
	std::string getAnswerKey();

public slots:
	
private slots:
	
private:
	//Row
	unsigned int row;

	//File path
	QUrl *path;
	QLabel *file;

	//Configuration file to use
	QComboBox *configFile;
	
	//Answer key to use
	QComboBox *answerKey;
};

#endif