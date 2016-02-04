#include "ResultWidget.hpp"
#include <algorithm>
#include <fstream>

//Constructor
ResultWidget::ResultWidget(QWidget *parent) {
	QWidget();
	//Layout
	layout = new QGridLayout();
	
	//Button
	exportButton = new QPushButton("Export");
	changeExportType(fileType::CSV);
	connect(exportButton, SIGNAL(released()), this, SLOT(exportResults()));
	exportButton->setEnabled(false);
	layout->addWidget(exportButton, 1000, 0);

	//Summary
	averageLabel = new QLabel();
	averageLabel->setTextFormat(Qt::RichText);
	layout->addWidget(averageLabel, 1, 0);
	medianLabel = new QLabel();
	medianLabel->setTextFormat(Qt::RichText);
	layout->addWidget(medianLabel, 1, 1);
	maxLabel = new QLabel();
	maxLabel->setTextFormat(Qt::RichText);
	layout->addWidget(maxLabel, 1, 2);
	minLabel = new QLabel();
	minLabel->setTextFormat(Qt::RichText);
	layout->addWidget(minLabel, 1, 3);

	//Title
	idTitle = new QLabel("<h3>ID</h3>");
	idTitle->setTextFormat(Qt::RichText);
	idTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(idTitle, 0, 0);

	correctTitle = new QLabel("<h3>Correct Questions</h3>");
	correctTitle->setTextFormat(Qt::RichText);
	correctTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(correctTitle, 0, 1);

	wrongTitle = new QLabel("<h3>Wrong Questions</h3>");
	wrongTitle->setTextFormat(Qt::RichText);
	wrongTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(wrongTitle, 0, 2);

	totalTitle = new QLabel("<h3>Total Questions</h3>");
	totalTitle->setTextFormat(Qt::RichText);
	totalTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(totalTitle, 0, 3);

	percentTitle = new QLabel("<h3>Percentage Score</h3>");
	percentTitle->setTextFormat(Qt::RichText);
	percentTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	layout->addWidget(percentTitle, 0, 4);

	//Empties
	QWidget *empty1 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty1, 999, 0);
	QWidget *empty2 = new QWidget();
	empty2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty2, 999, 1);
	QWidget *empty3 = new QWidget();
	empty3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty3, 999, 2);
	QWidget *empty4 = new QWidget();
	empty4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty4, 999, 3);
	QWidget *empty5 = new QWidget();
	empty5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty5, 999, 4);

	exportName = "Results";

	setLayout(layout);
}

//Destructor
ResultWidget::~ResultWidget() {
	delete layout;
}

//Add row
void ResultWidget::addRow(std::string id, const std::vector<int> &answers, const std::vector<int> &solutions) {
	answersList.push_back(answers);
	solutionsList.push_back(solutions);

	int correct = 0;
	//Get correct answers
	for (unsigned int i = 0; i < answers.size(); i++) {
		if (answers[i] == solutions[i]) {
			correct++;
		}
	}

	correctAnswers.push_back(correct);
	wrongAnswers.push_back(answers.size() - correct);
	totalQuestions.push_back(answers.size());
	percentScore.push_back((double)correct / answers.size());
	idList.push_back(id);
}

//Remove row
void ResultWidget::removeRow(std::string id) {
	//Get index from id
	int index = 0;
	for (unsigned int i = 0; i < idList.size(); i++) {
		if (id == idList[i]) {
			index = i;
			break;
		}
	}

	//Erase
	idList.erase(idList.begin() + index);
	answersList.erase(answersList.begin() + index);
	solutionsList.erase(solutionsList.begin() + index);
	correctAnswers.erase(correctAnswers.begin() + index);
	wrongAnswers.erase(wrongAnswers.begin() + index);
	totalQuestions.erase(totalQuestions.begin() + index);
	percentScore.erase(percentScore.begin() + index);

	calculate();
	display();
}

//**********Public Slots**********

//Clear display
void ResultWidget::clearDisplay() {
	for (unsigned int i = 0; i < id.size(); i++) {
		layout->removeWidget(id[i]);
		delete id[i];
		layout->removeWidget(correct[i]);
		delete correct[i];
		layout->removeWidget(wrong[i]);
		delete wrong[i];
		layout->removeWidget(total[i]);
		delete total[i];
		layout->removeWidget(percent[i]);
		delete percent[i];
	}
	layout->update();
	id.clear();
	correct.clear();
	wrong.clear();
	total.clear();
	percent.clear();
	update();
	exportButton->setEnabled(false);
}

//Clear data
void ResultWidget::clearData() {
	idList.clear();
	answersList.clear();
	solutionsList.clear();
	correctAnswers.clear();
	wrongAnswers.clear();
	totalQuestions.clear();
	percentScore.clear();
	average = 0;
	median = 0;
	min = 0;
	max = 0;
}

