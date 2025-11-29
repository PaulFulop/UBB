/********************************************************************************
** Form generated from reading UI file 'Test3Form.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST3FORM_H
#define UI_TEST3FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Test3FormClass
{
public:
    QWidget *centralWidget;
    QListWidget *listWidgetDocs;
    QLineEdit *lineEditSearch;
    QLabel *label;
    QLabel *label_2;
    QLabel *labelSImilarity;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Test3FormClass)
    {
        if (Test3FormClass->objectName().isEmpty())
            Test3FormClass->setObjectName("Test3FormClass");
        Test3FormClass->resize(488, 361);
        centralWidget = new QWidget(Test3FormClass);
        centralWidget->setObjectName("centralWidget");
        listWidgetDocs = new QListWidget(centralWidget);
        listWidgetDocs->setObjectName("listWidgetDocs");
        listWidgetDocs->setGeometry(QRect(20, 10, 311, 192));
        lineEditSearch = new QLineEdit(centralWidget);
        lineEditSearch->setObjectName("lineEditSearch");
        lineEditSearch->setGeometry(QRect(120, 230, 141, 24));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 230, 81, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 270, 51, 16));
        labelSImilarity = new QLabel(centralWidget);
        labelSImilarity->setObjectName("labelSImilarity");
        labelSImilarity->setGeometry(QRect(120, 270, 91, 16));
        Test3FormClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Test3FormClass);
        statusBar->setObjectName("statusBar");
        Test3FormClass->setStatusBar(statusBar);

        retranslateUi(Test3FormClass);

        QMetaObject::connectSlotsByName(Test3FormClass);
    } // setupUi

    void retranslateUi(QMainWindow *Test3FormClass)
    {
        Test3FormClass->setWindowTitle(QCoreApplication::translate("Test3FormClass", "Test3Form", nullptr));
        label->setText(QCoreApplication::translate("Test3FormClass", "Search doc:", nullptr));
        label_2->setText(QCoreApplication::translate("Test3FormClass", "Similarity:", nullptr));
        labelSImilarity->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Test3FormClass: public Ui_Test3FormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST3FORM_H
