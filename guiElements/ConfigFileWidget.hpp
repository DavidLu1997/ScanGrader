#ifndef CONFIGFILEWIDGET_H
#define CONFIGFILEWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QGridLayout>
#include <QtWidgets\QLabel>
#include <QtWidgets\QPushButton>
#include <QUrl>

class ConfigFileWidget : public QWidget {

Q_OBJECT

public:
	//Constructor
	ConfigFileWidget(QUrl URL, QGridLayout *layout, unsigned int row, QWidget *parent = 0);

	//Destructor
	~ConfigFileWidget();

	//Get URL
	QUrl getUrl();

	//Get name
	QString getName();

	//Remove button
	QPushButton *remove;

	bool deleted = false;

public slots:
	void setDeleted();
private slots :
	
private:
	
	//Url
	QUrl url;

	//Name Label
	QLabel *name;

	//Path Label
	QLabel *path;
};

#endif