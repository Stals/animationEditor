#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>

class Node;
class Edge;

class GraphWidget : public QGraphicsView{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

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
