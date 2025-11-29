#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AgentForm.h"
#include "Agent.h"
#include "Repository.h"
#include "Parcel.h"

class AgentForm : public QMainWindow
{
    Q_OBJECT

public:
    AgentForm(QWidget *parent = nullptr, const Agent& _agent = Agent(), Repo<Parcel>* _parcels = nullptr);
    ~AgentForm();
    void PopulateListWidget();
    void PopulateComboBox();
    void PopulateParcelsOnStreet(std::string street);

signals:
    void dataChanged();

public slots:
    void parcelDelivered();
    void on_pushButtonDeliver_clicked();
    void on_comboBoxParcel_activated(int index);

private:
    Ui::AgentFormClass ui;
    Agent agent;
    Repo<Parcel>* parcels;
};

