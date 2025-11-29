#include "ProgrammerForm.h"
#include "Statistics.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::vector<ProgrammerForm*> forms;
    auto programmers = Repo<Programmer>("programmers.txt");
    auto files = Repo<SourceFile>("files.txt");
    bool sorted = false;

    Statistics* sForm = new Statistics(&programmers);
    for (auto& p : programmers.data) {
        auto serv = Service(&p, &files, &sorted);
        auto pForm = new ProgrammerForm(serv);
        forms.push_back(pForm);
    }

    for (const auto& sender : forms) {
        for (const auto& receiver : forms)
            QObject::connect(sender, &ProgrammerForm::dataModified, receiver, &ProgrammerForm::on_dataModified);
        QObject::connect(sender, &ProgrammerForm::dataModified, sForm, &Statistics::on_dataModified);
    }

    for (const auto& f : forms)
        f->show();
    sForm->show();

    return app.exec();
}
