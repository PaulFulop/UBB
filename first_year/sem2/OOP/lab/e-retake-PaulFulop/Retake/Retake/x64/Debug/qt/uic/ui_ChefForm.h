/********************************************************************************
** Form generated from reading UI file 'ChefForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHEFFORM_H
#define UI_CHEFFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChefFormClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QListWidget *listWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEditName;
    QLabel *label_2;
    QLineEdit *lineEditPrep;
    QLabel *label_3;
    QLineEdit *lineEditIng;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonView;
    QCheckBox *checkBox;
    QLineEdit *lineEditSearch;

    void setupUi(QMainWindow *ChefFormClass)
    {
        if (ChefFormClass->objectName().isEmpty())
            ChefFormClass->setObjectName("ChefFormClass");
        ChefFormClass->resize(655, 535);
        centralWidget = new QWidget(ChefFormClass);
        centralWidget->setObjectName("centralWidget");
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName("listWidget");

        gridLayout_2->addWidget(listWidget, 0, 0, 2, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEditName = new QLineEdit(groupBox);
        lineEditName->setObjectName("lineEditName");

        gridLayout->addWidget(lineEditName, 0, 1, 1, 3);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 3);

        lineEditPrep = new QLineEdit(groupBox);
        lineEditPrep->setObjectName("lineEditPrep");

        gridLayout->addWidget(lineEditPrep, 1, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 2);

        lineEditIng = new QLineEdit(groupBox);
        lineEditIng->setObjectName("lineEditIng");

        gridLayout->addWidget(lineEditIng, 2, 2, 1, 2);

        pushButtonAdd = new QPushButton(groupBox);
        pushButtonAdd->setObjectName("pushButtonAdd");

        gridLayout->addWidget(pushButtonAdd, 3, 1, 1, 3);


        gridLayout_2->addWidget(groupBox, 0, 1, 1, 1);

        pushButtonView = new QPushButton(centralWidget);
        pushButtonView->setObjectName("pushButtonView");

        gridLayout_2->addWidget(pushButtonView, 1, 1, 1, 1);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName("checkBox");

        gridLayout_2->addWidget(checkBox, 2, 0, 1, 1);

        lineEditSearch = new QLineEdit(centralWidget);
        lineEditSearch->setObjectName("lineEditSearch");

        gridLayout_2->addWidget(lineEditSearch, 3, 0, 1, 1);

        ChefFormClass->setCentralWidget(centralWidget);

        retranslateUi(ChefFormClass);

        QMetaObject::connectSlotsByName(ChefFormClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChefFormClass)
    {
        ChefFormClass->setWindowTitle(QCoreApplication::translate("ChefFormClass", "ChefForm", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ChefFormClass", "Add new recipe", nullptr));
        label->setText(QCoreApplication::translate("ChefFormClass", "Name:", nullptr));
        label_2->setText(QCoreApplication::translate("ChefFormClass", "Preparation time:", nullptr));
        label_3->setText(QCoreApplication::translate("ChefFormClass", "Ingredients:", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("ChefFormClass", "Add", nullptr));
        pushButtonView->setText(QCoreApplication::translate("ChefFormClass", "View", nullptr));
        checkBox->setText(QCoreApplication::translate("ChefFormClass", "Show only recipes for your speciality", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChefFormClass: public Ui_ChefFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHEFFORM_H
