#pragma once

#include <QtWidgets/QMainWindow>
#include <QCloseEvent>
#include "ui_AdminForm.h"
#include "ServiceAM.h"

class AdminForm : public QMainWindow
{
    Q_OBJECT

public:
    ServiceAM* serv;
    QWidget* mainWindow;

    explicit AdminForm(QWidget* parent = nullptr, ServiceAM* _serv = new ServiceAM, QWidget* _mainWindow = nullptr);
    ~AdminForm();

    void StoreData();
    void setup();
    void SetProps();
    void InitComponents();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonRemove_clicked();
    void on_pushButtonUpdate_clicked();

private:
    Ui::AdminWindowClass* ui;
    QWidget* centralwidget;
    QGridLayout *gridLayout, *gridLayout_2, *gridLayout_3, *gridLayout_4;
    QTableWidget* tableWidgetEvents;
    QGroupBox *groupBox, *groupBox_2, *groupBox_3;

    QLineEdit *lineEditPartAdd, *lineEditDateAdd, *lineEditDescriptionAdd, *lineEditTitleAdd, *lineEditLinkAdd,
        *lineEditEventRemove, *lineEditDateUpdate, *lineEditTitleUpdate, *lineEditDescriptionUpdate,
        *lineEditLinkUpdate, *lineEditPartUpdate;

    QLabel *label, *label_2, *label_3, *label_4, *label_5, *label_6, *label_7, *label_8, *label_9, *label_10, *label_11,
        *labelErrorAdd, *labelErrorRemove, *labelErrorUpdate;

    QPushButton *pushButtonAdd, *pushButtonRemove, *pushButtonUpdate;   
};
