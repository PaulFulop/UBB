#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Bills.h"
#include "Repository.h"

class Bills : public QMainWindow
{
    Q_OBJECT

public:
    Bills(QWidget *parent = nullptr);
    ~Bills();

    void PopulateListView();
    void PopulateListViewUnpaid();
    void PopulateListViewPaid();

private slots:
    void on_pushButtonCalculate_clicked();
    void on_checkBoxPaid_checkStateChanged(Qt::CheckState state);
    void on_checkBoxUnpaid_checkStateChanged(Qt::CheckState state);
    void on_checkBoxAll_checkStateChanged(Qt::CheckState state);
private:
    Ui::BillsClass ui;
    Repository repo;
};
