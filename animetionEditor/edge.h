#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Edge : public QGraphicsItem{
public:
    Edge(GraphWidget *graphWidget, Node *sourceNode, Node *destNode);
    ~Edge();

    Node *sourceNode() const;
    Node *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const { return Type; }
    
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    Node *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;

    GraphWidget *graph;

    static const int lineWidth = 2;

};

#endif
