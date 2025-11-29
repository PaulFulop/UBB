#include "UserForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::vector<UserForm*> forms;

    Repo<User> users = Repo<User>("users.txt");
    Repo<Issue> issues = Repo<Issue>("issues.txt");
    bool sorted = false;

    for (const auto& user : users.data) {
        Service serv = Service(user, &issues, &sorted);
        UserForm* uForm = new UserForm(serv);
        forms.push_back(uForm);
    }

    for (const auto& sender : forms)
        for (const auto& receiver : forms)
            QObject::connect(sender, &UserForm::dataModified, receiver, &UserForm::on_dataModified);

    for (const auto& form : forms)
        form->show();

    return app.exec();
}
