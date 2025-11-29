#include "BiologistForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Repo<Biologist> biologists = Repo<Biologist>("biologists.txt");
    Repo<Bacterium> bacterium = Repo<Bacterium>("bacterium.txt");
    BacteriumTableModel* btm = new BacteriumTableModel(&bacterium);

    for (const auto& b : biologists.data) {
        BiologistForm* window = new BiologistForm(btm, b, &bacterium);
        window->show();
    }

    return app.exec();
}
