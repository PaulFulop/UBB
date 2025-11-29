#include "DepartmentForm.h"
#include <QtWidgets/QApplication>
#include "MainForm.h"
#include "Repository.h"
#include "Service.h"
#include "Volunteer.h"
#include "Department.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repository<Volunteer> v = Repository<Volunteer>("volunteers.txt");
    Repository<Department> deps = Repository<Department>("departments.txt");
    
    std::vector<Service> services;
    for (auto& d : deps.data) {
        Service serv = Service(&d, &v);
        services.push_back(serv);
    }

    std::vector<DepartmentForm*> depForms;
    for (auto& serv : services) {
        DepartmentForm* dForm = new DepartmentForm(&serv);
        depForms.push_back(dForm);
    }

    for(const auto& senderForm : depForms)
        for(const auto& receiverForm : depForms)
            if(senderForm != receiverForm)
                QObject::connect(senderForm, &DepartmentForm::volunteerAdded, 
                    receiverForm, &DepartmentForm::repoChanged);

    for (auto& form : depForms)
        form->show();

    std::sort(services.begin(), services.end(), [](Service s1, Service s2) {return s1.NrOfVolunteers() < s2.NrOfVolunteers(); });
    MainForm* window = new MainForm(services);
    window->show();
    return app.exec();
}
