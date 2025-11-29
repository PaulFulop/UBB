/********************************************************************************
** Form generated from reading UI file 'AdminForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINFORM_H
#define UI_ADMINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminWindowClass
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QTableWidget *tableWidgetEvents;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *lineEditPartAdd;
    QLineEdit *lineEditDateAdd;
    QLabel *label;
    QLineEdit *lineEditDescriptionAdd;
    QLineEdit *lineEditTitleAdd;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_3;
    QLineEdit *lineEditLinkAdd;
    QPushButton *pushButtonAdd;
    QLabel *labelErrorAdd;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEditEventRemove;
    QLabel *label_2;
    QLabel *labelErrorRemove;
    QPushButton *pushButtonRemove;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEditDateUpdate;
    QLineEdit *lineEditTitleUpdate;
    QLabel *label_10;
    QLineEdit *lineEditDescriptionUpdate;
    QLineEdit *lineEditLinkUpdate;
    QLineEdit *lineEditPartUpdate;
    QLabel *label_9;
    QLabel *label_5;
    QLabel *label_11;
    QLabel *label_8;
    QLabel *labelErrorUpdate;
    QPushButton *pushButtonUpdate;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdminWindowClass)
    {
        if (AdminWindowClass->objectName().isEmpty())
            AdminWindowClass->setObjectName("AdminWindowClass");
        AdminWindowClass->resize(1166, 872);
        centralwidget = new QWidget(AdminWindowClass);
        centralwidget->setObjectName("centralwidget");
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName("gridLayout_4");
        tableWidgetEvents = new QTableWidget(centralwidget);
        if (tableWidgetEvents->columnCount() < 5)
            tableWidgetEvents->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetEvents->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetEvents->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetEvents->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QFont font;
        font.setPointSize(9);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        tableWidgetEvents->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        tableWidgetEvents->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidgetEvents->setObjectName("tableWidgetEvents");
        tableWidgetEvents->setRowCount(0);
        tableWidgetEvents->setColumnCount(5);
        tableWidgetEvents->horizontalHeader()->setDefaultSectionSize(150);

        gridLayout_4->addWidget(tableWidgetEvents, 0, 0, 1, 3);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        groupBox->setFont(font1);
        groupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        lineEditPartAdd = new QLineEdit(groupBox);
        lineEditPartAdd->setObjectName("lineEditPartAdd");

        gridLayout->addWidget(lineEditPartAdd, 3, 1, 1, 1);

        lineEditDateAdd = new QLineEdit(groupBox);
        lineEditDateAdd->setObjectName("lineEditDateAdd");

        gridLayout->addWidget(lineEditDateAdd, 2, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        label->setFont(font2);
        label->setAutoFillBackground(false);
        label->setFrameShape(QFrame::Shape::NoFrame);
        label->setFrameShadow(QFrame::Shadow::Plain);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEditDescriptionAdd = new QLineEdit(groupBox);
        lineEditDescriptionAdd->setObjectName("lineEditDescriptionAdd");

        gridLayout->addWidget(lineEditDescriptionAdd, 1, 1, 1, 1);

        lineEditTitleAdd = new QLineEdit(groupBox);
        lineEditTitleAdd->setObjectName("lineEditTitleAdd");

        gridLayout->addWidget(lineEditTitleAdd, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setFont(font2);
        label_6->setAutoFillBackground(false);
        label_6->setFrameShape(QFrame::Shape::NoFrame);
        label_6->setFrameShadow(QFrame::Shadow::Plain);
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setFont(font2);
        label_4->setAutoFillBackground(false);
        label_4->setFrameShape(QFrame::Shape::NoFrame);
        label_4->setFrameShadow(QFrame::Shadow::Plain);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setFont(font2);
        label_7->setAutoFillBackground(false);
        label_7->setFrameShape(QFrame::Shape::NoFrame);
        label_7->setFrameShadow(QFrame::Shadow::Plain);
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setFont(font2);
        label_3->setAutoFillBackground(false);
        label_3->setFrameShape(QFrame::Shape::NoFrame);
        label_3->setFrameShadow(QFrame::Shadow::Plain);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        lineEditLinkAdd = new QLineEdit(groupBox);
        lineEditLinkAdd->setObjectName("lineEditLinkAdd");

        gridLayout->addWidget(lineEditLinkAdd, 4, 1, 1, 1);

        pushButtonAdd = new QPushButton(groupBox);
        pushButtonAdd->setObjectName("pushButtonAdd");
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        pushButtonAdd->setFont(font3);

        gridLayout->addWidget(pushButtonAdd, 6, 0, 1, 2);

        labelErrorAdd = new QLabel(groupBox);
        labelErrorAdd->setObjectName("labelErrorAdd");
        labelErrorAdd->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 0);"));

        gridLayout->addWidget(labelErrorAdd, 5, 0, 1, 2);


        gridLayout_4->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setFont(font1);
        groupBox_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName("gridLayout_3");
        lineEditEventRemove = new QLineEdit(groupBox_3);
        lineEditEventRemove->setObjectName("lineEditEventRemove");

        gridLayout_3->addWidget(lineEditEventRemove, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName("label_2");
        label_2->setFont(font2);
        label_2->setAutoFillBackground(false);
        label_2->setFrameShape(QFrame::Shape::NoFrame);
        label_2->setFrameShadow(QFrame::Shadow::Plain);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        labelErrorRemove = new QLabel(groupBox_3);
        labelErrorRemove->setObjectName("labelErrorRemove");
        labelErrorRemove->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 0);"));

        gridLayout_3->addWidget(labelErrorRemove, 2, 0, 1, 2);

        pushButtonRemove = new QPushButton(groupBox_3);
        pushButtonRemove->setObjectName("pushButtonRemove");
        pushButtonRemove->setFont(font3);

        gridLayout_3->addWidget(pushButtonRemove, 1, 0, 1, 2);


        gridLayout_4->addWidget(groupBox_3, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setFont(font1);
        groupBox_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        lineEditDateUpdate = new QLineEdit(groupBox_2);
        lineEditDateUpdate->setObjectName("lineEditDateUpdate");

        gridLayout_2->addWidget(lineEditDateUpdate, 2, 1, 1, 1);

        lineEditTitleUpdate = new QLineEdit(groupBox_2);
        lineEditTitleUpdate->setObjectName("lineEditTitleUpdate");

        gridLayout_2->addWidget(lineEditTitleUpdate, 0, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setFont(font2);
        label_10->setAutoFillBackground(false);
        label_10->setFrameShape(QFrame::Shape::NoFrame);
        label_10->setFrameShadow(QFrame::Shadow::Plain);
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_10, 3, 0, 1, 1);

        lineEditDescriptionUpdate = new QLineEdit(groupBox_2);
        lineEditDescriptionUpdate->setObjectName("lineEditDescriptionUpdate");

        gridLayout_2->addWidget(lineEditDescriptionUpdate, 1, 1, 1, 1);

        lineEditLinkUpdate = new QLineEdit(groupBox_2);
        lineEditLinkUpdate->setObjectName("lineEditLinkUpdate");

        gridLayout_2->addWidget(lineEditLinkUpdate, 4, 1, 1, 1);

        lineEditPartUpdate = new QLineEdit(groupBox_2);
        lineEditPartUpdate->setObjectName("lineEditPartUpdate");

        gridLayout_2->addWidget(lineEditPartUpdate, 3, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setFont(font2);
        label_9->setAutoFillBackground(false);
        label_9->setFrameShape(QFrame::Shape::NoFrame);
        label_9->setFrameShadow(QFrame::Shadow::Plain);
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_9, 2, 0, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setFont(font2);
        label_5->setAutoFillBackground(false);
        label_5->setFrameShape(QFrame::Shape::NoFrame);
        label_5->setFrameShadow(QFrame::Shadow::Plain);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");
        label_11->setFont(font2);
        label_11->setAutoFillBackground(false);
        label_11->setFrameShape(QFrame::Shape::NoFrame);
        label_11->setFrameShadow(QFrame::Shadow::Plain);
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_11, 4, 0, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setFont(font2);
        label_8->setAutoFillBackground(false);
        label_8->setFrameShape(QFrame::Shape::NoFrame);
        label_8->setFrameShadow(QFrame::Shadow::Plain);
        label_8->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        labelErrorUpdate = new QLabel(groupBox_2);
        labelErrorUpdate->setObjectName("labelErrorUpdate");
        labelErrorUpdate->setStyleSheet(QString::fromUtf8("color: rgb(170, 0, 0);"));

        gridLayout_2->addWidget(labelErrorUpdate, 5, 0, 1, 2);

        pushButtonUpdate = new QPushButton(groupBox_2);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setFont(font3);

        gridLayout_2->addWidget(pushButtonUpdate, 6, 0, 1, 2);


        gridLayout_4->addWidget(groupBox_2, 1, 2, 1, 1);

        AdminWindowClass->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(AdminWindowClass);
        statusbar->setObjectName("statusbar");
        AdminWindowClass->setStatusBar(statusbar);

        retranslateUi(AdminWindowClass);

        QMetaObject::connectSlotsByName(AdminWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *AdminWindowClass)
    {
        AdminWindowClass->setWindowTitle(QCoreApplication::translate("AdminWindowClass", "Admin ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetEvents->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AdminWindowClass", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetEvents->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AdminWindowClass", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetEvents->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AdminWindowClass", "Date and Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetEvents->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("AdminWindowClass", "Participants", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetEvents->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("AdminWindowClass", "Link", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AdminWindowClass", "Add new event", nullptr));
        label->setText(QCoreApplication::translate("AdminWindowClass", "Title:", nullptr));
        label_6->setText(QCoreApplication::translate("AdminWindowClass", "Participants:", nullptr));
        label_4->setText(QCoreApplication::translate("AdminWindowClass", "Date:", nullptr));
        label_7->setText(QCoreApplication::translate("AdminWindowClass", "Link:", nullptr));
        label_3->setText(QCoreApplication::translate("AdminWindowClass", "Description:", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("AdminWindowClass", "Add", nullptr));
        labelErrorAdd->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("AdminWindowClass", "Remove event", nullptr));
        label_2->setText(QCoreApplication::translate("AdminWindowClass", "Title:", nullptr));
        labelErrorRemove->setText(QString());
        pushButtonRemove->setText(QCoreApplication::translate("AdminWindowClass", "Remove", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("AdminWindowClass", "Update event", nullptr));
        label_10->setText(QCoreApplication::translate("AdminWindowClass", "New Participants:", nullptr));
        label_9->setText(QCoreApplication::translate("AdminWindowClass", "New Date:", nullptr));
        label_5->setText(QCoreApplication::translate("AdminWindowClass", "Title:", nullptr));
        label_11->setText(QCoreApplication::translate("AdminWindowClass", "New Link:", nullptr));
        label_8->setText(QCoreApplication::translate("AdminWindowClass", "New Description:", nullptr));
        labelErrorUpdate->setText(QString());
        pushButtonUpdate->setText(QCoreApplication::translate("AdminWindowClass", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminWindowClass: public Ui_AdminWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINFORM_H
