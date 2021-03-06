#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;

Edge::Edge(GraphWidget *graphWidget, Node *sourceNode, Node *destNode):
    graph(graphWidget){

    //setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    pen = QPen(Qt::black, lineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    adjust();
}

Edge::~Edge(){
    //remove this edge from sourse and dest
    source->removeEdge(this);
    dest->removeEdge(this);
}

Node *Edge::sourceNode() const{
    return source;
}

Node *Edge::destNode() const{
    return dest;
}

void Edge::adjust(){
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        sourcePoint = line.p1();
        destPoint = line.p2();
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const{
    if (!source || !dest)
        return QRectF();

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));

    const qreal x1 = line.p1().x();
    const qreal x2 = line.p2().x();
    const qreal y1 = line.p1().y();
    const qreal y2 = line.p2().y();
    qreal lx = qMin(x1, x2);
    qreal rx = qMax(x1, x2);
    qreal ty = qMin(y1, y2);
    qreal by = qMax(y1, y2);
    return QRectF(lx, ty, rx - lx, by - ty);

}

QPainterPath Edge::shape() const{
    QPainterPath path;

    path.moveTo(sourcePoint.toPoint());
    path.lineTo(destPoint.toPoint());

    // Code from QGrapthicsLineItem implemetation
    const qreal penWidthZero = qreal(0.00000001);

    QPainterPathStroker ps;
    ps.setCapStyle(pen.capStyle());
    if (pen.widthF() <= 0.0)
        ps.setWidth(penWidthZero);
    else
        ps.setWidth(pen.widthF());
    ps.setJoinStyle(pen.joinStyle());
    ps.setMiterLimit(pen.miterLimit());
    QPainterPath p = ps.createStroke(path);
    p.addPath(path);
    return p;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(pen);
    painter->drawLine(line);
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::RightButton){
        // remove edge and liks to it
        graph->removeEdge(this);
    }else{
        update();
        QGraphicsItem::mousePressEvent(event);
    }
}

void Edge::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
