//About widget
//Contains About for ZopperScan

#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QBoxLayout>
#include <QtWidgets\QLabel>

class AboutWidget : public QWidget {
	Q_OBJECT

public:
	//Constructor
	AboutWidget(QWidget *parent = 0);

	//Destructor
	~AboutWidget();

	//Version
	QLabel *version;

	public slots:

	//Update version
	void updateVersion(double ver);

public slots:

private slots:

private:
	//Main layout
	QBoxLayout *layout;

	//Labels
	QLabel *title;
	QLabel *desc;
	QLabel *authors;
};

#endif