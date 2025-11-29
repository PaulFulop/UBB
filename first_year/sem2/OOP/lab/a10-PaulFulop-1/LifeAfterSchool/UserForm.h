#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UserForm.h"
#include "ServiceUM.h"
#include "CSVEventViewer.h"
#include "HTMLEventViewer.h"
#include "CommandManager.h"
#include "AddCommand.h"
#include "RemoveCommand.h"
#include "UpdateCommand.h"
#include <QCloseEvent>
#include <QShortcut>
#include <QKeySequence>

class UserForm : public QMainWindow
{
    Q_OBJECT

public:
    ServiceUM* serv;
    QWidget* mainWindow;
    CommandManager* cmdManager;
    explicit UserForm(QWidget* parent = nullptr, ServiceUM* _serv = new ServiceUM, QWidget* _mainWindow = nullptr, CommandManager* _cmdManager = new CommandManager);
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
    void on_pushButtonUndo_clicked();
    void on_pushButtonRedo_clicked();
    void on_undoShortcut_activated();
    void on_redoShortcut_activated();

private:
    Ui::UserWindowClass* ui;
    int currentRow = 1;

    QWidget* centralwidget;
    QGridLayout *gridLayout_3, *gridLayout_2, *gridLayout, *gridLayout_4;
    QGroupBox *groupBox_2, *groupBox, *groupBox_3;
    QTableWidget *tableWidgetUserEvents, *tableWidgetAdminEvents;
    QPushButton *pushButtonNext, *pushButtonAdd, *pushButtonViewCSV, *pushButtonViewHTML, *pushButtonUndo, *pushButtonRedo;
    QComboBox* comboBoxMonths;
    QLabel* label;
    QShortcut *undoShortcut, *redoShortcut;
};
