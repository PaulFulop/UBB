#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BiologistForm.h"
#include "Repo.h"
#include "Biologist.h"
#include "Bacterium.h"
#include "BacteriumTableModel.h"
#include <QSortFilterProxyModel>
#include "BacteriumForm.h"

class BiologistForm : public QMainWindow
{
    Q_OBJECT

public:
    BiologistForm(BacteriumTableModel* _btm, Biologist _b, Repo<Bacterium>* _bacterium, QWidget *parent = nullptr);
    ~BiologistForm();
    void PopulateComboBox();

private slots:
    void on_comboBoxSearch_currentTextChanged(const QString& text);
    void on_pushButtonAddBacterium_clicked();
    void on_tableViewBacterium_clicked(const QModelIndex& index);
    void on_pushButtonAddDisease_clicked();
    void on_pushButtonView_clicked();

private:
    int row = -1; // to get the data of the bacterium that was clicked on, this is the row relative to a certain table not the actual row in the whole list
    std::string pattern;
    Ui::BiologistFormClass ui;
    Biologist b;
    Repo<Bacterium>* bacterium;
    BacteriumTableModel* btm;
    QSortFilterProxyModel* proxyTable;
    BacteriumForm* bacteriumForm;
};

