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

void Frame::addEdge(GraphWidget *graphWidget, int id1, int id2){
    if(id1 == id2)
        return;

    Node *node1 = NULL;
    Node *node2 = NULL;

    foreach (QGraphicsItem *item, items) {
        if (Node *node = qgraphicsitem_cast<Node*>(item)){
            // create node
            if(node->id == id1)
                node1 = node;
            else if(node->id == id2)
                node2 = node;
        }
    }

    // if one of nodes doesn't exits - exit
    if((node1 == NULL) || (node2 == NULL))
        return;

    // If there is already an edge - dont do anything
    if(Node::isConnected(node1, node2) != NULL)
        return;

    // create edge and add it to this frame
    Edge *edge = new Edge(graphWidget, node1, node2);
    addEdge(edge);
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
