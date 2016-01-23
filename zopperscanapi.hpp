#ifndef ZOPPERSCANAPI_H
#define ZOPPERSCANAPI_H

#include <QtWidgets/QMainWindow>
#include "ui_zopperscanapi.h"
#include "headers\Headers.hpp"

class ZopperScanAPI : public QMainWindow
{
	Q_OBJECT

public:
	ZopperScanAPI(QWidget *parent = 0);
	~ZopperScanAPI();

private:
	Ui::ZopperScanAPIClass ui;
	
	//Answer Keys
	std::vector<AnalyzeImage> keys;

	//Images to analyze
	std::vector<AnalyzeImage> images;

	//TODO: Refactor below into AnalyzeImage

	//Configuration file to use, indexes
	//Same size as images
	std::vector<unsigned int> useFile;

	//Keys to use, indexes
	//Same size as images
	std::vector<unsigned int> useKey;

	//END TODO

	//Configuration files
	std::vector<std::string> configFiles;

	//Results of analyzed images
	std::vector< std::vector<int> > results;

	//Raw results of analyzed images
	std::vector< std::vector<double> > rawResults;

	//Score out of total of analyzed images
	std::vector<unsigned int> score;

	//Percentage score out of total of analyzed images
	std::vector<double> percentScore;
};

#endif // ZOPPERSCANAPI_H
