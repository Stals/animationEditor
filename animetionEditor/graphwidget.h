#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>

#include "frame.h"

class Node;
class Edge;

// Widget for displaying and interacting with nodes and edges
class GraphWidget : public QGraphicsView{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0, const int width = 400, const int height = 400);

    // adds all nodes and edges from the frame to the scene
    void showFrame(Frame *frame);

    // adds node to the scene
    void addEdge(Edge *edge);
    // removes node from the scene
    void addNode(Node *node);
    // removes node from scene and the frame, removes its edges and deletes the node
    void removeNode(Node *node);
    // removes edge from scene and the frame, removes links to it from source and distionation
    void removeEdge(Edge *edge);

    // Removes all items from the scene, but does not delete them
    void emptyScene();

    // Creates an edge between node1 and node2, ands it to the scene and frame. Return pointer to it.
    Edge *createEdge(Node *node1, Node *node2);
    // Creates a node, adds it to the scene and frame. Returns pointer to it.
    Node *createNode(qreal x, qreal y);


    // if addEdges is true - edge will be created after clicking 2 nodes
    bool addEdges;
    // stores a node to create an edge from
    Node* from;

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    // stores currently showed frame
    Frame *currentFrame;
};

#endif
