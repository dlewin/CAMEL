#ifndef MATRIXBUTTON_H
#define MATRIXBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QStyle>

class MatrixButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(bool _rightClicked READ wasRightClicked WRITE changeState)

public:
    explicit MatrixButton(QWidget * parent = 0) : QPushButton(parent){}
    ~MatrixButton(){}

    bool wasRightClicked(){return _rightClicked;}

public slots:
    void changeState(bool b)
    {
        _rightClicked = b;
        style()->unpolish(this);
        style()->polish(this);
    }

signals:
    void rightClicked();

protected:

    virtual void mousePressEvent(QMouseEvent *e)
    Q_DECL_OVERRIDE
    {
        if(e->button() == Qt::RightButton)
        {
            emit rightClicked();
            changeState(true);
        }
        else
        {
            changeState(false);
        }
        QPushButton::mousePressEvent(e);
    }

private:
    bool _rightClicked = false;
};

#endif // MATRIXBUTTON_H
