#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "UserForm.h"
#include "AdminForm.h"
#include "ServiceUM.h"
#include "ServiceAM.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setup();

    void SetProps();

    void InitComponents();

private slots:
    void on_pushButtonSeeUserEvents_clicked();
    void on_pushButtonSeeAdminEvents_clicked();

private:
    Ui::MainWindowClass* ui;
    UserForm* userForm;
    AdminForm* adminForm;
    QWidget* centralWidget;
    QPushButton* pushButtonSeeUserEvents;
    QPushButton* pushButtonSeeAdminEvents;
    QVBoxLayout* layout;
};
