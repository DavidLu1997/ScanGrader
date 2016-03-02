/********************************************************************************
** Form generated from reading UI file 'scangrader.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANGRADER_H
#define UI_SCANGRADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZopperScanAPIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ZopperScanAPIClass)
    {
        if (ZopperScanAPIClass->objectName().isEmpty())
            ZopperScanAPIClass->setObjectName(QStringLiteral("ZopperScanAPIClass"));
        ZopperScanAPIClass->resize(600, 400);
        menuBar = new QMenuBar(ZopperScanAPIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ZopperScanAPIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ZopperScanAPIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ZopperScanAPIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ZopperScanAPIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ZopperScanAPIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ZopperScanAPIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ZopperScanAPIClass->setStatusBar(statusBar);

        retranslateUi(ZopperScanAPIClass);

        QMetaObject::connectSlotsByName(ZopperScanAPIClass);
    } // setupUi

    void retranslateUi(QMainWindow *ZopperScanAPIClass)
    {
        ZopperScanAPIClass->setWindowTitle(QApplication::translate("ZopperScanAPIClass", "ZopperScanAPI", 0));
    } // retranslateUi

};

namespace Ui {
    class ZopperScanAPIClass: public Ui_ZopperScanAPIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANGRADER_H
