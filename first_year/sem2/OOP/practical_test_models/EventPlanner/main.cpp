#include "PersonForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::vector<PersonForm*> forms;
    auto persons = Repo<Person>("persons.txt");
    auto events = Repo<Event>("events.txt");
    auto tickets = Repo<Ticket>("positions.txt");

    for (auto& p : persons.data) {
        Service serv = Service(p, &events, &persons, &tickets);
        auto form = new PersonForm(serv);
        forms.push_back(form);
    }

    for (const auto& sender : forms)
        for (const auto& receiver : forms) {
                QObject::connect(sender, &PersonForm::dataModified, receiver, &PersonForm::on_dataModified);
        }

    for (const auto& form : forms)
        form->show();

    return app.exec();
}
