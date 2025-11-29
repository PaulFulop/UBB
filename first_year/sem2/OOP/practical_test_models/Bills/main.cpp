#include "Bills.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bills w;
    w.show();
    return a.exec();
}
