#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "edge.h"
#include "node.h"
#include "graphwidget.h"

int Node::newId = 0;

Node::Node(GraphWidget *graphWidget, qreal x, qreal y)
    : graph(graphWidget){

    id = newId++;
    this->setPos(x, y);

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    // set z to 1 so that node is over edges
    setZValue(1);
}

Node::~Node(){
    // if all nodes are deleted it should become 0 again
    --newId;
}

void Node::addEdge(Edge *edge){
    edgeList.push_back(edge);
    edge->adjust();
}

void Node::removeEdge(Edge *edge){
    edgeList.remove(edge);
}

void Node::removeConnections(){
    std::list<Edge*> edgeListCopy = edgeList;

    std::list<Edge*>::iterator edgeIt = edgeListCopy.begin();
    for(; edgeIt != edgeListCopy.end(); ++edgeIt){
        graph->removeEdge(*edgeIt);
    }
}

Edge *Node::isConnected(Node *node1, Node *node2){
    std::list<Edge*> edges = node1->edges();
    for(std::list<Edge*>::iterator edgeIt = edges.begin(); edgeIt != edges.end(); ++edgeIt){
    if(((*edgeIt)->destNode() == node2) || ((*edgeIt)->sourceNode() == node2)){
            return *edgeIt;
        }
    }
    return NULL;
}

std::list<Edge*> Node::edges() const{
    return edgeList;
}

QRectF Node::boundingRect() const{
    return QRectF((-1)*ellipseSide/2, (-1)*ellipseSide/2, ellipseSide, ellipseSide);
}

QPainterPath Node::shape() const{
    QPainterPath path;
    path.addEllipse((-1)*ellipseSide/2, (-1)*ellipseSide/2, ellipseSide, ellipseSide);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *){
    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        // change color if selected
        gradient.setColorAt(0, QColor(Qt::black).light(120));
        gradient.setColorAt(1, QColor(Qt::darkGray).light(120));
    } else {
        gradient.setColorAt(0, Qt::darkGray);
        gradient.setColorAt(1, Qt::black);
    }
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));

    painter->drawEllipse((-1)*ellipseSide/2, (-1)*ellipseSide/2, ellipseSide, ellipseSide);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value){
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::RightButton){
        // remove node and its edges
        graph->removeNode(this);
        return;
    }
    else if(event->button() == Qt::LeftButton){
        if(graph->addEdges){
            if(graph->from == NULL){
                // if this is a first node to be selected
                graph->from = this;
            }else{
                // if it is the second one - create an edge
                graph->createEdge(graph->from, this);
                // reset from
                graph->from = NULL;
            }
        }
    }
        update();
        QGraphicsItem::mousePressEvent(event);

}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
