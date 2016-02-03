#include "zopperscanapi.hpp"
#include <Algorithm>
#include <QDesktopWidget>

//TODO: Redo for ScanFileWidget

ZopperScanAPI::ZopperScanAPI(QWidget *parent)
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
	setMinimumSize(dw.width() * 0.4, dw.height() * 0.4);

	//Hide toolbar
	ui.mainToolBar->hide();

	//Hide status bar
	statusBar()->hide();

	//Set Title
	setWindowTitle("ScanGrader");
	adjustSize();
}

ZopperScanAPI::~ZopperScanAPI()
{
	delete navbar;
}

//**********Public Slots************

//Refresh UI
void ZopperScanAPI::refresh() {
	adjustSize();
	update();
}

//Calculate results based on current settings
void ZopperScanAPI::calculate() {
	//Get data
	clearVariables();
	getImageData();

	//Calculate keys
	for (unsigned int i = 0; i < keyPaths.size(); i++) {
		keys.push_back(AnalyzeImage(keyPaths.at(i), useFile.at(i)));
	}

	//Get solutions
	solutions.clear();
	for (unsigned int i = 0; i < keys.size(); i++) {
		solutions.push_back(keys.at(i).getAnswers());
	}


	//Calculate images
	for (unsigned int i = 0; i < imagePaths.size(); i++) {
		images.push_back(AnalyzeImage(imagePaths.at(i), useFile.at(useKey.at(i))));
	}

	//Get answers
	answers.clear();
	for (unsigned int i = 0; i < imagePaths.size(); i++) {
		answers.push_back(images.at(i).getAnswers());
	}

	//Get score and percentage score
	score.clear();
	percentScore.clear();
	for (unsigned int i = 0; i < answers.size(); i++) {
		score.push_back(compare(answers[i], solutions[useKey.at(i)]));
		percentScore.push_back((double)score[i] / answers[i].size());
	}

	//Push out to result
	navbar->result->clearDisplay();
	navbar->result->clearData();
	for (unsigned int i = 0; i < answers.size(); i++) {
		navbar->result->addRow(tr("%1").arg(images.at(i).getID()).toStdString(), answers.at(i), solutions.at(useKey.at(i)));
	}
	navbar->result->calculate();
	navbar->result->display();
	navbar->result->update();
}

//Update config file comboboxes
void ZopperScanAPI::updateConfig() {
	QList<QUrl> urls = navbar->config->getFileUrls();

	//Fill comboboxes
	navbar->key->updateConfig(urls);
}

//Update answer key comboboxes
void ZopperScanAPI::updateKeys() {
	QList<QUrl> urls = navbar->key->getKeyUrls();

	//Fill comboboxes
	navbar->image->updateKeys(urls);

	//Local
	keyPaths.clear();
	for (unsigned int i = 0; i < urls.size(); i++) {
		keyPaths.push_back(urls.at(i).toString().toStdString());
	}
}


//**********Private Functions**********

//Clear variables
void ZopperScanAPI::clearVariables() {
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
void ZopperScanAPI::getImageData() {
	//Get Key files
	QList<QUrl> keyFiles = navbar->key->getKeyUrls();
	QList<QUrl> configFiles = navbar->key->getConfigUrls();
	for (unsigned int i = 0; i < keyFiles.size(); i++) {
		keyPaths.push_back(keyFiles.at(i).toLocalFile().toStdString());
		useFile.push_back(configFiles.at(i).toLocalFile().toStdString());
	}

	//Get image files
	QList<QUrl> imageFiles = navbar->image->getImageUrls();
	std::vector<int> keyIndexes = navbar->image->getKeyIndexes();
	for (unsigned int i = 0; i < imageFiles.size(); i++) {
		imagePaths.push_back(imageFiles.at(i).toLocalFile().toStdString());
		useKey.push_back(keyIndexes.at(i));
	}
	
}

//Connect Image
void ZopperScanAPI::connectImage() {
	connect(navbar->image->add, SIGNAL(released()), this, SLOT(refresh()));
	connect(navbar->image->add, SIGNAL(released()), this, SLOT(updateKeys()));
	connect(navbar->image->add, SIGNAL(released()), this, SLOT(updateConfig()));
	connect(navbar->image->calculate, SIGNAL(released()), this, SLOT(calculate()));
	connect(navbar->image->refreshButton, SIGNAL(released()), this, SLOT(updateKeys()));
	connect(navbar->image->refreshButton, SIGNAL(released()), this, SLOT(updateConfig()));
	connect(navbar->image->refreshButton, SIGNAL(released()), this, SLOT(refresh()));
}

//Connect Keys
void ZopperScanAPI::connectKeys() {
	connect(navbar->key->addKey, SIGNAL(released()), this, SLOT(updateKeys()));
	connect(navbar->key->addKey, SIGNAL(released()), this, SLOT(updateConfig()));
	connect(navbar->key->refreshButton, SIGNAL(released()), this, SLOT(updateKeys()));
	connect(navbar->key->refreshButton, SIGNAL(released()), this, SLOT(updateConfig()));
	connect(navbar->key->refreshButton, SIGNAL(released()), this, SLOT(refresh()));
}

//Connect Config
void ZopperScanAPI::connectConfig() {
	connect(navbar->config->addConfig, SIGNAL(released()), this, SLOT(updateConfig()));
}

//Connect Results
void ZopperScanAPI::connectResults() {
	
}

//Connect Export
void ZopperScanAPI::connectExport() {
	//Connect export lines
	connect(navbar->exportW->fileName, SIGNAL(textChanged(const QString)), navbar->result, SLOT(changeExportName(const QString)));
	connect(navbar->exportW->fileType, SIGNAL(currentIndexChanged(int)), navbar->result, SLOT(changeExportType(int)));
	connect(navbar->exportW->radioButtons, SIGNAL(buttonReleased(int)), navbar->result, SLOT(changeExportType(int)));
	connect(navbar->exportW->hostName, SIGNAL(textChanged(const QString)), navbar->result, SLOT(changeHostName(const QString)));
	connect(navbar->exportW->databaseName, SIGNAL(textChanged(const QString)), navbar->result, SLOT(changeDatabaseName(const QString)));
	connect(navbar->exportW->port, SIGNAL(textChanged(const QString)), navbar->result, SLOT(changePort(const QString)));
	connect(navbar->exportW->user, SIGNAL(textChanged(const QString)), navbar->result, SLOT(changeUserName(const QString)));
	connect(navbar->exportW->password, SIGNAL(textChanged(const QString)), navbar->result, SLOT(changePassword(const QString)));
}

//Connect Options
void ZopperScanAPI::connectOptions() {

}

//Connect About
void ZopperScanAPI::connectAbout() {
	navbar->about->updateVersion(version);
}

//Compare two int vectors, returns number of equalities
int ZopperScanAPI::compare(std::vector<int> a, std::vector<int> b) {
	//Size equality check
	if (a.size() != b.size()) {
		return -1;
	}
	int result = 0;
	for (unsigned int i = 0; i < a.size(); i++) {
		if (a[i] == b[i]) {
			result++;
		}
	}
	return result;
}