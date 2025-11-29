#include "DoctorForm.h"
#include <QtWidgets/QApplication>
#include "Statistics.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Repo<Doctor> doctors = Repo<Doctor>("doctors.txt");
    Repo<Patient> patients = Repo<Patient>("patients.txt");
    std::vector<DoctorForm*> forms;
    
    for (const auto& d : doctors.data) {
        Service s = Service(d, &patients);
        DoctorForm* dForm = new DoctorForm(s);
        forms.push_back(dForm);
    }

    Statistics* sForm = new Statistics(&doctors, &patients);

    for (const auto& sender : forms)
        for (const auto& receiver : forms) {
            if (sender != receiver) {
                QObject::connect(sender, &DoctorForm::patientUpdated, receiver, &DoctorForm::on_patientUpdated);
                QObject::connect(sender, &DoctorForm::patientAdded, receiver, &DoctorForm::on_patientAdded);
            }

            QObject::connect(sender, &DoctorForm::patientUpdated, sForm, &Statistics::on_dataModified);
            QObject::connect(sender, &DoctorForm::patientAdded, sForm, &Statistics::on_dataModified);
        }

    for (const auto& form : forms)
        form->show();

    sForm->show();

    return app.exec();
}
