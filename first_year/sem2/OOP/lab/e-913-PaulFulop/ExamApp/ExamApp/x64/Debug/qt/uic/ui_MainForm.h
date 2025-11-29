/********************************************************************************
** Form generated from reading UI file 'MainForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainFormClass
{
public:
    QWidget *centralWidget;
    QListWidget *listWidgetDepartments;

    void setupUi(QMainWindow *MainFormClass)
    {
        if (MainFormClass->objectName().isEmpty())
            MainFormClass->setObjectName("MainFormClass");
        MainFormClass->resize(449, 415);
        centralWidget = new QWidget(MainFormClass);
        centralWidget->setObjectName("centralWidget");
        listWidgetDepartments = new QListWidget(centralWidget);
        listWidgetDepartments->setObjectName("listWidgetDepartments");
        listWidgetDepartments->setGeometry(QRect(10, 10, 421, 391));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        listWidgetDepartments->setFont(font);
        MainFormClass->setCentralWidget(centralWidget);

        retranslateUi(MainFormClass);

        QMetaObject::connectSlotsByName(MainFormClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainFormClass)
    {
        MainFormClass->setWindowTitle(QCoreApplication::translate("MainFormClass", "MainForm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainFormClass: public Ui_MainFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
