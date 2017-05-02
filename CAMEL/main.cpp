#include "camel.h"
#include <QApplication>

//#include "projectmatrix.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("David Lewin");
    QCoreApplication::setApplicationName("CAMEL");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    Camel *window = new Camel()                  ;

    window->setWindowTitle(QString::fromUtf8("Leds Matrix"))    ;
    window->show();

    return a.exec();
}
