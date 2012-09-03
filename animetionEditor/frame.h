#ifndef FRAME_H
#define FRAME_H

#include <QList>
#include <QGraphicsItem>

// Stores a single frame
class Frame{
public:
    Frame();
    ~Frame();

    QList<QGraphicsItem*> items;
};

#endif // FRAME_H
