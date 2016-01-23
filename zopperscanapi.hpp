#ifndef ZOPPERSCANAPI_H
#define ZOPPERSCANAPI_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayOut>
#include "ui_zopperscanapi.h"
#include "headers\Headers.hpp"
#include "NavBar.hpp"

class ZopperScanAPI : public QMainWindow
{
	Q_OBJECT

public:
	const double version = 0.01;

	ZopperScanAPI(QWidget *parent = 0);
	~ZopperScanAPI();

private:
	Ui::ZopperScanAPIClass ui;

	//Main NavBar
	NavBar *navbar;

	//Images to analyze
	std::vector<AnalyzeImage> images;

	//Configuration file to use, indexes
	//Same size as images
	std::vector<unsigned int> useFile;

	//Keys to use, indexes
	//Same size as images
	std::vector<unsigned int> useKey;

	//Configuration files
	std::vector<std::string> configFiles;

	//Answer Keys
	std::vector<AnalyzeImage> keys;

	//Score out of total of analyzed images
	std::vector<unsigned int> score;

	//Percentage score out of total of analyzed images
	std::vector<double> percentScore;
};

#endif // ZOPPERSCANAPI_H
