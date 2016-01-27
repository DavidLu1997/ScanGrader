#ifndef KEYFILEWIDGET_H
#define KEYFILEWIDGET_H

#include <QtWidgets\QWidget>
#include <QtWidgets\QGridLayout>
#include <QtWidgets\QLabel>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QPushButton>
#include <QUrl>

class KeyFileWidget : public QWidget {

	Q_OBJECT

public:
	//Constructor
	KeyFileWidget(QUrl URL, QGridLayout *layout, unsigned int row, QWidget *parent = 0);

	//Destructor
	~KeyFileWidget();

	//Get URL
	QUrl getUrl();

	//Get name
	QString getName();

	//Get configName
	QUrl getConfigUrl();

	//Update config files
	void updateConfigFiles(const QList<QUrl> &urls);

	//Remove button
	QPushButton *remove;

public slots:

private slots :
	

private:

	//Url
	QUrl *url;

	//Config files
	QList<QUrl> configUrls;

	//Name Label
	QLabel *name;

	//Path Label
	QLabel *path;

	//Config file
	QComboBox *configFile;
};

#endif