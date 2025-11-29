#include "DepartmentForm.h"
#include "Utils.h"
#include <QMessageBox>

DepartmentForm::DepartmentForm(Service* _serv, QWidget *parent)
    : serv(_serv), QMainWindow(parent)
{
    ui.setupUi(this);
    PopulateListWidget();
    PopulateListWidgetU();
    this->setWindowTitle(QString::fromStdString(serv->d->name));
    ui.labelDesc->setText(QString::fromStdString(serv->d->desc));
}

DepartmentForm::~DepartmentForm()
{}

void DepartmentForm::PopulateListWidget() {
	ui.listWidgetVolunteers->clear();
    std::vector<Volunteer> volunteers = serv->VolunteersOfDepartment();
    for (auto& d : volunteers) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.ToString()));
        ui.listWidgetVolunteers->addItem(item);
    }
}

void DepartmentForm::PopulateListWidgetU() {
    ui.listWidgetUnassigned->clear();
    std::vector<Volunteer> volunteers = serv->UnassignedVolunteers();
    for (auto& d : volunteers) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.ToString()));
        ui.listWidgetUnassigned->addItem(item);
    }
}

void DepartmentForm::on_pushButton_clicked() {
    try {
        std::string name = ui.lineEditName->text().toStdString();
        std::string email = ui.lineEditEmail->text().toStdString();
        std::string list = ui.lineEditList->text().toStdString();
        std::vector<std::string> interests = Tokenize(list, ' ');

        Volunteer v = Volunteer(name, email, interests, Department());
        serv->AddVolunteer(v);
        PopulateListWidgetU();
        serv->volunteers->SaveToFile();
        emit volunteerAdded();
    }
    catch (const std::exception& e) {
        QMessageBox* q = new QMessageBox(QMessageBox::Warning, "Warning", QString::fromStdString(e.what()));
        q->show();
    }
}

void DepartmentForm::repoChanged() {
    PopulateListWidgetU();
}

void DepartmentForm::on_listWidgetUnassigned_itemDoubleClicked(QListWidgetItem* item) {

    //for(int i = 0; i < serv->volunteers->size(); ++i)
    //    if (item->text().toStdString() == serv->volunteers->data[i].ToString()) {
    //        serv->volunteers->data[i].department.desc = serv->d->desc;
    //        serv->volunteers->data[i].department.name = serv->d->name;
    //        serv->volunteers->SaveToFile();
    //        PopulateListWidgetU();
    //        PopulateListWidget();
    //        return;
    //    }
}

void DepartmentForm::on_pushButton_2_clicked() {

}