//Calculate results
void ResultWidget::calculate() {
	//Get average, min, max
	average = 0;
	for (unsigned int i = 0; i < correctAnswers.size(); i++) {
		average += (double)correctAnswers[i] / totalQuestions[i];
	}
	average /= correctAnswers.size();

	//Get median, max, min
	std::vector<double> correctCopy;
	for (unsigned int i = 0; i < correctAnswers.size(); i++) {
		correctCopy.push_back((double)correctAnswers[i] / totalQuestions[i]);
	}
	std::sort(correctCopy.begin(), correctCopy.end());

	if (correctCopy.size() % 2) {
		median = correctCopy.at(correctCopy.size() / 2);
	}
	else {
		median = (correctCopy.at(correctCopy.size() / 2) + correctCopy.at((correctCopy.size() / 2) - 1)) / 2.0;
	}
	min = correctCopy[0];
	max = correctCopy[correctCopy.size() - 1];
}

//Display calculated results
void ResultWidget::display() {
	clearDisplay();
	//Construct summary
	averageLabel->setText(tr("<b>Average: %1%</b>").arg(average * 100));
	medianLabel->setText(tr("<b>Median: %1%</b>").arg(median * 100));
	maxLabel->setText(tr("<b>Maximum: %1%</b>").arg(max * 100));
	minLabel->setText(tr("<b>Minimum: %1%</b>").arg(min * 100));

	//Construct label vectors
	for (unsigned int i = 0; i < idList.size(); i++) {
		id.push_back(new QLabel(tr(idList[i].c_str())));
		correct.push_back(new QLabel(tr("%1").arg(correctAnswers[i])));
		wrong.push_back(new QLabel(tr("%1").arg(wrongAnswers[i])));
		total.push_back(new QLabel(tr("%1").arg(totalQuestions[i])));
		percent.push_back(new QLabel(tr("%1%").arg(percentScore[i] * 100)));
	}

	//Add labels to grid
	for (unsigned int i = 0; i < id.size(); i++) {
		layout->addWidget(id[i], i + 2, 0);
		layout->addWidget(correct[i], i + 2, 1);
		layout->addWidget(wrong[i], i + 2, 2);
		layout->addWidget(total[i], i + 2, 3);
		layout->addWidget(percent[i], i + 2, 4);
	}

	exportButton->setEnabled(true);

	//New layout
	setLayout(layout);

	update();
}

//Export Results
void ResultWidget::exportResults() {
	switch (exportType) {
	case CSV:
		exportToFile();
		break;
	case TXT:
		exportToFile();
		break;
	case SQL:
		exportToServer();
		break;
	default:
		break;
	}
}

//Export results to file
void ResultWidget::exportToFile() {
	std::string fileName;
	char delimiter = ' ';

	switch (exportType) {
	case fileType::CSV:
		delimiter = ',';
		fileName = exportName + ".csv";
		break;
	case fileType::TXT:
		delimiter = ' ';
		fileName = exportName + ".txt";
		break;
	}

	std::ofstream out(fileName, std::ios::out);

	//Print out summary
	out << "Average:" << delimiter << average << delimiter << "Median:" << delimiter << median << delimiter << "Minimum:" << delimiter << min << delimiter << "Maximum:" << delimiter << max << std::endl;

	//Print out headers
	out << "ID" << delimiter << "Correct" << delimiter << "Wrong" << delimiter << "Total" << delimiter << "Percent Score" << std::endl;

	//Print out results
	for (unsigned int i = 0; i < idList.size(); i++) {
		out << idList[i] << delimiter;
		out << correctAnswers[i] << delimiter;
		out << wrongAnswers[i] << delimiter;
		out << totalQuestions[i] << delimiter;
		out << percentScore[i] << std::endl;
	}

	out.close();
}

//Export results to server
void ResultWidget::exportToServer() {

}

//Change export name
void ResultWidget::changeExportName(const QString &name) {
	exportName = name.toStdString();
}

//Change export type
void ResultWidget::changeExportType(int type) {
	exportType = type;
}

//Change host name
void ResultWidget::changeHostName(const QString &name) {
	serverHostName = name;
}

//Change databaseName
void ResultWidget::changeDatabaseName(const QString &name) {
	serverDatabaseName = name;
}

//Change port
void ResultWidget::changePort(const QString &name) {
	port = name.toInt();
}

//Change userName
void ResultWidget::changeUserName(const QString &name) {
	serverUserName = name;
}

//Change password
void ResultWidget::changePassword(const QString &name) {
	serverPassword = name;
}

