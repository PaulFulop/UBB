#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Equations.h"
#include "Repository.h"


class Equations : public QMainWindow
{
    Q_OBJECT

public:
    Equations(QWidget *parent = nullptr);
    ~Equations();
    void PopulateList();

private slots:
    void on_pushButtonSol_clicked();
    void on_pushButtonUpdate_clicked();
    void on_listWidgetEq_itemClicked(QListWidgetItem* item);
private:
    Ui::EquationsClass ui;
    Repository repo;
    int clickedRow = 0;
};

