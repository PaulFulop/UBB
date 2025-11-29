/********************************************************************************
** Form generated from reading UI file 'UserForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERFORM_H
#define UI_USERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserWindowClass
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidgetUserEvents;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QComboBox *comboBoxMonths;
    QPushButton *pushButtonNext;
    QLabel *label;
    QTableWidget *tableWidgetAdminEvents;
    QPushButton *pushButtonAdd;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UserWindowClass)
    {
        if (UserWindowClass->objectName().isEmpty())
            UserWindowClass->setObjectName("UserWindowClass");
        UserWindowClass->resize(1376, 545);
        centralwidget = new QWidget(UserWindowClass);
        centralwidget->setObjectName("centralwidget");
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        tableWidgetUserEvents = new QTableWidget(groupBox_2);
        if (tableWidgetUserEvents->columnCount() < 5)
            tableWidgetUserEvents->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetUserEvents->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetUserEvents->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetUserEvents->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QFont font;
        font.setPointSize(7);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        tableWidgetUserEvents->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetUserEvents->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetUserEvents->setObjectName("tableWidgetUserEvents");
        tableWidgetUserEvents->setRowCount(0);
        tableWidgetUserEvents->setColumnCount(5);

        gridLayout_2->addWidget(tableWidgetUserEvents, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        comboBoxMonths = new QComboBox(groupBox);
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->addItem(QString());
        comboBoxMonths->setObjectName("comboBoxMonths");
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setStyleStrategy(QFont::PreferDefault);
        comboBoxMonths->setFont(font1);
        comboBoxMonths->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToMinimumContentsLengthWithIcon);

        gridLayout->addWidget(comboBoxMonths, 4, 0, 1, 1);

        pushButtonNext = new QPushButton(groupBox);
        pushButtonNext->setObjectName("pushButtonNext");
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        pushButtonNext->setFont(font2);

        gridLayout->addWidget(pushButtonNext, 2, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setFont(font2);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 5, 0, 1, 1);

        tableWidgetAdminEvents = new QTableWidget(groupBox);
        if (tableWidgetAdminEvents->columnCount() < 5)
            tableWidgetAdminEvents->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetAdminEvents->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetAdminEvents->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetAdminEvents->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font);
        tableWidgetAdminEvents->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetAdminEvents->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        tableWidgetAdminEvents->setObjectName("tableWidgetAdminEvents");
        tableWidgetAdminEvents->setRowCount(0);
        tableWidgetAdminEvents->setColumnCount(5);

        gridLayout->addWidget(tableWidgetAdminEvents, 0, 0, 1, 1);

        pushButtonAdd = new QPushButton(groupBox);
        pushButtonAdd->setObjectName("pushButtonAdd");
        pushButtonAdd->setFont(font2);

        gridLayout->addWidget(pushButtonAdd, 3, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        UserWindowClass->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(UserWindowClass);
        statusbar->setObjectName("statusbar");
        UserWindowClass->setStatusBar(statusbar);

        retranslateUi(UserWindowClass);

        QMetaObject::connectSlotsByName(UserWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *UserWindowClass)
    {
        UserWindowClass->setWindowTitle(QCoreApplication::translate("UserWindowClass", "User Events", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("UserWindowClass", "Your List", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetUserEvents->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("UserWindowClass", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetUserEvents->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("UserWindowClass", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetUserEvents->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("UserWindowClass", "Date and Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetUserEvents->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("UserWindowClass", "Number of Participants", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetUserEvents->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("UserWindowClass", "Link", nullptr));
        groupBox->setTitle(QCoreApplication::translate("UserWindowClass", "Add events to your list", nullptr));
        comboBoxMonths->setItemText(0, QCoreApplication::translate("UserWindowClass", "0", nullptr));
        comboBoxMonths->setItemText(1, QCoreApplication::translate("UserWindowClass", "1", nullptr));
        comboBoxMonths->setItemText(2, QCoreApplication::translate("UserWindowClass", "2", nullptr));
        comboBoxMonths->setItemText(3, QCoreApplication::translate("UserWindowClass", "3", nullptr));
        comboBoxMonths->setItemText(4, QCoreApplication::translate("UserWindowClass", "4", nullptr));
        comboBoxMonths->setItemText(5, QCoreApplication::translate("UserWindowClass", "5", nullptr));
        comboBoxMonths->setItemText(6, QCoreApplication::translate("UserWindowClass", "6", nullptr));
        comboBoxMonths->setItemText(7, QCoreApplication::translate("UserWindowClass", "7", nullptr));
        comboBoxMonths->setItemText(8, QCoreApplication::translate("UserWindowClass", "8", nullptr));
        comboBoxMonths->setItemText(9, QCoreApplication::translate("UserWindowClass", "9", nullptr));
        comboBoxMonths->setItemText(10, QCoreApplication::translate("UserWindowClass", "10", nullptr));
        comboBoxMonths->setItemText(11, QCoreApplication::translate("UserWindowClass", "11", nullptr));
        comboBoxMonths->setItemText(12, QCoreApplication::translate("UserWindowClass", "12", nullptr));

        pushButtonNext->setText(QCoreApplication::translate("UserWindowClass", "Next", nullptr));
        label->setText(QCoreApplication::translate("UserWindowClass", "TextLabel", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetAdminEvents->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("UserWindowClass", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetAdminEvents->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("UserWindowClass", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetAdminEvents->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("UserWindowClass", "Date and Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetAdminEvents->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("UserWindowClass", "Number of Participants", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetAdminEvents->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("UserWindowClass", "Link", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("UserWindowClass", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserWindowClass: public Ui_UserWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERFORM_H
