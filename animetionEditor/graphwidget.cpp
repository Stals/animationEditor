#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <QtGui>

#include <math.h>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent){

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

    Node *node1 = new Node(this);
    Node *node2 = new Node(this);
    Node *node3 = new Node(this);
    Node *node4 = new Node(this);
//    centerNode = new Node(this);
//    Node *node6 = new Node(this);
//    Node *node7 = new Node(this);
//    Node *node8 = new Node(this);
//    Node *node9 = new Node(this);
    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);
//    scene->addItem(centerNode);
//    scene->addItem(node6);
//    scene->addItem(node7);
//    scene->addItem(node8);
//    scene->addItem(node9);
    Edge * edge = new Edge(this, node1, node2);
    scene->addItem(edge);
    //scene->removeItem(edge);
    scene->addItem(new Edge(this, node2, node3));
//    scene->addItem(new Edge(node2, centerNode));
//    scene->addItem(new Edge(node3, node6));
    scene->addItem(new Edge(this, node4, node2));
//    scene->addItem(new Edge(node4, centerNode));
//    scene->addItem(new Edge(centerNode, node6));
//    scene->addItem(new Edge(centerNode, node8));
//    scene->addItem(new Edge(node6, node9));
//    scene->addItem(new Edge(node7, node4));
//    scene->addItem(new Edge(node8, node7));
//    scene->addItem(new Edge(node9, node8));

    node1->setPos(50, 50);
    node2->setPos(100, 100);
    node3->setPos(50, 100);
    node4->setPos(250, 250);
//    centerNode->setPos(0, 0);
//    node6->setPos(50, 0);
//    node7->setPos(-50, 50);
//    node8->setPos(0, 50);
//    node9->setPos(50, 50);

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
        Node *node = new Node(this);
        scene()->addItem(node);

        node->setPos(event->pos());
    }
    update();
    QGraphicsView::mousePressEvent(event);
}

void GraphWidget::removeNode(Node* node){
    scene()->removeItem(node);
    // deleting node will also delete all conected edges
    delete node;
}

void GraphWidget::removeEdge(Edge *edge){
    scene()->removeItem(edge);
    // deleting edge will also delete it from nodes it is connected to
    delete edge;
}

void GraphWidget::emptyScene(){
    // TODO может быть утечка памяти, так как я не удаляю сами объекты
        QList<Node *> nodes;
        foreach (QGraphicsItem *item, scene()->items()) {
            if (Node *node = qgraphicsitem_cast<Node *>(item))
                nodes << node;
        }

        foreach (Node *node, nodes)
            removeNode(node);
}
