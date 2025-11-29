#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Quiz2.h"
#include "PresenterServices.h"
#include "ParticipantForm.h"

class PresenterForm : public QMainWindow
{
    Q_OBJECT

public:
    PresenterForm(QWidget *parent = nullptr);
    ~PresenterForm();
    void PopulateListWidget();
private slots:
    void on_pushButtonAdd_clicked();
 
private:
    Ui::Quiz2Class ui;
    PresenterServices presenter;
    std::vector<ParticipantForm*> participantForms;
};

