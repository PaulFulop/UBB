#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DoctorForm.h"
#include "Service.h"

class DoctorForm : public QMainWindow
{
    Q_OBJECT

public:
    DoctorForm(Service _serv, QWidget *parent = nullptr);
    ~DoctorForm();
    void PopulateLisWidget();

signals:
    void patientUpdated();
    void patientAdded();

public slots:
    void on_checkBox_checkStateChanged(Qt::CheckState state);
    void on_listWidgetPatients_itemClicked(QListWidgetItem* item);
    void on_patientUpdated();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonAdd_clicked();
    void on_patientAdded();

private:
    Ui::DoctorFormClass ui;
    Service serv;
    int actualRow = -1;
};

