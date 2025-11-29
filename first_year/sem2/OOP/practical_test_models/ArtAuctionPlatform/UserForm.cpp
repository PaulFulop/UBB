#include "UserForm.h"
#include <unordered_set>
#include <QMessageBox>
#include <QDate>

UserForm::UserForm(User _u, Repo<Item>* _items, QWidget *parent)
    : u(_u), items(_items), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(u.name));

    if (u.type == "administrator")
        ui.pushButtonBid->setEnabled(false);
    else
        ui.pushButtonAdd->setEnabled(false);
    PopulateListWidget();
    PopulateComboBox();
}

UserForm::~UserForm()
{}

void UserForm::PopulateListWidget() {
    std::sort(items->data.begin(), items->data.end(), [](const Item& i1, const Item& i2) {return i1.price < i2.price; });

    ui.listWidgetItems->clear();
    for (const auto& i : items->data) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(i.ToString()));
        ui.listWidgetItems->addItem(item);
    }
}

void UserForm::PopulateComboBox() {
    ui.comboBoxSearch->clear();
    ui.comboBoxSearch->addItem("");

    std::unordered_set<std::string> categories;
    for (const auto& i : items->data)
        categories.insert(i.category);

    for (const auto& category : categories) {
        ui.comboBoxSearch->addItem(QString::fromStdString(category));
    }
}

void UserForm::on_comboBoxSearch_currentTextChanged(const QString& text) {
    if (text == "") {
        PopulateListWidget();
    }
    else {
        ui.listWidgetItems->clear();
        for (const auto& i : items->data) {
            if (i.category == text.toStdString()) {
                QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(i.ToString()));
                ui.listWidgetItems->addItem(item);
            }
        }
    }
}

void UserForm::on_pushButtonAdd_clicked() {
    std::string name = ui.lineEditName->text().toStdString();
    std::string category = ui.lineEditCategory->text().toStdString();
    int price = std::atoi(ui.lineEditPrice->text().toStdString().c_str());

    if (name == "" || price <= 0) {
        QMessageBox* msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", "Invalid data!");
        return;
    }

    Item newItem = Item(name, category, price, std::vector < std::tuple<int, std::string, int >> ());
    items->data.push_back(newItem);
    emit newItemAdded();
}

void UserForm::on_listWidgetItems_itemClicked(QListWidgetItem* item) {
    selectedRow = ui.listWidgetItems->row(item);
    PopulateListOfOffers(items->data[selectedRow].offers);
}

void UserForm::PopulateListOfOffers(std::vector<std::tuple<int, std::string, int>> offers) {
    ui.listWidgetOffers->clear();
    std::sort(offers.begin(), offers.end(), [](const std::tuple<int, std::string, int>& t1, const std::tuple<int, std::string, int>& t2)
        {return std::get<1>(t1) > std::get<1>(t2); });
    for (int i = 0; i < offers.size(); ++i) {
        std::string idTxt = std::to_string(std::get<0>(offers[i]));
        std::string priceTxt = std::to_string(std::get<2>(offers[i]));
        std::string offerTxt = idTxt + " " + std::get<1>(offers[i]) + " " + priceTxt;

        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(offerTxt));
        ui.listWidgetOffers->addItem(item);
    }
}

void UserForm::on_pushButtonBid_clicked() {
    try {
        if (selectedRow == -1)
            throw std::exception("No item was selected!");

        int newPrice = std::atoi(ui.lineEditBid->text().toStdString().c_str());
        if(newPrice < items->data[selectedRow].price)
            throw std::exception("The bidding price is not enough!");

        items->data[selectedRow].price = newPrice;
        QDate date = QDate::currentDate();

        auto t = std::make_tuple(u.id,date.toString("yyyy/MM/dd").toStdString(), newPrice);
        items->data[selectedRow].offers.push_back(t);
        PopulateListOfOffers(items->data[selectedRow].offers);
        emit itemPriceChanged();
        
    }
    catch (const std::exception& e) {
        QMessageBox* msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void UserForm::on_itemPriceChanged() {
    PopulateListWidget();
}

void UserForm::on_newItemAdded() {
    PopulateListWidget();
    PopulateComboBox();
}