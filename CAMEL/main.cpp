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


//    QWidget *centralWidget = new QWidget(window)                ;
    window->setWindowTitle(QString::fromUtf8("Leds Matrix"))    ;

//    ProjectMatrix workMatrix("Adafruit Bicolors I2C Leds Matrix", 8,8,3, centralWidget);
//    window->setCentralWidget(centralWidget) ;

    window->show();

    return a.exec();
}
