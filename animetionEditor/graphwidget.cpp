#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <QtGui>

#include <math.h>

GraphWidget::GraphWidget(QWidget *parent, const int width, const int height)
    : QGraphicsView(parent),
      addEdges(false),
      from(NULL),
      currentFrame(new Frame){

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, width, height);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(width, height);
}

void GraphWidget::addEdge(Edge *edge){
    scene()->addItem(edge);
}

void GraphWidget::addNode(Node *node){
    scene()->addItem(node);
}

void GraphWidget::mousePressEvent(QMouseEvent *event){
    // add new Node on middle click
    if(event->button() == Qt::MiddleButton){        
        createNode(event->pos().x(), event->pos().y());
    }
    update();
    QGraphicsView::mousePressEvent(event);
}

void GraphWidget::removeNode(Node *node){
    scene()->removeItem(node);
    currentFrame->removeNode(node);
    // deleting node will also delete all conected edges
    node->removeConnections();
    delete node;
}

void GraphWidget::removeEdge(Edge *edge){
    scene()->removeItem(edge);
    currentFrame->removeEdge(edge);
    // deleting edge will also delete it from nodes it is connected to
    delete edge;
}

void GraphWidget::showFrame(Frame *frame){
    currentFrame = frame;

    QList<Node*> nodes;
    QList<Edge*> edges;
    foreach (QGraphicsItem *item, frame->items) {
        if (Node *node = qgraphicsitem_cast<Node*>(item))
            nodes << node;
        else if (Edge *edge = qgraphicsitem_cast<Edge*>(item))
            edges << edge;
    }
    foreach (Node *node, nodes){
        addNode(node);
    }
    foreach (Edge *edge, edges){
        addEdge(edge);
    }
}
void GraphWidget::emptyScene(){
    QList<Node*> nodes;
    QList<Edge*> edges;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node*>(item))
            nodes << node;
        else if (Edge *edge = qgraphicsitem_cast<Edge*>(item))
            edges << edge;
    }
    foreach (Node *node, nodes)
        scene()->removeItem(node);
    foreach (Edge *edge, edges)
        scene()->removeItem(edge);
}

Edge *GraphWidget::createEdge(Node *node1, Node *node2){
    // Check if nodes are already connected
    // just return pointer to this edge if they are
    Edge* edge = Node::isConnected(node1, node2);
    if (edge != NULL)
        return edge;

    // else create new Edge
    edge = new Edge(this, node1, node2);
    scene()->addItem(edge);
    currentFrame->addEdge(edge);
    return edge;
}

Node *GraphWidget::createNode(qreal x, qreal y){
    Node *node = new Node(this);
    scene()->addItem(node);
    node->setPos(x, y);
    currentFrame->addNode(node);
    return node;
}
