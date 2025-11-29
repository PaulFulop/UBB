#include "WriterForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::vector<WriterForm*> forms;
    auto writers = Repo<Writer>("writers.txt");
    auto ideas = Repo<Idea>("ideas.txt");
    bool sorted = false;
    auto itm = new IdeasTableModel(&ideas, &sorted);

    for (const auto& w : writers.data) {
        auto wForm = new WriterForm(w, itm);
        forms.push_back(wForm);
    }

    for (const auto& sender : forms)
        for (const auto& receiver : forms)
            QObject::connect(sender, &WriterForm::ideaAccepted, receiver, &WriterForm::on_ideaAccepted);

    for (const auto& form : forms)
        form->show();

    return app.exec();
}
