#include "Bills.h"

Bills::Bills(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    repo = Repository("bills.txt");
    PopulateListView();
}

void Bills::PopulateListView() {
    ui.listWidgetBills->clear();
    for (auto& bill : repo.bills) {
        QListWidgetItem* item = new QListWidgetItem(QString(bill.ToString().c_str()));
        if (!bill.isPaid)
            item->setBackground(Qt::red);

        ui.listWidgetBills->addItem(item);
    }
}


void Bills::PopulateListViewUnpaid()
{
    ui.listWidgetBills->clear();
    for (auto& bill : repo.bills) {
        QListWidgetItem* item = new QListWidgetItem(QString(bill.ToString().c_str()));
        if (!bill.isPaid)
            ui.listWidgetBills->addItem(item);
    }
}

void Bills::PopulateListViewPaid()
{
    ui.listWidgetBills->clear();
    for (auto& bill : repo.bills) {
        QListWidgetItem* item = new QListWidgetItem(QString(bill.ToString().c_str()));
        if (bill.isPaid)
            ui.listWidgetBills->addItem(item);
    }
}

void Bills::on_pushButtonCalculate_clicked() {
    double total = repo.TotalUnpaidBills(ui.lineEditCalculate->text().toStdString());
    if (total == -1)
        ui.labelTotal->setText("No unpaid bills for this company.");
    else
        ui.labelTotal->setText(QString(std::to_string(total).c_str()));
}

void Bills::on_checkBoxPaid_checkStateChanged(Qt::CheckState state){
    if (state == Qt::Checked) {
        PopulateListViewPaid();
        ui.checkBoxAll->setChecked(false);
        ui.checkBoxUnpaid->setChecked(false);
    }
}

void Bills::on_checkBoxUnpaid_checkStateChanged(Qt::CheckState state) {
    if (state == Qt::Checked) {
        PopulateListViewUnpaid();
        ui.checkBoxAll->setChecked(false);
        ui.checkBoxPaid->setChecked(false);
    }
}

void Bills::on_checkBoxAll_checkStateChanged(Qt::CheckState state) {
    if (state == Qt::Checked) {
        PopulateListView();
        ui.checkBoxPaid->setChecked(false);
        ui.checkBoxUnpaid->setChecked(false);
    }
}

Bills::~Bills()
{}
