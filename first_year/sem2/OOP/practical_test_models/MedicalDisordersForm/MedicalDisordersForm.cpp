#include "MedicalDisordersForm.h"

MedicalDisordersForm::MedicalDisordersForm(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    mainRepo = Repository("disorders.txt");
    mainRepo.SortAscendingByCategory();
    PopulateList(this->mainRepo);
}

MedicalDisordersForm::~MedicalDisordersForm()
{}

void MedicalDisordersForm::PopulateList(Repository repo) {

    ui.listWidgetDisorders->clear();
    for (auto& disorder : repo.disorders) {
        QListWidgetItem* item = new QListWidgetItem(QString(disorder.ToString().c_str()));
        ui.listWidgetDisorders->addItem(item);
    }
}

void MedicalDisordersForm::PopulateSymptomsList(std::vector<std::string> symptoms){
    ui.listWidgetSymptoms->clear();
    for (auto& symptom : symptoms) {
        QListWidgetItem* item = new QListWidgetItem(QString(symptom.c_str()));
        ui.listWidgetSymptoms->addItem(item);
    }
}

void MedicalDisordersForm::on_lineEditSearchCategory_textChanged(const QString& text) {
    if (text == "") PopulateList(mainRepo);
    else {
        Repository fltRepo = mainRepo.FilterByCategory(text.toStdString());
        PopulateList(fltRepo);
    }
}
void MedicalDisordersForm::on_lineEditSearchName_textChanged(const QString& text) {
    if (text == "") PopulateList(mainRepo);
    else {
        Repository fltRepo = mainRepo.FilterByName(text.toStdString());
        PopulateList(fltRepo);
    }
}

void MedicalDisordersForm::on_pushButtonShowSymptoms_clicked() {
    std::string name = ui.lineEditDisorderName->text().toStdString();

    for (auto& disorder : mainRepo.disorders) {
        if (disorder.name == name) {
            PopulateSymptomsList(disorder.symptoms);
            ui.labelNotFound->setText("");
            return;
        }
    }

    ui.labelNotFound->setText("No such disorder!");
}
