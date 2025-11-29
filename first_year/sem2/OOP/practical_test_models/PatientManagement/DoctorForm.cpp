#include "DoctorForm.h"
#include <QMessageBox>

DoctorForm::DoctorForm(Service _serv, QWidget *parent)
    : serv(_serv), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(serv.d.name));
    PopulateLisWidget();
    ui.lineEditUpdateDiagnosis->setEnabled(false);
    ui.lineEditUpdateSpecialisation->setEnabled(false);
    ui.pushButtonUpdate->setEnabled(false);
    ui.dateEdit->setDisplayFormat("yyyy/MM/dd");
}

DoctorForm::~DoctorForm()
{}

void DoctorForm::PopulateLisWidget() {
    auto patients = serv.PatientsOfSameNeededSpecialiation();
    serv.SortPatients(patients);

    ui.listWidgetPatients->clear();

    for (const auto& p : patients) {
        auto item = new QListWidgetItem(QString::fromStdString(p.ToString()));
        if (serv.PatientTreatedByDoctor(p))
            item->setBackground(Qt::darkGreen);

        ui.listWidgetPatients->addItem(item);
    }
}

void DoctorForm::on_checkBox_checkStateChanged(Qt::CheckState state) {
    if (state == Qt::Checked) {
        auto patients = serv.PatientsOfDoctor();
        ui.listWidgetPatients->clear();

        for (const auto& p : patients) {
            auto item = new QListWidgetItem(QString::fromStdString(p.ToString()));
            ui.listWidgetPatients->addItem(item);
        }
    }
    else {
        PopulateLisWidget();
    }
}

void DoctorForm::on_pushButtonAdd_clicked() {
    try {
        std::string name = ui.lineEditName->text().toStdString();
        std::string diagnosis = ui.lineEditDiagnosis->text().toStdString();
        std::string specialisation = ui.lineEditSpecialisation->text().toStdString();
        std::string doctor = ui.lineEditDoctor->text().toStdString();
        std::string date = ui.dateEdit->text().toStdString();

        std::string currentDate = QDate::currentDate().toString("yyyy/MM/dd").toStdString();
        if (currentDate > date) throw std::exception("This date is in the past!");

        serv.AddPatient(name, diagnosis, specialisation, doctor, date);
        PopulateLisWidget();
        emit patientAdded();
    }
    catch (const std::exception& e) {
        auto msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void DoctorForm::on_listWidgetPatients_itemClicked(QListWidgetItem* item) {
    int row = ui.listWidgetPatients->row(item);
    auto patients = serv.PatientsOfSameNeededSpecialiation();
    serv.SortPatients(patients);
    auto p = patients[row];

    for(int i = 0; i < serv.patients->data.size(); ++i)
        if (p.ToString() == serv.patients->data[i].ToString()) {
            actualRow = i;
            break;
        }

    if (serv.ModifiablePatientData(serv.patients->data[actualRow])) {
        ui.lineEditUpdateDiagnosis->setEnabled(true);
        ui.lineEditUpdateSpecialisation->setEnabled(true);
        ui.pushButtonUpdate->setEnabled(true);
    }
    else {
        ui.lineEditUpdateDiagnosis->setEnabled(false);
        ui.lineEditUpdateSpecialisation->setEnabled(false);
        ui.pushButtonUpdate->setEnabled(false);
    }
}

void DoctorForm::on_pushButtonUpdate_clicked() {
    try {
        serv.UpdatePatientData(serv.patients->data[actualRow], ui.lineEditUpdateDiagnosis->text().toStdString(), ui.lineEditUpdateSpecialisation->text().toStdString());
        PopulateLisWidget();
        emit patientUpdated();
    }
    catch (const std::exception& e) {
        auto msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void DoctorForm::on_patientUpdated() {
    PopulateLisWidget();
}

void DoctorForm::on_patientAdded() {
    PopulateLisWidget();
}