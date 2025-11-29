#include "MedicalDisordersForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MedicalDisordersForm window;
    window.show();
    return app.exec();
}
