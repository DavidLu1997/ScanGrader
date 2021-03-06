#include "scangrader.hpp"
#include <algorithm>
#include <QtWidgets/qdesktopwidget.h>

ScanGrader::ScanGrader(QWidget *parent)
	: QMainWindow(parent)
{
	//Set up UI
	ui.setupUi(this);

	//Add navbar to window
	navbar = new NavBar(this);
	navbar->adjustSize();
	setCentralWidget(navbar);

	//Connect buttons
	connectImage();
	connectConfig();
	connectExport();
	connectKeys();
	connectOptions();
	connectResults();
	connectAbout();

	//Set Size
	QDesktopWidget dw;
	//If desktop width *0.4 is less than 800, set minimum width to 800 and height to 400
	if (dw.width() * 0.4 < 800) {
		setMinimumSize(800, 400);
	}
	else {
		setMinimumSize(dw.width() * 0.4, dw.height() * 0.4);
	}

	//Hide toolbar
	ui.mainToolBar->hide();

	//Status
	status = new QLabel("Idle");
	statusBar()->addWidget(status);

	//Progress bar
	progress = navbar->image->progress;
	progress->setAlignment(Qt::AlignRight);
	statusBar()->addWidget(progress);
	//progress->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	//Ensure dragger displayed
	statusBar()->setSizeGripEnabled(true);

	//Set Title
	setWindowTitle("ScanGrader");
	adjustSize();
}

ScanGrader::~ScanGrader()
{
	delete navbar;
}

//**********Public Slots************

//Refresh UI
void ScanGrader::refresh() {
	adjustSize();
	update();
}

//Calculate results based on current settings
void ScanGrader::calculate() {
	//Get data
	clearVariables();
	getImageData();

	//Check
	if (keyPaths.empty() || imagePaths.empty() || useFile.empty() || useKey.empty()) {
		progress->reset();
		progress->setVisible(false);
		return;
	}

	//Initialize progress
	status->setText("Calculating: ");
	progress->setMinimum(0);
	progress->setValue(0);
	progress->setVisible(true);

	//Calculate number of images needed
	unsigned int numImage = keyPaths.size() + imagePaths.size();
	//Calculate number of other actions needed
	unsigned int others = keyPaths.size() + imagePaths.size() * 3;
	progress->setMaximum(numImage * 5 + others);

	//Calculate keys
	for (unsigned int i = 0; i < keyPaths.size(); i++) {
		progress->setValue(progress->value() + 5);
		keys.push_back(AnalyzeImage(keyPaths.at(i), useFile.at(i)));
	}

	//Get solutions
	solutions.clear();
	for (unsigned int i = 0; i < keys.size(); i++) {
		progress->setValue(progress->value() + 1);
		solutions.push_back(keys.at(i).getAnswers());
	}


	//Calculate images
	for (unsigned int i = 0; i < imagePaths.size(); i++) {
		progress->setValue(progress->value() + 5);
		images.push_back(AnalyzeImage(imagePaths.at(i), useFile.at(useKey.at(i))));
	}

	//Get answers
	answers.clear();
	for (unsigned int i = 0; i < imagePaths.size(); i++) {
		progress->setValue(progress->value() + 1);
		answers.push_back(images.at(i).getAnswers());
	}

	//Get score and percentage score
	score.clear();
	percentScore.clear();
	for (unsigned int i = 0; i < answers.size(); i++) {
		progress->setValue(progress->value() + 2);
		score.push_back(compare(answers[i], solutions[useKey.at(i)]));
		percentScore.push_back((double)score[i] / answers[i].size());
	}

	//Push out to result
	navbar->result->clearDisplay();
	navbar->result->clearData();
	for (unsigned int i = 0; i < answers.size(); i++) {
		progress->setValue(progress->value() + 1);
		navbar->result->addRow(tr("%1").arg(images.at(i).getID()).toStdString(), answers.at(i), solutions.at(useKey.at(i)));
	}
	navbar->result->calculate();
	navbar->result->display();
	navbar->result->update();
	progress->reset();
	progress->setVisible(false);
	status->setText("Idle");
}

//Update config file comboboxes
void ScanGrader::updateConfig() {
	QList<QUrl> urls = navbar->config->getFileUrls();

	//Fill comboboxes
	navbar->key->updateConfig(urls);
}

//Update answer key comboboxes
void ScanGrader::updateKeys() {
	QList<QUrl> urls = navbar->key->getKeyUrls();

	//Fill comboboxes
	navbar->image->updateKeys(urls);

	//Local
	keyPaths.clear();
	for (unsigned int i = 0; i < urls.size(); i++) {
		keyPaths.push_back(urls.at(i).toString().toStdString());
	}
}

