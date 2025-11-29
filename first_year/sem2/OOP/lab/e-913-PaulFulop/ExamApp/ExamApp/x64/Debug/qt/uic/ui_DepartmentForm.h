/********************************************************************************
** Form generated from reading UI file 'DepartmentForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPARTMENTFORM_H
#define UI_DEPARTMENTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DepartmentFormClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QListWidget *listWidgetVolunteers;
    QListWidget *listWidgetUnassigned;
    QPushButton *pushButton_2;
    QLabel *labelDesc;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEditName;
    QLabel *label_2;
    QLineEdit *lineEditEmail;
    QLabel *label_3;
    QLineEdit *lineEditList;
    QPushButton *pushButton;

    void setupUi(QMainWindow *DepartmentFormClass)
    {
        if (DepartmentFormClass->objectName().isEmpty())
            DepartmentFormClass->setObjectName("DepartmentFormClass");
        DepartmentFormClass->resize(875, 544);
        centralWidget = new QWidget(DepartmentFormClass);
        centralWidget->setObjectName("centralWidget");
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        listWidgetVolunteers = new QListWidget(centralWidget);
        listWidgetVolunteers->setObjectName("listWidgetVolunteers");
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        listWidgetVolunteers->setFont(font);

        gridLayout_2->addWidget(listWidgetVolunteers, 0, 0, 1, 2);

        listWidgetUnassigned = new QListWidget(centralWidget);
        listWidgetUnassigned->setObjectName("listWidgetUnassigned");
        listWidgetUnassigned->setFont(font);

        gridLayout_2->addWidget(listWidgetUnassigned, 0, 2, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout_2->addWidget(pushButton_2, 1, 2, 1, 1);

        labelDesc = new QLabel(centralWidget);
        labelDesc->setObjectName("labelDesc");
        labelDesc->setFont(font);

        gridLayout_2->addWidget(labelDesc, 2, 1, 1, 2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 2);

        lineEditName = new QLineEdit(groupBox);
        lineEditName->setObjectName("lineEditName");

        gridLayout->addWidget(lineEditName, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        lineEditEmail = new QLineEdit(groupBox);
        lineEditEmail->setObjectName("lineEditEmail");

        gridLayout->addWidget(lineEditEmail, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEditList = new QLineEdit(groupBox);
        lineEditList->setObjectName("lineEditList");

        gridLayout->addWidget(lineEditList, 2, 1, 1, 2);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 3, 0, 1, 3);


        gridLayout_2->addWidget(groupBox, 1, 0, 2, 1);

        DepartmentFormClass->setCentralWidget(centralWidget);

        retranslateUi(DepartmentFormClass);

        QMetaObject::connectSlotsByName(DepartmentFormClass);
    } // setupUi

    void retranslateUi(QMainWindow *DepartmentFormClass)
    {
        DepartmentFormClass->setWindowTitle(QCoreApplication::translate("DepartmentFormClass", "DepartmentForm", nullptr));
        pushButton_2->setText(QCoreApplication::translate("DepartmentFormClass", "See top 3", nullptr));
        labelDesc->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("DepartmentFormClass", "Add ", nullptr));
        label->setText(QCoreApplication::translate("DepartmentFormClass", "Name:", nullptr));
        label_2->setText(QCoreApplication::translate("DepartmentFormClass", "Email:", nullptr));
        label_3->setText(QCoreApplication::translate("DepartmentFormClass", "List:", nullptr));
        pushButton->setText(QCoreApplication::translate("DepartmentFormClass", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DepartmentFormClass: public Ui_DepartmentFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPARTMENTFORM_H
