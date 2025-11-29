#include "DriverForm.h"
#include <QtWidgets/QApplication>
#include "Map.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo<Driver> drivers = Repo<Driver>("drivers.txt");
    Repo<Report> reports = Repo<Report>("reports.txt");
    std::vector<DriverForm*> forms;
    std::vector<int> validations = std::vector<int>(drivers.data.size());

    int count = 0;
    for (int i = 0; i < drivers.data.size(); ++i) {
        DriverForm* dForm = new DriverForm(count++, &validations, &reports, &drivers.data[i]);
        forms.push_back(dForm);
    }

    Map* map = new Map(&reports);

    for(const auto& sender : forms)
        for (const auto& receiver : forms) {
            if (sender != receiver) {
                QObject::connect(sender, &DriverForm::messageAdded, receiver, &DriverForm::on_messageAdded);
                QObject::connect(sender, &DriverForm::reportAdded, receiver, &DriverForm::on_reportAdded);
                QObject::connect(sender, &DriverForm::reportValidated, receiver, &DriverForm::on_reportValidated);
                QObject::connect(sender, &DriverForm::reportActuallyValidated, receiver, &DriverForm::PopulateListWidget);
            }

            QObject::connect(sender, &DriverForm::reportActuallyValidated, map, &Map::on_reportValidated);
        }

    for (const auto& f : forms)
        f->show();
    map->show();

    return app.exec();
}
