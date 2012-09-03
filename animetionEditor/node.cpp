#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "edge.h"
#include "node.h"
#include "graphwidget.h"

Node::Node(GraphWidget *graphWidget)
    : graph(graphWidget){

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    // set z to 1 so that node is over edges
    setZValue(1);
}

Node::~Node(){
    //TODO попробывать переписать без использования копии
    std::list<Edge*> edgeListCopy = edgeList;

    std::list<Edge*>::iterator edgeIt = edgeListCopy.begin();
    for(; edgeIt != edgeListCopy.end(); ++edgeIt){
        graph->scene()->removeItem(*edgeIt);
        delete *edgeIt;
    }
}

void Node::addEdge(Edge *edge){
    edgeList.push_back(edge);
    edge->adjust();
}

void Node::removeEdge(Edge *edge){
    edgeList.remove(edge);
}

std::list<Edge*> Node::edges() const{
    return edgeList;
}

bool Node::advance(){
//    if (newPos == pos())
//        return false;

//    setPos(newPos);
//    return true;
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
    // TODO rewrite with a switch case
    if(event->button() == Qt::LeftButton){
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
    else if(event->button() == Qt::RightButton){
        // remove node and its edges
        graph->removeNode(this);
    }else{
        update();
        QGraphicsItem::mousePressEvent(event);
    }
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
