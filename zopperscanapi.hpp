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
	const double version = 0.01;

	ZopperScanAPI(QWidget *parent = 0);
	~ZopperScanAPI();

	//Refresh UI
	void refresh();

	//Image get index from string
	int getImage(std::string name);

	//Image get string from index
	std::string getImage(unsigned int index);

	//Key get index from string
	int getKey(std::string name);

	//Key get string from index
	std::string getKey(unsigned int index);

	//Config get index from string
	int getConfig(std::string name);

	//Config get string from index
	std::string getConfig(unsigned int index);

public slots:
	//Add image
	void addImage(std::string name);

	//Remove image by name
	void removeImage(std::string name);

	//Remove image by index
	void removeImage(unsigned int index);

	//Swap image, swaps two indexes of images
	void swapImage(unsigned int a, unsigned int b);

	//Add answer key
	void addKey(std::string name);

	//Remove answer key
	void removeKey(std::string name);

	//Remove answer key by index
	void removeKey(unsigned int index);

	//Add configuration file
	void addConfig(std::string name);

	//Remove configuration file
	void removeConfig(std::string name);

	//Remove configuration file by index
	void removeConfig(unsigned int index);

	//Calculate results based on current settings
	void calculate();

	//Clear variables
	void clearVariables();

private:
	Ui::ZopperScanAPIClass ui;

	//Main NavBar
	NavBar *navbar;

	//Initialize variables
	void initVariables();

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
	std::vector<AnalyzeImage> *images;

	//Image names to analyze (file paths)
	std::vector<std::string> *imagePaths;

	//Keys to use, indexes
	//Same size as images
	std::vector<unsigned int> *useKey;

	//Configuration files to use (file paths)
	std::vector<std::string> *configPaths;

	//Answer Keys
	std::vector<AnalyzeImage> *keys;

	//Answer key files to use(file paths)
	std::vector<std::string> *keyPaths;

	//Answer key config files to use, same size as keyPaths
	std::vector<unsigned int> *useFile;

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
