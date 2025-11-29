#include "ChefForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::vector<ChefForm*> forms;
    auto chefs = Repo<Chef>("chefs.txt");
    auto recipes = Repo<Recipe>("recipes.txt");
    bool sorted = false;

    for (const auto& c : chefs.data) {
        Service serv = Service(c, &recipes, &sorted);
        auto cForm = new ChefForm(serv);
        forms.push_back(cForm);
    }

    for (const auto& sender : forms) {
        for (const auto& receiver : forms) {
            QObject::connect(sender, &ChefForm::dataModified, receiver, &ChefForm::on_dataModified);
        }
    }

    for (const auto& f : forms)
        f->show();

    return app.exec();
}
