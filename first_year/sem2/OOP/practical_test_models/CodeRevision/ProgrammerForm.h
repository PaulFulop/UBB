#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProgrammerForm.h"
#include "Service.h"

class ProgrammerForm : public QMainWindow
{
    Q_OBJECT

public:
    ProgrammerForm(Service _serv, QWidget *parent = nullptr);
    ~ProgrammerForm();
    void PopulateListWidget();

signals:
    void dataModified();

public slots:
    void on_listWidget_itemClicked(QListWidgetItem* item);
    void on_pushButton_clicked();
    void on_pushButtonAdd_clicked();
    void on_dataModified();

private:
    Ui::ProgrammerFormClass ui;
    Service serv;
    int selectedRow = -1;
};

