#include "camel.h"
#include <QApplication>

#include "matrix.h"

int main(int argc, char *argv[])
{

    MathMatrix TestMatrix("Adafruit Bicolors I2C Leds Matrix");

    QApplication a(argc, argv);
    Camel w;
    w.show();

    return a.exec();
}
