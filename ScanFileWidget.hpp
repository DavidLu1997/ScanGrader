//ScanFile Widget
//Displays a file to be scanned, its ID, the config file to use, and the answer key to use

#ifndef SCANFILEWIDGET_H
#define SCANFILEWIDGET_H

#include <QtWidgets\QWidget>

class ScanFileWidget : public QWidget  {
	Q_OBJECT

public:
	//Constructor
	ScanFileWidget(QWidget *parent = 0);

	//Destructor
	~ScanFileWidget();

public slots:
	
private slots:
	
private:

};

#endif