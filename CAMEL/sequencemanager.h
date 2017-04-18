#ifndef SEQUENCEMANAGER_H
#define SEQUENCEMANAGER_H

#include <QVector>
#include <QImage>

class SequenceManager
{
public:
    SequenceManager();
    ~SequenceManager();
    QVector<QImage> Matrix_Sequence;
};

#endif // SEQUENCEMANAGER_H
