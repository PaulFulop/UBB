#include "AstronomerForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::vector<AstronomerForm*> forms;

    Repository<Astronomer> repoAstronomers = Repository<Astronomer>("astronomers.txt");
    Repository<Star> repoStars = Repository<Star>("stars.txt");
    AstronomerTableModel* modelTable = new AstronomerTableModel(&repoStars, &app);
    AstronomerListModel* modelList = new AstronomerListModel(&repoStars, &app);

    for (auto& astronomer : repoAstronomers.data) {
        Services serv = Services(&astronomer, &repoStars);
        AstronomerForm* form = new AstronomerForm(modelTable, modelList, serv);
        forms.push_back(form);
    }

    for (auto& form : forms)
        form->show();


    return app.exec();
}
