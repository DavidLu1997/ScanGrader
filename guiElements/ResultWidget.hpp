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
	void addRow(std::string id, const std::vector<int> &answers, const std::vector<int> &solutions);

	//Remove row
	void removeRow(std::string id);

	enum exportType {CSV = 1, TXT = 0};

public slots: 
	
	//Refresh()
	void refresh();

	//Clear display
	void clearDisplay();

	//Clear data
	void clearData();

	//Calculate
	void calculate();

	//Display calculated results
	void display();

	//Export results to CSV
	void exportCSV();

	//Export to txt
	void exportTXT();

	//Change export name
	void changeExportName(const QString &name);

	//Change export type
	void changeExportType(int type);

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
	QLabel *idTitle;
	QLabel *correctTitle;
	QLabel *wrongTitle;
	QLabel *totalTitle;
	QLabel *percentTitle;

	//Buttons
	QBoxLayout *buttonLayout;
	QWidget *buttonWidget;
	QPushButton *refreshButton;
	QPushButton *exportButton;

	//Information labels, vector
	std::vector<QLabel *> id;
	std::vector<QLabel *> correct;
	std::vector<QLabel *> wrong;
	std::vector<QLabel *> total;
	std::vector<QLabel *> percent;

	//Raw data
	std::vector<std::string> idList;
	std::vector< std::vector<int> > answersList;
	std::vector< std::vector<int> > solutionsList;
	std::vector<int> correctAnswers;
	std::vector<int> wrongAnswers;
	std::vector<int> totalQuestions;
	std::vector<double> percentScore;
	double average;
	double median;
	int min;
	int max;

	//Export name
	QString exportName;

	//Export type
	int exportT = exportType::CSV;
};

#endif