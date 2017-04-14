#ifndef CAMEL_H
#define CAMEL_H

#include <QMainWindow>

namespace Ui {
class Camel;
}

class Camel : public QMainWindow
{
    Q_OBJECT

public:
    explicit Camel(QWidget *parent = 0);
    ~Camel();

private:
    Ui::Camel *ui;
};

#endif // CAMEL_H
