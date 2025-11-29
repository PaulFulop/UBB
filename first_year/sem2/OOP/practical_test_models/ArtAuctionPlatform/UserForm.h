#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UserForm.h"
#include "Repo.h"
#include "User.h"
#include "Item.h"

class UserForm : public QMainWindow
{
    Q_OBJECT

public:
    UserForm(User _u, Repo<Item>* _items, QWidget *parent = nullptr);
    ~UserForm();

    void PopulateListWidget();
    void PopulateComboBox();
    void PopulateListOfOffers(std::vector<std::tuple<int, std::string, int>> offers);

signals:
    void newItemAdded();
    void itemPriceChanged();

public slots:
    void on_comboBoxSearch_currentTextChanged(const QString& text);
    void on_pushButtonAdd_clicked();
    void on_listWidgetItems_itemClicked(QListWidgetItem* item);
    void on_pushButtonBid_clicked();
    void on_itemPriceChanged();
    void on_newItemAdded();

private:
    Ui::UserFormClass ui;
    User u;
    Repo<Item>* items;
    int selectedRow = -1;
};

