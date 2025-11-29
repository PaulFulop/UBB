#include "UserForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::vector<UserForm*> userForms;

    Repo<User> userRepo = Repo<User>("users.txt");
    Repo<Item> itemRepo = Repo<Item>("items.txt");

    for (const auto& user : userRepo.data) {
        UserForm* userForm = new UserForm(user, &itemRepo);
        userForms.push_back(userForm);
    }

    for (const auto& sender : userForms)
        for (const auto& receiver : userForms) {
            QWidget::connect(sender, &UserForm::newItemAdded, receiver, &UserForm::on_newItemAdded);
            QWidget::connect(sender, &UserForm::itemPriceChanged, receiver, &UserForm::on_itemPriceChanged);
        }


    for (const auto& userForm : userForms)
        userForm->show();

    return app.exec();
}
