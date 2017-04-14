#include "camel.h"
#include <QApplication>

#include "matrix.h"

int main(int argc, char *argv[])
{

    Matrix TestMatrix("TestName");

    QApplication a(argc, argv);
    Camel w;
    w.show();

    return a.exec();
}
