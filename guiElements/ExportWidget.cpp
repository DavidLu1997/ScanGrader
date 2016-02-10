#include "ExportWidget.hpp"

//Constructor
ExportWidget::ExportWidget(QWidget *parent) {
	QWidget();

	//Initialize buttons
	radioButtons = new QButtonGroup();

	//Radio buttons
	fileButton = new QRadioButton("Local File");
	sqlButton = new QRadioButton("SQL Database (DISABLED)");
	sqlButton->setDisabled(true);
	radioButtons->addButton(fileButton);
	radioButtons->setId(fileButton, 1);
	fileButton->setChecked(true);
	//radioButtons->addButton(sqlButton);
	//radioButtons->setId(sqlButton, 2);

	//Widgets
	fileWidget = new QWidget();
	fileLayout = new QGridLayout();
	sqlWidget = new QWidget();
	sqlLayout = new QGridLayout();

	//Text
	fileLabel = new QLabel("File Name: ");
	fileLayout->addWidget(fileLabel, 0, 0);
	fileName = new QLineEdit();
	fileName->setText("result");
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
	/*
	hostLabel = new QLabel("Host Name: ");
	sqlLayout->addWidget(hostLabel, 0, 0);
	hostName = new QLineEdit();
	sqlLayout->addWidget(hostName, 0, 1);
	databaseLabel = new QLabel("Database Name: ");
	sqlLayout->addWidget(databaseLabel, 1, 0);
	databaseName = new QLineEdit();
	sqlLayout->addWidget(databaseName, 1, 1);
	portLabel = new QLabel("Port: ");
	sqlLayout->addWidget(portLabel, 2, 0);
	port = new QLineEdit();
	port->setValidator(new QIntValidator(0, 10000, this));
	sqlLayout->addWidget(port, 2, 1);
	userLabel = new QLabel("Username: ");
	sqlLayout->addWidget(userLabel, 3, 0);
	user = new QLineEdit();
	sqlLayout->addWidget(user, 3, 1);
	passwordLabel = new QLabel("Password: ");
	sqlLayout->addWidget(passwordLabel, 4, 0);
	password = new QLineEdit();
	password->setEchoMode(QLineEdit::PasswordEchoOnEdit);
	sqlLayout->addWidget(password, 4, 1);
	test = new QPushButton("Test Connection");
	sqlLayout->addWidget(test, 5, 0);
	connectStatus = new QLabel("Untested");
	sqlLayout->addWidget(connectStatus, 5, 1);
	QWidget *empty3 = new QWidget();
	empty1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sqlLayout->addWidget(empty3, 999, 0);
	QWidget *empty4 = new QWidget();
	empty2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sqlLayout->addWidget(empty4, 999, 1);

	sqlWidget->setLayout(sqlLayout);
	*/

	//Main widget
	layout = new QGridLayout();

	intro = new QLabel("<h3>Export type:</h3>");
	intro->setTextFormat(Qt::RichText); 
	layout->addWidget(intro, 0, 0);
	layout->addWidget(fileButton, 1, 0);
	//layout->addWidget(sqlButton, 1, 1);
	layout->addWidget(fileWidget, 2, 0);
	//layout->addWidget(sqlWidget, 2, 1);
	QWidget *empty5 = new QWidget();
	empty5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty5, 999, 0);
	QWidget *empty6 = new QWidget();
	empty6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(empty6, 999, 1);
	setLayout(layout);

	//Connect
	connect(radioButtons, SIGNAL(buttonReleased(int)), this, SLOT(selectionChanged(int)));
	//connect(test, SIGNAL(released()), this, SLOT(testConnection()));
	//connect(hostName, SIGNAL(textChanged(const QString)), this, SLOT(statusReset(const QString)));
	//connect(databaseName, SIGNAL(textChanged(const QString)), this, SLOT(statusReset(const QString)));
	//connect(port, SIGNAL(textChanged(const QString)), this, SLOT(statusReset(const QString)));
	//connect(user, SIGNAL(textChanged(const QString)), this, SLOT(statusReset(const QString)));
	//connect(password, SIGNAL(textChanged(const QString)), this, SLOT(statusReset(const QString)));
	//fileButton->setChecked(true);
	selectionChanged(1);
	
}

//Destructor
ExportWidget::~ExportWidget() {
	delete layout;
}

//**********Public Slots***********

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

//Test connection
void ExportWidget::testConnection() {
	//TODO Test
	if (connectionGood) {
		connectStatus->setText("Connection Successful");
	}
	else {
		connectStatus->setText("Connection Failed");
	}
}

//Reset status
void ExportWidget::statusReset(const QString &text) {
	connectStatus->setText("Untested");
}