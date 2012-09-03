#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <QtGui>

#include <math.h>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent),
      addEdges(false),
      from(NULL),
      currentFrame(new Frame){

    // TODO understand what does what and remove unnessary stuff
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    //scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Elastic Nodes"));

//    Node *node1 = createNode(50, 50);
//    Node *node2 = createNode(100, 100);
//    Node *node3 = createNode(50, 100);
//    Node *node4 = createNode(250, 250);

//    createEdge(node1, node2);
//    createEdge(node2, node3);
//    createEdge(node4, node2);
//    createEdge(node3, node1);

}

void GraphWidget::addEdge(Edge *edge){
    scene()->addItem(edge);
}

void GraphWidget::addNode(Node *node){
    scene()->addItem(node);
}

void GraphWidget::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
//    case Qt::Key_Up:
//        centerNode->moveBy(0, -20);
//        break;
//    case Qt::Key_Down:
//        centerNode->moveBy(0, 20);
//        break;
//    case Qt::Key_Left:
//        centerNode->moveBy(-20, 0);
//        break;
//    case Qt::Key_Right:
//        centerNode->moveBy(20, 0);
//        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect){
//    // Shadow
//    QRectF sceneRect = this->sceneRect();
//    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
//    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
//    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
//    painter->fillRect(rightShadow, Qt::darkGray);
//    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
//    painter->fillRect(bottomShadow, Qt::darkGray);

//    // Fill
//    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
//    gradient.setColorAt(0, Qt::white);
//    gradient.setColorAt(1, Qt::lightGray);
//    painter->fillRect(rect.intersect(sceneRect), gradient);
//    painter->setBrush(Qt::NoBrush);
//    painter->drawRect(sceneRect);

//    // Text
//    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
//                    sceneRect.width() - 4, sceneRect.height() - 4);
//    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
//                       "wheel or the '+' and '-' keys"));

//    QFont font = painter->font();
//    font.setBold(true);
//    font.setPointSize(14);
//    painter->setFont(font);
//    painter->setPen(Qt::lightGray);
//    painter->drawText(textRect.translated(2, 2), message);
//    painter->setPen(Qt::black);
//    painter->drawText(textRect, message);

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
    // TODO может быть утечка памяти, так как я не удаляю сами объекты
//        QList<Node*> nodes;
//        foreach (QGraphicsItem *item, scene()->items()) {
//            if (Node *node = qgraphicsitem_cast<Node*>(item))
//                nodes << node;
//        }

//        foreach (Node *node, nodes)
//            removeNode(node);

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

//TODO what if node1 == node2?
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
