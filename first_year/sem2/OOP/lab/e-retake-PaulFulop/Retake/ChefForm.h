#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChefForm.h"
#include "Service.h"
#include "Statistics.h"

class ChefForm : public QMainWindow
{
    Q_OBJECT

public:
    ChefForm(Service _serv, QWidget *parent = nullptr);
    ~ChefForm();
    void PopulateListWidget();
    void PopualteListWidgetFiltered();

signals:
    void dataModified();

public slots:
    void on_checkBox_checkStateChanged(Qt::CheckState state);
    void on_pushButtonAdd_clicked();
    void on_pushButtonView_clicked();
    void on_lineEditSearch_textChanged(const QString& text);
    void PopulateBySearchBox(const QString& text);
    void on_dataModified();

private:
    Ui::ChefFormClass ui;
    Service serv;
    Statistics* stats;
};

