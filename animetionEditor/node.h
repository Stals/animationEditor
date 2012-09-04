#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <list>

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

// Note: x and y are stored in base class,
// each node has a unique id
class Node : public QGraphicsItem{
public:
    Node(GraphWidget *graphWidget, qreal x = 0, qreal y = 0);
    ~Node();

    int id;

    // adds edge to the edge list and adjusts it
    void addEdge(Edge *edge);
    // removes edge from the edgeList
    void removeEdge(Edge *edge);

    // removes all edges that have a connection to this node
    void removeConnections();

    // returns Edge if nodes are connected, else returns NULL
    static Edge *isConnected(Node* node1, Node* node2);

    std::list<Edge*> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    
private:
    static const double ellipseSide = 15;
    // static integer that stores if fore the next node
    static int newId;
    QPointF newPos;
    GraphWidget *graph;
    std::list<Edge*> edgeList;
};

#endif
