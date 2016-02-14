//Export widget
//Exports results for ZopperScan onto:
//CSV, TXT

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

	//Textboxes
	QLineEdit *fileName;
	QLabel *fileLabel;
	QComboBox *fileType;
	QLabel *fileTypeLabel;

public slots:

private slots:
	
private:

	//Introduction label
	QLabel *intro;

	//Layout
	QGridLayout *layout;
	
	//Radio buttons
	QRadioButton *fileButton;

	//Widgets
	QWidget *fileWidget;
	QGridLayout *fileLayout;

	//Connection status
	QLabel *connectStatus;
};

#endif