#include "ResearcherForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo<Researcher> researchers = Repo<Researcher>("researchers.txt");
    Repo<Idea> ideas = Repo<Idea>("ideas.txt");
    Repo<Idea> filteredIdeas = Repo<Idea>();
    for (const auto& idea : ideas.data)
        if (idea.status == "accepted")
            filteredIdeas.Add(idea);

    IdeasTableModel itm = IdeasTableModel(&ideas);
    DevelopedIdeasTableModel ditm = DevelopedIdeasTableModel(&filteredIdeas);

    std::vector<ResearcherForm*> forms;
    for (auto& r : researchers.data) {
        auto rForm = new ResearcherForm(&r, &ideas, &itm, &ditm);
        forms.push_back(rForm);
    }

    for (const auto& sender : forms)
        for (const auto& receiver : forms)
            if(sender != receiver)
                QObject::connect(sender, &ResearcherForm::ideaAccepted, receiver,&ResearcherForm::on_ideaAccepted);

    for (const auto& f : forms)
        f->show();

    return app.exec();
}
