//Results widget
//Contains Results for ZopperScan

#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

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

	enum fileType {CSV = 0, TXT = 1, SQL = 2};

public slots: 

	//Clear display
	void clearDisplay();

	//Clear data
	void clearData();

	//Calculate
	void calculate();

	//Display calculated results
	void display();

	//Export Results
	void exportResults();

	//Export results to file
	void exportToFile();

	//Export results to server
	void exportToServer();

	//Change export name
	void changeExportName(const QString &name);

	//Change export type
	void changeExportType(int type);

	//Change host name
	void changeHostName(const QString &name);

	//Change databaseName
	void changeDatabaseName(const QString &name);

	//Change port
	void changePort(const QString &name);

	//Change userName
	void changeUserName(const QString &name);

	//Change password
	void changePassword(const QString &name);

private slots:
	
private:
	//Grid layout
	QGridLayout *layout;

	//Title Labels
	QLabel *idTitle;
	QLabel *correctTitle;
	QLabel *wrongTitle;
	QLabel *totalTitle;
	QLabel *percentTitle;
	QLabel *averageLabel;
	QLabel *medianLabel;
	QLabel *minLabel;
	QLabel *maxLabel;

	//Button
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
	double min;
	double max;

	//Export name
	std::string exportName;

	//Export type
	int exportType;

	//Server information
	QString serverHostName;
	QString serverDatabaseName;
	int port;
	QString serverUserName;
	QString serverPassword;
};

#endif
