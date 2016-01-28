#include "ResultWidget.hpp"
#include <algorithm>

//Constructor
ResultWidget::ResultWidget(QWidget *parent) {
	QWidget();

	//Buttons
	buttonWidget = new QWidget();
	buttonLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	refreshButton = new QPushButton("Refresh");
	connect(refreshButton, SIGNAL(released()), this, SLOT(refresh()));
	buttonLayout->addWidget(refreshButton);
	exportButton = new QPushButton("Export");
	buttonLayout->addWidget(exportButton);
	changeExportType(exportType::CSV);
	buttonWidget->setLayout(buttonLayout);

	//Layout
	layout = new QBoxLayout(QBoxLayout::TopToBottom);
	summary = new QLabel();
	table = new QWidget();
	layout->addWidget(summary);
	layout->addWidget(buttonWidget);
	layout->addWidget(table);

	//Title
	idTitle = new QLabel("<h3>ID</h3>");
	idTitle->setTextFormat(Qt::RichText);
	idTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	correctTitle = new QLabel("<h3>Correct Questions</h3>");
	correctTitle->setTextFormat(Qt::RichText);
	correctTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	wrongTitle = new QLabel("<h3>Wrong Questions</h3>");
	wrongTitle->setTextFormat(Qt::RichText);
	wrongTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	totalTitle = new QLabel("<h3>Total Questions</h3>");
	totalTitle->setTextFormat(Qt::RichText);
	totalTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	percentTitle = new QLabel("<h3>Percentage Score</h3>");
	percentTitle->setTextFormat(Qt::RichText);
	percentTitle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

//Destructor
ResultWidget::~ResultWidget() {
	delete layout;
	delete table;
	delete tableLayout;
	delete summary;
	delete idTitle;
	delete correctTitle;
	delete wrongTitle;
	delete totalTitle;
	delete percentTitle;
	delete refreshButton;
	delete exportButton;
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

//Refresh display
void ResultWidget::refresh() {
	clearDisplay();
	calculate();
	display();
	update();
}

//Clear display
void ResultWidget::clearDisplay() {
	id.clear();
	correct.clear();
	wrong.clear();
	total.clear();
	percent.clear();
	delete summary;
	delete tableLayout;
	delete table;
	update();
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
		average += correctAnswers[i];
	}
	average /= correctAnswers.size();

	//Get median, max, min
	std::vector<int> correctCopy = correctAnswers;
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
	summary = new QLabel(tr("Average: %1 Median: %2 Min: %3 Max: %4").arg(average).arg(median).arg(min).arg(max));

	//Construct label vectors
	for (unsigned int i = 0; i < idList.size(); i++) {
		id.push_back(new QLabel(tr(idList[i].c_str())));
		correct.push_back(new QLabel(tr("%1").arg(correctAnswers[i])));
		wrong.push_back(new QLabel(tr("%1").arg(wrongAnswers[i])));
		total.push_back(new QLabel(tr("%1").arg(totalQuestions[i])));
		percent.push_back(new QLabel(tr("%1").arg(percentScore[i])));
	}

	//Add labels to grid
	tableLayout = new QGridLayout();
	tableLayout->addWidget(idTitle, 0, 0);
	tableLayout->addWidget(correctTitle, 0, 1);
	tableLayout->addWidget(wrongTitle, 0, 2);
	tableLayout->addWidget(totalTitle, 0, 3);
	tableLayout->addWidget(percentTitle, 0, 4);
	for (unsigned int i = 0; i < id.size(); i++) {
		tableLayout->addWidget(id[i], i + 1, 0);
		tableLayout->addWidget(correct[i], i + 1, 1);
		tableLayout->addWidget(wrong[i], i + 1, 2);
		tableLayout->addWidget(total[i], i + 1, 3);
		tableLayout->addWidget(percent[i], i + 1, 4);
	}

	//New layout
	table->setLayout(tableLayout);

	update();
}

//Export results to CSV
void ResultWidget::exportCSV() {

}

//Export to txt
void ResultWidget::exportTXT() {

}

//Change export name
void ResultWidget::changeExportName(const QString &name) {
	exportName = name;
}

//Change export type
void ResultWidget::changeExportType(int type) {
	exportT = type;
}