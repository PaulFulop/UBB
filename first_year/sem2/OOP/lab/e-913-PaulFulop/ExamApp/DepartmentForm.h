#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DepartmentForm.h"
#include "Service.h"

class DepartmentForm : public QMainWindow
{
    Q_OBJECT

public:
    DepartmentForm(Service* _serv, QWidget *parent = nullptr);
    ~DepartmentForm();
    void PopulateListWidget();
    void PopulateListWidgetU();

signals:
    void volunteerAdded();

public slots:
    void on_pushButton_clicked();
    void repoChanged();
    void on_listWidgetUnassigned_itemDoubleClicked(QListWidgetItem* item);
    void on_pushButton_2_clicked();

private:
    Ui::DepartmentFormClass ui;
    Service* serv;
};

