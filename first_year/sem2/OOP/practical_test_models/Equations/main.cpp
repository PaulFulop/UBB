#include "Equations.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Equations window;
    window.show();
    return app.exec();
}
