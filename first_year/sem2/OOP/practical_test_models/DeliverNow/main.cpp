#include "CourierCompanyForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CourierCompanyForm window;
    window.show();
    return app.exec();
}
