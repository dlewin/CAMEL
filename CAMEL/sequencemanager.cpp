#include "sequencemanager.h"

SequenceManager::SequenceManager()
{
    QImage img1("C:\\img1.jpg");
    Matrix_Sequence.push_back(img1);
}

/// NOTE : For animation with QPixmap and Qimage look @ http://www.qtcentre.org/threads/26911-PNG-based-animation
