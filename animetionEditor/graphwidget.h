#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>

#include "frame.h"

class Node;
class Edge;

class GraphWidget : public QGraphicsView{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    // adds node to the scene
    void addEdge(Edge *edge);
    // removes node from the scene
    void addNode(Node *node);
    // removes node from scene, removes its edges and deletes the node
    void removeNode(Node *node);
    // removes edge from scene and removes liks to it from source and distionation
    void removeEdge(Edge *edge);

    // adds all nodes and edges to the scene
    void showFrame(Frame *frame);

    // Removes all items from the scene, but does not delete them
    void emptyScene();

    // Creates an edge between node1 and node2, ands it to the scene and frame. Return pointer to it.
    Edge *createEdge(Node *node1, Node *node2);
    // Creates a node, adds it to the scene and frame. Returns pointer to it.
    Node *createNode(qreal x, qreal y);


    // if addEdges is true - create edges when click 2 nodes
    bool addEdges;
    // stores a node to create an edge from
    Node* from;

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    Frame *currentFrame;
};

#endif
