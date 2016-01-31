#include "ExportWidget.hpp"

//Constructor
ExportWidget::ExportWidget(QWidget *parent) {
	QWidget();

	//Initialize buttons
	radioButtons = new QButtonGroup();

	//Radio buttons
	fileButton = new QRadioButton("Local File");
	sqlButton = new QRadioButton("SQL Database");
	radioButtons->addButton(fileButton);
	radioButtons->setId(fileButton, 1);
	radioButtons->addButton(sqlButton);
	radioButtons->setId(sqlButton, 2);

	//Widgets
	fileWidget = new QWidget();
	fileLayout = new QGridLayout();
	sqlWidget = new QWidget();
	sqlLayout = new QGridLayout();

	//Text
	fileLabel = new QLabel("File Name: ");
	fileLayout->addWidget(fileLabel, 0, 0);
	fileName = new QLineEdit();
	fileLayout->addWidget(fileName, 0, 1);
	fileTypeLabel = new QLabel("File Type: ");
	fileLayout->addWidget(fileTypeLabel, 1, 0);
	fileType = new QComboBox();
	fileType->addItem(".CSV");
	fileType->addItem(".TXT");
	fileLayout->addWidget(fileType, 1, 1);
	QWidget *empty1 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	fileLayout->addWidget(empty1, 999, 0);
	QWidget *empty2 = new QWidget();
	empty2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	fileLayout->addWidget(empty2, 999, 1);

	fileWidget->setLayout(fileLayout);

	//SQL
	serverLabel = new QLabel("Server Name: ");
	sqlLayout->addWidget(serverLabel, 0, 0);
	serverName = new QLineEdit();
	sqlLayout->addWidget(serverName, 0, 1);
	portLabel = new QLabel("Port: ");
	sqlLayout->addWidget(portLabel, 1, 0);
	port = new QLineEdit();
	sqlLayout->addWidget(port, 1, 1);
	userLabel = new QLabel("Username: ");
	sqlLayout->addWidget(userLabel, 2, 0);
	user = new QLineEdit();
	sqlLayout->addWidget(user, 2, 1);
	passwordLabel = new QLabel("Password: ");
	sqlLayout->addWidget(passwordLabel, 3, 0);
	password = new QLineEdit();
	password->setEchoMode(QLineEdit::Password);
	sqlLayout->addWidget(password, 3, 1);
	test = new QPushButton("Test Connection");
	sqlLayout->addWidget(test, 4, 0);
	QWidget *empty3 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sqlLayout->addWidget(empty3, 999, 0);
	QWidget *empty4 = new QWidget();
	empty2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sqlLayout->addWidget(empty4, 999, 1);

	sqlWidget->setLayout(sqlLayout);

	//Main widget
	layout = new QGridLayout();

	intro = new QLabel("Export type: ");
	layout->addWidget(intro, 0, 0);
	layout->addWidget(fileButton, 1, 0);
	layout->addWidget(sqlButton, 1, 1);
	layout->addWidget(fileWidget, 2, 0);
	layout->addWidget(sqlWidget, 2, 1);
	apply = new QPushButton("Apply");
	layout->addWidget(apply, 1000, 0);
	QWidget *empty5 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty5, 999, 0);
	QWidget *empty6 = new QWidget();
	empty2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty6, 999, 1);
	setLayout(layout);

	//Connect
	connect(radioButtons, SIGNAL(buttonReleased(int)), this, SLOT(selectionChanged(int)));
	fileButton->setChecked(true);
	selectionChanged(1);
	
}

//Destructor
ExportWidget::~ExportWidget() {
	delete radioButtons;
	delete fileName;
	delete fileLabel;
	delete fileType;
	delete fileTypeLabel;
	delete serverName;
	delete serverLabel;
	delete port;
	delete portLabel;
	delete user;
	delete userLabel;
	delete password;
	delete passwordLabel;
	delete apply;
	delete fileButton;
	delete sqlButton;
	delete fileWidget;
	delete sqlWidget;
	delete layout;
	delete fileLayout;
	delete sqlLayout;
	delete test;
}

//Change selection
void ExportWidget::selectionChanged(int id) {
	switch (id) {
	case 1:
		fileWidget->setEnabled(true);
		sqlWidget->setEnabled(false);
		break;

	case 2:
		sqlWidget->setEnabled(true);
		fileWidget->setEnabled(false);
		break;
	default:
		break;
	}
}