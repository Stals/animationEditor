#ifndef FRAME_H
#define FRAME_H

#include <QList>
#include <QGraphicsItem>

#include "node.h"
#include "edge.h"

// Stores a single frame
class Frame{
public:
    Frame();
    ~Frame();
    // adds node to items
    void addNode(Node *node);
    // adds edge to items
    void addEdge(Edge *edge);

    // removes node from items
    void removeNode(Node *node);
    //removes edge from items
    void removeEdge(Edge *edge);

    // returns true if is empty
    bool isEmpty();

    QList<QGraphicsItem*> items;
};

#endif // FRAME_H
