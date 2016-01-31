//Export widget
//Exports results for ZopperScan onto:
//CSV
//SQL Server
//Etc.

#ifndef EXPORTWIDGET_H
#define EXPORTWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QRadioButton>
#include <QtWidgets\QButtonGroup>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QGridLayout>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QLineEdit>
#include <QtWidgets\QLabel>

class ExportWidget : public QWidget
{
	Q_OBJECT

public:
	//Constructor
	ExportWidget(QWidget *parent = 0);

	//Destructor
	~ExportWidget();

	//ButtonGroup
	QButtonGroup *radioButtons;

	//Textboxes
	QLineEdit *fileName;
	QLabel *fileLabel;
	QComboBox *fileType;
	QLabel *fileTypeLabel;

	//Server info
	QLineEdit *hostName;
	QLabel *hostLabel;
	QLineEdit *databaseName;
	QLabel *databaseLabel;
	QLineEdit *port;
	QLabel *portLabel;
	QLineEdit *user;
	QLabel *userLabel;
	QLineEdit *password;
	QLabel *passwordLabel;

	//Test
	QPushButton *test;

	//Connection good
	bool connectionGood = false;

public slots:
	//Change selection
	void selectionChanged(int id);

	//Test connection
	void testConnection();

	//Status reset
	void statusReset(const QString &text);

private slots:
	
private:

	//Introduction label
	QLabel *intro;

	//Layout
	QGridLayout *layout;
	
	//Radio buttons
	QRadioButton *fileButton;
	QRadioButton *sqlButton;

	//Widgets
	QWidget *fileWidget;
	QGridLayout *fileLayout;
	QWidget *sqlWidget;
	QGridLayout *sqlLayout;

	//Connection status
	QLabel *connectStatus;
};

#endif