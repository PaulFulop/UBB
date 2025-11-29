#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UserForm.h"
#include "ServiceUM.h"
#include "CSVEventViewer.h"
#include "HTMLEventViewer.h"
#include <QCloseEvent>

class UserForm : public QMainWindow
{
    Q_OBJECT

public:
    ServiceUM* serv;
    QWidget* mainWindow;
    explicit UserForm(QWidget* parent = nullptr, ServiceUM* _serv = new ServiceUM, QWidget* _mainWindow = nullptr);
    ~UserForm();

    void StoreGlobalData();
    void StoreUserData();
    void setup();
    void SetProps();
    void InitComponents();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonNext_clicked();
    void on_pushButtonViewCSV_clicked();
    void on_pushButtonViewHTML_clicked();
    void on_comboBoxMonths_currentIndexChanged(int index);
    void on_tableWidgetUserEvents_cellDoubleClicked(int row, int column);

private:
    Ui::UserWindowClass* ui;
    int currentRow = 1;

    QWidget* centralwidget;
    QGridLayout *gridLayout_3, *gridLayout_2, *gridLayout;
    QGroupBox *groupBox_2, *groupBox;
    QTableWidget *tableWidgetUserEvents, *tableWidgetAdminEvents;
    QPushButton *pushButtonNext, *pushButtonAdd, *pushButtonViewCSV, *pushButtonViewHTML;
    QComboBox* comboBoxMonths;
    QLabel* label;
};
