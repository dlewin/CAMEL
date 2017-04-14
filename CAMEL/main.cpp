#include "camel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Camel w;
    w.show();

    return a.exec();
}
