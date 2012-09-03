#include "frame.h"

Frame::Frame(){
}

Frame::~Frame(){
    // remove edges first so that it will not try to access deleted nodes
    QList<Edge*> edges;
    QList<Node*> nodes;
    foreach (QGraphicsItem *item, items) {
        if (Edge *edge = qgraphicsitem_cast<Edge*>(item))
            edges << edge;
        else if (Node *node = qgraphicsitem_cast<Node*>(item))
            nodes << node;
    }
    foreach (Edge *edge, edges){
        delete edge;
    }
    foreach (Node *node, nodes){
        delete node;
    }
}

void Frame::addNode(Node *node){
    items.push_back(node);
}

void Frame::addEdge(Edge *edge){
    items.push_back(edge);
}

void Frame::removeNode(Node *node){
    items.removeOne(node);
}

void Frame::removeEdge(Edge *edge){
    items.removeOne(edge);
}

bool Frame::isEmpty(){
    return !items.size();
}
