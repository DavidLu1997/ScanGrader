#ifndef ZOPPERSCANAPI_H
#define ZOPPERSCANAPI_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayOut>
#include "ui_zopperscanapi.h"
#include "headers\Headers.hpp"
#include "guiElements\NavBar.hpp"

class ZopperScanAPI : public QMainWindow
{
	Q_OBJECT

public:
	const double version = 0.02;

	ZopperScanAPI(QWidget *parent = 0);
	~ZopperScanAPI();

public slots:

	//Refresh UI
	void refresh();

	//Calculate results based on current settings
	void calculate();

	//Update configfile comboboxes
	void updateConfig();

	//Update answer key comboboxes
	void updateKeys();

private:
	Ui::ZopperScanAPIClass ui;

	//Main NavBar
	NavBar *navbar;

	//Clear variables
	void clearVariables();

	//Get Image Data
	void getImageData();

	//Functions to connect signals and slots
	void connectImage();
	void connectKeys();
	void connectConfig();
	void connectResults();
	void connectExport();
	void connectOptions();

	//Compare two int vectors, returns number of equalities
	//TODO Rewrite as template
	int compare(std::vector<int> a, std::vector<int> b);

	//Images to analyze
	std::vector<AnalyzeImage> images;

	//Image names to analyze (file paths)
	std::vector<std::string> imagePaths;

	//Keys to use, indexes
	//Same size as images
	std::vector<unsigned int> useKey;

	//Answer Keys
	std::vector<AnalyzeImage> keys;

	//Answer key files to use(file paths)
	std::vector<std::string> keyPaths;

	//Answer key config files to use, same size as keyPaths
	std::vector<std::string> useFile;

	//Answers of images
	std::vector<std::vector<int>> answers;

	//Answers of solutions
	std::vector<std::vector<int>> solutions;

	//Score out of total of analyzed images
	std::vector<int> score;

	//Percentage score out of total of analyzed images
	std::vector<double> percentScore;
};

#endif // ZOPPERSCANAPI_H
