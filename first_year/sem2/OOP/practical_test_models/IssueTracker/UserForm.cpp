#include "UserForm.h"
#include <QMessageBox>

UserForm::UserForm(Service _serv, QWidget *parent)
    : serv(_serv), QMainWindow(parent)
{
    ui.setupUi(this);
    QString title = QString::fromStdString(serv.u.name) + " " + QString::fromStdString(serv.u.type);
    this->setWindowTitle(title);

    if (!serv.IsTester()) {
        ui.lineEdit->setEnabled(false);
        ui.pushButtonAdd->setEnabled(false);
    }

    ui.pushButtonResolve->setEnabled(false);
    ui.pushButtonRemove->setEnabled(false);
    PopulateListWidget();
}

UserForm::~UserForm()
{}

void UserForm::PopulateListWidget() {
    serv.SortIssues();

    ui.listWidgetIssues->clear();
    for (const auto& issue : serv.issues->data) {
        auto item = new QListWidgetItem(QString::fromStdString(issue.ToString()));
        ui.listWidgetIssues->addItem(item);
    }
}

void UserForm::on_pushButtonResolve_clicked() {
    serv.ResolveIssue(serv.issues->data[selectedRow]);
    PopulateListWidget();
    emit dataModified();
}

void UserForm::on_pushButtonAdd_clicked() {
    try {
        std::string desc = ui.lineEdit->text().toStdString();
        serv.AddIssue(desc);
        PopulateListWidget();
        ui.lineEdit->clear();
        emit dataModified();
    }
    catch (const std::exception& e) {
        auto msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void UserForm::on_pushButtonRemove_clicked() {
    serv.RemoveIssue(serv.issues->data[selectedRow]);
    PopulateListWidget();
    emit dataModified();
}

void UserForm::on_listWidgetIssues_itemClicked(QListWidgetItem* item) {
    selectedRow = ui.listWidgetIssues->row(item);

    if (!serv.IsTester())
        if (serv.IsIssueOpen(serv.issues->data[selectedRow]))
            ui.pushButtonResolve->setEnabled(true);
        else
            ui.pushButtonResolve->setEnabled(false);

    if (!serv.IsIssueOpen(serv.issues->data[selectedRow]))
        ui.pushButtonRemove->setEnabled(true);
    else
        ui.pushButtonRemove->setEnabled(false);
}

void UserForm::on_dataModified() {
    PopulateListWidget();
}