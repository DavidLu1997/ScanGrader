//Results widget
//Contains Results for ZopperScan

#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QGridLayout>
#include <QtWidgets\QLabel>
#include <QtWidgets\QPushButton>

class ResultWidget : public QWidget
{
	Q_OBJECT

public:
	//Constructor
	ResultWidget(QWidget *parent = 0);

	//Destructor
	~ResultWidget();

	//Add row
	void addRow(std::string id, std::vector<int> answers, std::vector<int> solutions);

	//Remove row
	void removeRow(std::string id);

public slots: 
	
	//Clear display
	void clear();

	//Recalculate
	void calculate();

	//Display calculated results
	void display();

	//Export results to CSV
	void exportCSV();

	//Export to txt
	void exportTXT();

	//Change export name
	void changeExportName(const QString &name);

private slots:
	
private:
	//Main layout
	QBoxLayout *layout;

	//Table for results
	QWidget *table;

	//Grid layout for table
	QGridLayout *tableLayout;

	//Title Labels
	QLabel *summary;
	QLabel *correctTitle;
	QLabel *wrongTitle;
	QLabel *totalTitle;
	QLabel *percentTitle;
	QLabel *deviationTitle;

	//Buttons
	QPushButton *refresh;
	QPushButton *export;

	//Information labels, vector
	std::vector<QLabel *> id;
	std::vector<QLabel *> correct;
	std::vector<QLabel *> wrong;
	std::vector<QLabel *> total;
	std::vector<QLabel *> percent;
	std::vector<QLabel *> deviation;

	//Raw data
	std::vector<std::string> idList;
	std::vector< std::vector<int> > answersList;
	std::vector< std::vector<int> > solutionsList;
	std::vector<int> correctAnswers;
	std::vector<int> wrongAnswers;
	std::vector<int> totalQuestions;
	std::vector<double> percentScore;
	std::vector<double> deviationAverage;
	double average;
	double median;
	double stdev;
	double min;
	double max;

	//Export name
	QString exportName;
};

#endif