#ifndef ZOPPERSCANAPI_H
#define ZOPPERSCANAPI_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>
#include <QtWidgets/QProgressBar>
#include "ui_scangrader.h"
#include "ScanAPI/Headers.hpp"
#include "guiElements/NavBar.hpp"

class ScanGrader : public QMainWindow
{
	Q_OBJECT

public:
	const double version = 1.30;

	ScanGrader(QWidget *parent = 0);
	~ScanGrader();

public slots:

	//Refresh UI
	void refresh();

	//Calculate results based on current settings
	void calculate();

	//Update configfile comboboxes
	void updateConfig();

	//Update answer key comboboxes
	void updateKeys();

	//Update percent
	void updatePercent(int value);

	//Update threshold
	void updateThreshold(int value);

private:
	Ui::ZopperScanAPIClass ui;

	//Main NavBar
	NavBar *navbar;

	//Progress bar
	QProgressBar *progress;

	//Status label
	QLabel *status;

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
	void connectAbout();

	//Compare two int vectors, returns number of equalities
	template <typename T>
	unsigned int compare(std::vector<T> a, std::vector<T> b);

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
	std::vector<std::vector<int> > answers;

	//Answers of solutions
	std::vector<std::vector<int> > solutions;

	//Score out of total of analyzed images
	std::vector<int> score;

	//Percentage score out of total of analyzed images
	std::vector<double> percentScore;
};

#endif // ZOPPERSCANAPI_H
