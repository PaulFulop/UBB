#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PersonForm.h"
#include "Service.h"

class PersonForm : public QMainWindow
{
    Q_OBJECT

public:
    PersonForm(Service _serv, QWidget *parent = nullptr);
    ~PersonForm();

signals:
    void dataModified();

public slots:
    void PopulateEventsWidget();
    void PopulateFilteredEventsWidget();
    void PopulatePersonsWidget(Event& e);
    void on_listWidgetEvents_itemClicked(QListWidgetItem* item);
    void on_checkBox_checkStateChanged(Qt::CheckState state);
    void on_pushButtonAdd_clicked();
    void on_pushButtonUpdate_clicked();
    void on_dataModified();
    void on_pushButtonGoing_clicked();

private:
    Ui::PersonFormClass ui;
    Service serv;
    int actualRow = -1;
};

