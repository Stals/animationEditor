#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>

class Node;
class Edge;

class GraphWidget : public QGraphicsView{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    // Creates and edge between node1 and node2, ands it to the scene and return pointer
    Edge *createEdge(Node *node1, Node *node2);
    // Creates a node, adds it to the scene and returns pointer
    Node *createNode(qreal x, qreal y);

    // if addEdges is true - create edges when click 2 nodes
    bool addEdges;
    // stores a node to create an edge from
    Node* from;

public slots:
    // removes node from scene, removes its edges and deletes the node
    void removeNode(Node *node);
    // removes edge from scene and removes liks to it from source and distionation
    void removeEdge(Edge *edge);

    void emptyScene();
protected:
    void keyPressEvent(QKeyEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    void mousePressEvent(QMouseEvent *event);
};

#endif
