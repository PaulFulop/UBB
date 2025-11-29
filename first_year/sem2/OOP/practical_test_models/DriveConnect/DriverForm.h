#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DriverForm.h"
#include "Driver.h"
#include "Report.h"
#include "Repo.h"

class DriverForm : public QMainWindow
{
    Q_OBJECT

public:
    DriverForm(int _id, std::vector<int>* _validations, Repo<Report>* _reports, Driver* _d, QWidget *parent = nullptr);
    ~DriverForm();
    void PopulateListWidget();

signals:
    void messageAdded(QString message);
    void reportAdded();
    void reportValidated(int row, QListWidgetItem* item, std::string name);
    void reportActuallyValidated();

public slots:
    void on_reportAdded();
    void on_pushButtonSend_clicked();
    void on_messageAdded(QString message);
    void on_pushButtonAdd_clicked();
    void on_listWidgetReports_itemDoubleClicked(QListWidgetItem* item);
    void on_reportValidated(int row, QListWidgetItem* item, std::string name);
    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::DriverFormClass ui;
    int id;
    std::vector<int>* validations;
    Repo<Report>* reports;
    Driver* d;
    std::vector<bool> validated;
};

