#include "camel.h"
#include <QApplication>

#include "projectmatrix.h"

int main(int argc, char *argv[])
{
    ProjectMatrix workMatrix("Adafruit Bicolors I2C Leds Matrix", 8,8,3);

    QApplication a(argc, argv);
    Camel *window = new Camel()                  ;
    QWidget *centralWidget = new QWidget(window)                ;
    window->setWindowTitle(QString::fromUtf8("Leds Matrix"))    ;
    window->setCentralWidget(centralWidget)                     ;

    window->show();

    return a.exec();
}
