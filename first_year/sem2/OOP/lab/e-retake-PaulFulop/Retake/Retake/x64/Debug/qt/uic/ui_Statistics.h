/********************************************************************************
** Form generated from reading UI file 'Statistics.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICS_H
#define UI_STATISTICS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatisticsClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StatisticsClass)
    {
        if (StatisticsClass->objectName().isEmpty())
            StatisticsClass->setObjectName("StatisticsClass");
        StatisticsClass->resize(600, 400);
        menuBar = new QMenuBar(StatisticsClass);
        menuBar->setObjectName("menuBar");
        StatisticsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(StatisticsClass);
        mainToolBar->setObjectName("mainToolBar");
        StatisticsClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(StatisticsClass);
        centralWidget->setObjectName("centralWidget");
        StatisticsClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(StatisticsClass);
        statusBar->setObjectName("statusBar");
        StatisticsClass->setStatusBar(statusBar);

        retranslateUi(StatisticsClass);

        QMetaObject::connectSlotsByName(StatisticsClass);
    } // setupUi

    void retranslateUi(QMainWindow *StatisticsClass)
    {
        StatisticsClass->setWindowTitle(QCoreApplication::translate("StatisticsClass", "Statistics", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatisticsClass: public Ui_StatisticsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICS_H
