#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UserForm.h"
#include "Service.h"

class UserForm : public QMainWindow
{
    Q_OBJECT

public:
    UserForm(Service _serv, QWidget *parent = nullptr);
    ~UserForm();
    void PopulateListWidget();

signals:
    void dataModified();

public slots:
    void on_pushButtonResolve_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonRemove_clicked();
    void on_listWidgetIssues_itemClicked(QListWidgetItem* item);
    void on_dataModified();

private:
    Ui::UserFormClass ui;
    Service serv;
    int selectedRow = -1;
};