//Update percent
void ScanGrader::updatePercent(int value) {
	AnalyzeImage::percentage = value / 100.0;
}

//Update threshold
void ScanGrader::updateThreshold(int value) {
	AnalyzeImage::threshold = value;
}


//**********Private Functions**********

//Clear variables
void ScanGrader::clearVariables() {
	images.clear();
	imagePaths.clear();
	useKey.clear();
	keys.clear();
	keyPaths.clear();
	useFile.clear();
	score.clear();
	percentScore.clear();
	answers.clear();
	solutions.clear();
}

//Get image data
void ScanGrader::getImageData() {
	//Get Key files
	QList<QUrl> keyFiles = navbar->key->getKeyUrls();
	QList<QUrl> configFiles = navbar->key->getConfigUrls();
	if (configFiles.empty() || keyFiles.empty()) {
		return;
	}
	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		keyPaths.push_back(keyFiles.at(i).toLocalFile().toStdString());
		useFile.push_back(configFiles.at(i).toLocalFile().toStdString());
	}

	//Get image files
	QList<QUrl> imageFiles = navbar->image->getImageUrls();
	std::vector<int> keyIndexes = navbar->image->getKeyIndexes();
	if (imageFiles.empty() || keyIndexes.empty()) {
		return;
	}
	for (unsigned int i = 0; i < imageFiles.size(); i++) {
		imagePaths.push_back(imageFiles.at(i).toLocalFile().toStdString());
		useKey.push_back(keyIndexes.at(i));
	}

}

//Connect Image
void ScanGrader::connectImage() {
	connect(navbar->image->add, SIGNAL(released()), this, SLOT(refresh()));
	connect(navbar->image->add, SIGNAL(released()), this, SLOT(updateKeys()));
	connect(navbar->image->add, SIGNAL(released()), this, SLOT(updateConfig()));
	connect(navbar->image->calculate, SIGNAL(released()), this, SLOT(calculate()));
	connect(navbar->image->refreshButton, SIGNAL(released()), this, SLOT(updateKeys()));
	connect(navbar->image->refreshButton, SIGNAL(released()), this, SLOT(updateConfig()));
	connect(navbar->image->refreshButton, SIGNAL(released()), this, SLOT(refresh()));
}

//Connect Keys
void ScanGrader::connectKeys() {
	connect(navbar->key->addKey, SIGNAL(released()), this, SLOT(updateKeys()));
	connect(navbar->key->addKey, SIGNAL(released()), this, SLOT(updateConfig()));
	connect(navbar->key->refreshButton, SIGNAL(released()), this, SLOT(updateKeys()));
	connect(navbar->key->refreshButton, SIGNAL(released()), this, SLOT(updateConfig()));
	connect(navbar->key->refreshButton, SIGNAL(released()), this, SLOT(refresh()));
}

//Connect Config
void ScanGrader::connectConfig() {
	connect(navbar->config->addConfig, SIGNAL(released()), this, SLOT(updateConfig()));
}

//Connect Results
void ScanGrader::connectResults() {

}

//Connect Export
void ScanGrader::connectExport() {
	//Connect export lines
	connect(navbar->exportW->fileName, SIGNAL(textChanged(const QString)), navbar->result, SLOT(changeExportName(const QString)));
	connect(navbar->exportW->fileType, SIGNAL(currentIndexChanged(int)), navbar->result, SLOT(changeExportType(int)));
}

//Connect Options
void ScanGrader::connectOptions() {
	connect(navbar->option->threshold, SIGNAL(valueChanged(int)), this, SLOT(updateThreshold(int)));
	connect(navbar->option->percent, SIGNAL(valueChanged(int)), this, SLOT(updatePercent(int)));
	connect(navbar->option->thresholdValue, SIGNAL(valueChanged(int)), this, SLOT(updateThreshold(int)));
	connect(navbar->option->percentValue, SIGNAL(valueChanged(int)), this, SLOT(updatePercent(int)));
}

//Connect About
void ScanGrader::connectAbout() {
	navbar->about->updateVersion(version);
}

//Compare two int vectors, returns number of equalities
template <typename T>
unsigned int ScanGrader::compare(std::vector<T> a, std::vector<T> b) {
	//Size equality check
	if (a.size() != b.size()) {
		return -1;
	}
	unsigned int result = 0;
	for (unsigned int i = 0; i < a.size(); i++) {
		if (a[i] == b[i]) {
			result++;
		}
	}
	return result;
}
