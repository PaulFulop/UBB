#include "PresenterForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PresenterForm window;
    window.show();
    return app.exec();
}
