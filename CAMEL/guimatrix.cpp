#include "guimatrix.h"
#include "projectmatrix.h"

#define MESSAGE \
    GuiMatrix::tr("<p>Message boxes have a caption, a text, " \
               "and any number of buttons, each with standard or custom texts." \
               "<p>Click a button to close the message box. Pressing the Esc button " \
               "will activate the detected escape button (if any).")


GuiMatrix::GuiMatrix(int Rows, int Cols, int Led_colors)
{
    // Let's create the HMI that accepts click as input and also represent the MainMatrix states
// MyButtonGroup* group   = new MyButtonGroup(centralWidget)   ;
//    setParent(parentWidget)  ;

    QVBoxLayout *layout     = new QVBoxLayout()                             ;
    QHBoxLayout *Hlayout    = new QHBoxLayout()                                         ;
    QGridLayout *Glayout    = new QGridLayout()                                         ;
    Glayout->setSpacing(0)                                                              ;
    Hlayout->addStretch(1)                                                              ;
    Hlayout->addLayout(Glayout)                                                         ;
    Hlayout->addStretch(1)                                                              ;
    layout->addLayout(Hlayout)                                                          ;
    layout->addStretch(1)                                                               ;

    Populate(Glayout,Rows,Cols);

//    errorMessageDialog = new QErrorMessage();
//   colorLabel = new QLabel;
//   QPushButton *colorButton = new QPushButton(tr("QColorDialog"));
//   Glayout->addWidget(colorButton);

//   parentWidget->setLayout(layout)                                                     ;
//   connect(colorButton, SIGNAL(clicked()), this, SLOT( setColor() ));
   connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));


}

void GuiMatrix::Populate(QGridLayout *layout, const int rows, const int cols)
{
    for (uint i = 0; i < rows; ++ i)
    {
     for (uint j = 0; j < cols; ++j)
     {
//      QString index = QStringLiteral("(%1,%2)").arg(i).arg(j)   ;
      QPushButton* btn = new QPushButton(" ")                 ;
      btn->setFixedWidth(20);
      btn->setStyleSheet("background-color:grey;")              ;
      layout->addWidget(btn,i,j)                                ;

      this->addButton(btn)                              ;
     }
    }
}

void GuiMatrix::buttonClick(QAbstractButton* button)
{
    qDebug() << "in buttonClick" ;
}

GuiMatrix::~GuiMatrix()
{
}

/*
void GuiMatrix::setColor()
{
    qDebug() << "in Setcolor" ;
    QColor color;

        color = QColorDialog::getColor(Qt::green, parentWidget);

    if (color.isValid()) {
        colorLabel->setText(color.name());
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }
}


void GuiMatrix::criticalMessage(QWidget *parentWidget)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(parentWidget, tr("QMessageBox::critical()"),
                                    MESSAGE,
                                    QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);
//    if (reply == QMessageBox::Abort)
//        criticalLabel->setText(tr("Abort"));
//    else if (reply == QMessageBox::Retry)
//        criticalLabel->setText(tr("Retry"));
//    else
//        criticalLabel->setText(tr("Ignore"));
}

void GuiMatrix::informationMessage(QWidget *parentWidget)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(parentWidget, tr("QMessageBox::information()"), MESSAGE);
//    if (reply == QMessageBox::Ok)
//        informationLabel->setText(tr("OK"));
//    else
//        informationLabel->setText(tr("Escape"));
}

void GuiMatrix::questionMessage(QWidget *parentWidget)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(parentWidget, tr("QMessageBox::question()"),
                                    MESSAGE,
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
//    if (reply == QMessageBox::Yes)
//        questionLabel->setText(tr("Yes"));
//    else if (reply == QMessageBox::No)
//        questionLabel->setText(tr("No"));
//    else
//        questionLabel->setText(tr("Cancel"));
}

void GuiMatrix::warningMessage(QWidget *parentWidget)
{
    QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"),
                       MESSAGE, 0, parentWidget);
    msgBox.addButton(tr("Save &Again"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("&Continue"), QMessageBox::RejectRole);
//    if (msgBox.exec() == QMessageBox::AcceptRole)
//        warningLabel->setText(tr("Save Again"));
//    else
//        warningLabel->setText(tr("Continue"));
}

void GuiMatrix::errorMessage()
{
    errorMessageDialog->showMessage(
            tr("This dialog shows and remembers error messages. "
               "If the checkbox is checked (as it is by default), "
               "the shown message will be shown again, "
               "but if the user unchecks the box the message "
               "will not appear again if QErrorMessage::showMessage() "
               "is called with the same message."));
//    errorLabel->setText(tr("If the box is unchecked, the message "                           "won't appear again."));
}
*/
